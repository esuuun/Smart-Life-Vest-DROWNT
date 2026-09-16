import React, { useState, useEffect, useRef } from 'react';
import Header from './components/Header';
import StatsBar from './components/StatsBar';
import LiveMap from './components/LiveMap';
import MLDiagnostics from './components/MLDiagnostics';
import TelemetryLog from './components/TelemetryLog';
import SimulatorControls from './components/SimulatorControls';
import { serialService } from './services/serialService';

// Initial Mock Telemetry State (Titik awal: Danau Kenanga Rektorat UI Depok)
const initialTelemetry = {
  id: 'VEST-01',
  seq: 0,
  timestamp: new Date().toLocaleTimeString(),
  status: 'AMAN',
  riskScore: 6,
  spo2: 98,
  heartRate: 74,
  temperature: 36.6,
  inWater: false,
  isFaceDown: false,
  pitch: 2.1,
  roll: -1.4,
  latitude: -6.3627,
  longitude: 106.8272,
  satellites: 9,
  probAman: 0.94,
  probWaspada: 0.05,
  probKritis: 0.01,
};

export default function App() {
  const [telemetry, setTelemetry] = useState(initialTelemetry);
  const [breadcrumbs, setBreadcrumbs] = useState([[-6.3627, 106.8272]]);
  const [logs, setLogs] = useState([]);
  const [connectionState, setConnectionState] = useState({ connected: false });
  const [isSimulatorActive, setIsSimulatorActive] = useState(false);
  const [currentScenario, setCurrentScenario] = useState('NORMAL');
  const [isMuted, setIsMuted] = useState(true); // Default muted to avoid annoying loud sound initially
  const [theme, setTheme] = useState('light');  // Default: Light Mode

  useEffect(() => {
    document.documentElement.setAttribute('data-theme', theme);
  }, [theme]);

  const handleToggleTheme = () => {
    setTheme((prev) => (prev === 'light' ? 'dark' : 'light'));
  };

  const audioCtxRef = useRef(null);

  // Fungsi Audio Alarm menggunakan Web Audio API (Tanpa butuh file MP3 eksternal)
  const playAlertTone = (type) => {
    if (isMuted) return;

    try {
      if (!audioCtxRef.current) {
        audioCtxRef.current = new (window.AudioContext || window.webkitAudioContext)();
      }
      const ctx = audioCtxRef.current;
      if (ctx.state === 'suspended') {
        ctx.resume();
      }

      const osc = ctx.createOscillator();
      const gain = ctx.createGain();
      osc.connect(gain);
      gain.connect(ctx.destination);

      if (type === 'KRITIS') {
        // Dual-tone High Alert Beep
        osc.frequency.setValueAtTime(880, ctx.currentTime);
        osc.frequency.setValueAtTime(659, ctx.currentTime + 0.15);
        gain.gain.setValueAtTime(0.3, ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.35);
        osc.start();
        osc.stop(ctx.currentTime + 0.35);
      } else if (type === 'WASPADA') {
        // Single Attention Ping
        osc.frequency.setValueAtTime(523.25, ctx.currentTime); // C5
        gain.gain.setValueAtTime(0.15, ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.01, ctx.currentTime + 0.25);
        osc.start();
        osc.stop(ctx.currentTime + 0.25);
      }
    } catch (e) {
      console.warn('Audio Context error:', e);
    }
  };

  // Handler penerimaan data baru (baik dari Serial USB maupun Simulator)
  const handleDataReceived = (newData) => {
    setTelemetry(newData);

    // Tambahkan titik breadcrumb jika koordinat valid
    if (newData.latitude && newData.longitude) {
      setBreadcrumbs((prev) => {
        const last = prev[prev.length - 1];
        if (!last || Math.abs(last[0] - newData.latitude) > 0.00002 || Math.abs(last[1] - newData.longitude) > 0.00002) {
          return [...prev.slice(-100), [newData.latitude, newData.longitude]];
        }
        return prev;
      });
    }

    // Tambah ke riwayat log
    setLogs((prev) => [...prev, newData]);

    // Bunyikan nada alert jika bahaya
    if (newData.status === 'KRITIS') {
      playAlertTone('KRITIS');
    } else if (newData.status === 'WASPADA') {
      playAlertTone('WASPADA');
    }
  };

  // Koneksi Web Serial USB
  const handleConnectSerial = async () => {
    try {
      if (isSimulatorActive) {
        serialService.stopSimulator();
        setIsSimulatorActive(false);
      }
      await serialService.connect(handleDataReceived, setConnectionState);
    } catch (err) {
      console.error('Serial connect error:', err);
      alert('Koneksi Serial Gagal: ' + err.message);
    }
  };

  const handleDisconnectSerial = async () => {
    await serialService.disconnect(setConnectionState);
  };

  // Simulator Toggle & Scenario Change
  const handleToggleSimulator = () => {
    if (isSimulatorActive) {
      serialService.stopSimulator();
      setIsSimulatorActive(false);
    } else {
      if (connectionState.connected) {
        serialService.disconnect(setConnectionState);
      }
      setIsSimulatorActive(true);
      serialService.startSimulator(currentScenario, handleDataReceived);
    }
  };

  const handleSelectScenario = (scenarioId) => {
    setCurrentScenario(scenarioId);
    if (isSimulatorActive) {
      serialService.startSimulator(scenarioId, handleDataReceived);
    }
  };

  // Quick Preset Locations
  const handleSetPresetLocation = (lat, lng) => {
    setTelemetry((prev) => ({ ...prev, latitude: lat, longitude: lng }));
    setBreadcrumbs([[lat, lng]]);
  };

  // Export Data Sesi ke CSV
  const handleExportCSV = () => {
    if (logs.length === 0) {
      alert('Belum ada data rekaman telemetri untuk di-export.');
      return;
    }

    const headers = [
      'Timestamp',
      'Seq',
      'Device_ID',
      'Status_ML',
      'Risk_Score',
      'SpO2_Percent',
      'Heart_Rate_BPM',
      'Temp_Celcius',
      'In_Water',
      'Is_FaceDown',
      'Pitch_Deg',
      'Roll_Deg',
      'Latitude',
      'Longitude',
      'Satellites'
    ];

    const csvRows = logs.map((l) => [
      l.timestamp,
      l.seq,
      l.id,
      l.status,
      l.riskScore,
      l.spo2,
      l.heartRate,
      l.temperature,
      l.inWater ? 1 : 0,
      l.isFaceDown ? 1 : 0,
      l.pitch,
      l.roll,
      l.latitude,
      l.longitude,
      l.satellites
    ]);

    const csvContent = [headers.join(','), ...csvRows.map((r) => r.join(','))].join('\n');
    const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });
    const url = URL.createObjectURL(blob);
    const link = document.createElement('a');
    link.setAttribute('href', url);
    link.setAttribute('download', `DROWNT_SAR_Session_${new Date().toISOString().slice(0, 10)}.csv`);
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
  };

  return (
    <div className="app-container">
      {/* Header Bar */}
      <Header
        connectionState={connectionState}
        onConnectSerial={handleConnectSerial}
        onDisconnectSerial={handleDisconnectSerial}
        isSimulatorActive={isSimulatorActive}
        onToggleSimulator={handleToggleSimulator}
        isMuted={isMuted}
        onToggleMute={() => setIsMuted(!isMuted)}
        onExportCSV={handleExportCSV}
        currentStatus={telemetry.status}
        packetCount={logs.length}
        theme={theme}
        onToggleTheme={handleToggleTheme}
      />

      {/* Main Dashboard Layout */}
      <main className="main-content">
        {/* Top KPI Metrics HUD */}
        <StatsBar telemetry={telemetry} />

        {/* Demo Simulator Controls (Active when user clicks Demo Simulator) */}
        {isSimulatorActive && (
          <SimulatorControls
            currentScenario={currentScenario}
            onSelectScenario={handleSelectScenario}
          />
        )}

        {/* Split Grid: Live Map (Left) & Diagnostics / Log (Right) */}
        <div style={{
          display: 'grid',
          gridTemplateColumns: 'minmax(0, 1.45fr) minmax(0, 1fr)',
          gap: '1.25rem',
          flex: 1
        }}>
          {/* Left Column: Live Tactical Map */}
          <LiveMap
            telemetry={telemetry}
            breadcrumbs={breadcrumbs}
            onSetPresetLocation={handleSetPresetLocation}
            theme={theme}
          />

          {/* Right Column: ML Engine Breakdown & Real-Time Log */}
          <div style={{ display: 'flex', flexDirection: 'column', gap: '1.25rem' }}>
            <MLDiagnostics telemetry={telemetry} />
            <TelemetryLog logs={logs} onClearLogs={() => setLogs([])} />
          </div>
        </div>
      </main>
    </div>
  );
}
