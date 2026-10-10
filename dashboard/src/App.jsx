import React, { useState, useEffect, useRef } from 'react';
import Sidebar from './components/Sidebar';
import Header from './components/Header';
import OverviewPage from './components/OverviewPage';
import ReportPage from './components/ReportPage';
import HistoryPage from './components/HistoryPage';
import DevicesPage from './components/DevicesPage';
import SettingsPage from './components/SettingsPage';
import { serialService } from './services/serialService';
import { bleService } from './services/bleService';

// Initial Mock Telemetry State (Titik awal: Danau Kenanga Rektorat UI Depok)
const initialTelemetry = {
  id: 'VEST-01',
  seq: 0,
  timestamp: new Date().toLocaleTimeString(),
  status: 'AMAN',
  riskScore: 0,
  spo2: 0,
  heartRate: 0,
  waistWater: 0,
  neckWater: 0,
  isSubmerged: false,
  inWater: false,
  latitude: -6.3627,
  longitude: 106.8272,
  satellites: 9,
  probAman: 0.94,
  probWaspada: 0.05,
  probKritis: 0.01,
};

export default function App() {
  const [activePage, setActivePage] = useState('overview');
  const [isSidebarCollapsed, setIsSidebarCollapsed] = useState(false);
  const [isMobileSidebarOpen, setIsMobileSidebarOpen] = useState(false);

  const [telemetry, setTelemetry] = useState(initialTelemetry);
  const [breadcrumbs, setBreadcrumbs] = useState([[-6.3627, 106.8272]]);
  const [logs, setLogs] = useState([]);
  const [connectionState, setConnectionState] = useState({ connected: false });
  const [isSimulatorActive, setIsSimulatorActive] = useState(false);
  const [currentScenario, setCurrentScenario] = useState('NORMAL');
  const [isMuted, setIsMuted] = useState(false); // Default: Suara alarm aktif!
  const [theme, setTheme] = useState('light');  // Default: Light Mode
  const alarmAudioRef = useRef(null);

  useEffect(() => {
    document.documentElement.setAttribute('data-theme', theme);
  }, [theme]);

  // Siapkan elemen Audio untuk alarm.mp4
  useEffect(() => {
    const audio = new Audio('/alarm.mp4');
    audio.loop = true;
    alarmAudioRef.current = audio;

    return () => {
      audio.pause();
    };
  }, []);

  // Sync mute state ke elemen audio
  useEffect(() => {
    if (alarmAudioRef.current) {
      alarmAudioRef.current.muted = isMuted;
      if (isMuted) {
        alarmAudioRef.current.pause();
      }
    }
  }, [isMuted]);

  const handleToggleTheme = () => {
    setTheme((prev) => (prev === 'light' ? 'dark' : 'light'));
  };

  const audioCtxRef = useRef(null);

  // Ping warning lembut untuk status WASPADA (Web Audio API)
  const playWarningTone = () => {
    if (isMuted) return;
    try {
      if (!audioCtxRef.current) {
        audioCtxRef.current = new (window.AudioContext || window.webkitAudioContext)();
      }
      const ctx = audioCtxRef.current;
      if (ctx.state === 'suspended') ctx.resume();

      const now = ctx.currentTime;
      const osc = ctx.createOscillator();
      const gain = ctx.createGain();

      osc.type = 'sine';
      osc.frequency.setValueAtTime(720, now);
      osc.frequency.exponentialRampToValueAtTime(880, now + 0.12);

      gain.gain.setValueAtTime(0.2, now);
      gain.gain.exponentialRampToValueAtTime(0.01, now + 0.22);

      osc.connect(gain);
      gain.connect(ctx.destination);

      osc.start(now);
      osc.stop(now + 0.22);
    } catch (e) {
      console.warn('Audio Context error:', e);
    }
  };

  // Handler penerimaan data baru (baik dari Serial USB, BLE, maupun Simulator)
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

    // Putar file alarm.mp4 jika status KRITIS
    if (newData.status === 'KRITIS') {
      if (!isMuted && alarmAudioRef.current) {
        if (alarmAudioRef.current.paused) {
          alarmAudioRef.current.currentTime = 0;
          alarmAudioRef.current.play().catch((err) => {
            console.log('Autoplay audio dicegah oleh browser, tunggu klik user:', err);
          });
        }
      }
    } else {
      // Jika status turun dari KRITIS ke WASPADA/AMAN -> matikan sirine mp4
      if (alarmAudioRef.current && !alarmAudioRef.current.paused) {
        alarmAudioRef.current.pause();
        alarmAudioRef.current.currentTime = 0;
      }
      if (newData.status === 'WASPADA') {
        playWarningTone();
      }
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

  // Koneksi Nirkabel Web Bluetooth (BLE)
  const handleConnectBLE = async () => {
    try {
      if (isSimulatorActive) {
        serialService.stopSimulator();
        setIsSimulatorActive(false);
      }
      await bleService.connect(handleDataReceived, setConnectionState);
    } catch (err) {
      console.error('BLE connect error:', err);
      if (err.name !== 'NotFoundError') {
        alert('Koneksi Bluetooth Gagal: ' + err.message);
      }
    }
  };

  const handleDisconnectBLE = async () => {
    await bleService.disconnect(setConnectionState);
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
      'Water_Waist_Percent',
      'Water_Neck_Percent',
      'In_Water',
      'Latitude',
      'Longitude',
      'Satellites',
      'Prob_Aman',
      'Prob_Waspada',
      'Prob_Kritis'
    ];

    const csvRows = logs.map((l) => [
      l.timestamp,
      l.seq,
      l.id,
      l.status,
      l.riskScore,
      l.spo2,
      l.heartRate,
      l.waistWater != null ? l.waistWater : '',
      l.neckWater != null ? l.neckWater : '',
      l.inWater ? 1 : 0,
      l.latitude,
      l.longitude,
      l.satellites,
      l.probAman,
      l.probWaspada,
      l.probKritis
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
    <div className="app-shell">
      {/* 1. Global Navigation Sidebar */}
      <Sidebar
        activePage={activePage}
        setActivePage={setActivePage}
        isCollapsed={isSidebarCollapsed}
        setIsCollapsed={setIsSidebarCollapsed}
        connectionState={connectionState}
        currentStatus={telemetry.status}
        packetCount={logs.length}
        isMobileOpen={isMobileSidebarOpen}
        setIsMobileOpen={setIsMobileSidebarOpen}
      />

      {/* 2. Main Viewport Container */}
      <div className={`main-viewport ${isSidebarCollapsed ? 'sidebar-collapsed' : ''}`}>
        {/* Top Header Bar */}
        <Header
          activePage={activePage}
          onToggleMobileSidebar={() => setIsMobileSidebarOpen(!isMobileSidebarOpen)}
          connectionState={connectionState}
          onConnectSerial={handleConnectSerial}
          onDisconnectSerial={handleDisconnectSerial}
          onConnectBLE={handleConnectBLE}
          onDisconnectBLE={handleDisconnectBLE}
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

        {/* Dynamic Page Views */}
        <main className="content-area">
          {activePage === 'overview' && (
            <OverviewPage
              telemetry={telemetry}
              breadcrumbs={breadcrumbs}
              logs={logs}
              onClearLogs={() => setLogs([])}
              connectionState={connectionState}
              isSimulatorActive={isSimulatorActive}
              currentScenario={currentScenario}
              onSelectScenario={handleSelectScenario}
              onSetPresetLocation={handleSetPresetLocation}
              theme={theme}
            />
          )}

          {activePage === 'reports' && (
            <ReportPage
              telemetry={telemetry}
              logs={logs}
              currentScenario={currentScenario}
              onExportCSV={handleExportCSV}
            />
          )}

          {activePage === 'history' && (
            <HistoryPage
              logs={logs}
              onClearLogs={() => setLogs([])}
              onExportCSV={handleExportCSV}
            />
          )}

          {activePage === 'devices' && (
            <DevicesPage
              telemetry={telemetry}
              connectionState={connectionState}
            />
          )}

          {activePage === 'settings' && (
            <SettingsPage
              isMuted={isMuted}
              onToggleMute={() => setIsMuted(!isMuted)}
              theme={theme}
              onToggleTheme={handleToggleTheme}
              currentStatus={telemetry.status}
            />
          )}
        </main>
      </div>
    </div>
  );
}
