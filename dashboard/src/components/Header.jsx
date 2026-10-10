import React from 'react';
import { 
  Radio, 
  Usb, 
  Volume2, 
  VolumeX, 
  Download, 
  Play, 
  Square,
  ShieldAlert,
  Activity,
  Sun,
  Moon
} from 'lucide-react';

export default function Header({
  connectionState,
  onConnectSerial,
  onDisconnectSerial,
  onConnectBLE,
  onDisconnectBLE,
  isSimulatorActive,
  onToggleSimulator,
  isMuted,
  onToggleMute,
  onExportCSV,
  currentStatus,
  packetCount,
  theme,
  onToggleTheme
}) {
  return (
    <header style={{
      background: 'var(--bg-surface)',
      borderBottom: '1px solid var(--border-subtle)',
      padding: '0.85rem 1.5rem',
      display: 'flex',
      alignItems: 'center',
      justifyContent: 'space-between',
      position: 'sticky',
      top: 0,
      zIndex: 1000
    }}>
      {/* Brand Identity */}
      <div style={{ display: 'flex', alignItems: 'center', gap: '1rem' }}>
        <div style={{
          width: '38px',
          height: '38px',
          borderRadius: 'var(--radius-sm)',
          background: 'linear-gradient(135deg, var(--primary-deep), var(--primary-emerald))',
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'center',
          border: '1px solid var(--primary-sage)',
          boxShadow: 'var(--shadow-sm)'
        }}>
          <ShieldAlert size={22} color="#EEF7F1" />
        </div>

        <div>
          <div style={{ display: 'flex', alignItems: 'center', gap: '0.6rem' }}>
            <h1 style={{
              fontSize: '1.05rem',
              fontWeight: 800,
              letterSpacing: '0.04em',
              color: 'var(--text-primary)'
            }}>
              DROWNT
            </h1>
            <span style={{
              fontSize: '0.675rem',
              fontWeight: 700,
              padding: '0.15rem 0.45rem',
              borderRadius: '4px',
              background: 'var(--accent-mint-soft)',
              color: 'var(--accent-mint)',
              border: '1px solid var(--status-safe-border)',
              letterSpacing: '0.06em'
            }}>
              EDGE AI SAR
            </span>
          </div>
          <p style={{
            fontSize: '0.725rem',
            color: 'var(--text-muted)',
            fontWeight: 500,
            marginTop: '2px'
          }}>
            Tactical Lifesaving Telemetry &bull; FTUI Kelompok 33
          </p>
        </div>
      </div>

      {/* Center Operational Badge */}
      <div style={{ display: 'flex', alignItems: 'center', gap: '1.25rem' }}>
        <div style={{
          display: 'flex',
          alignItems: 'center',
          gap: '0.5rem',
          padding: '0.35rem 0.85rem',
          borderRadius: 'var(--radius-sm)',
          background: 'var(--bg-app)',
          border: '1px solid var(--border-subtle)',
          fontSize: '0.75rem'
        }}>
          <span style={{
            width: '8px',
            height: '8px',
            borderRadius: '50%',
            background: connectionState.connected ? 'var(--primary-sage)' : isSimulatorActive ? '#D9822B' : 'var(--text-muted)',
            boxShadow: (connectionState.connected || isSimulatorActive) ? '0 0 8px currentColor' : 'none'
          }} />
          <span style={{ color: 'var(--text-secondary)' }}>
            Source: <strong style={{ color: 'var(--text-primary)' }}>
              {connectionState.connected ? 'ESP32-S3 (USB)' : isSimulatorActive ? 'SIMULATOR ACTIVE' : 'STANDBY'}
            </strong>
          </span>
          <span style={{ color: 'var(--border-medium)' }}>|</span>
          <span style={{ color: 'var(--text-muted)' }} className="font-mono">
            Packets: {packetCount}
          </span>
        </div>
      </div>

      {/* Controls / Actions */}
      <div style={{ display: 'flex', alignItems: 'center', gap: '0.65rem' }}>
        {/* Simulator Toggle */}
        <button
          onClick={onToggleSimulator}
          className={`btn ${isSimulatorActive ? 'btn-danger' : 'btn-outline'}`}
          title="Jalankan skenario simulasi tanpa hardware fisik"
        >
          {isSimulatorActive ? <Square size={15} /> : <Play size={15} />}
          <span>{isSimulatorActive ? 'Stop Sim' : 'Demo Simulator'}</span>
        </button>

        {/* Web Serial Connect (USB) */}
        {connectionState.connected && !connectionState.ble ? (
          <button onClick={onDisconnectSerial} className="btn btn-outline" style={{ borderColor: 'var(--status-crit-border)' }}>
            <Usb size={15} color="var(--status-crit-bright)" />
            <span>Putus USB</span>
          </button>
        ) : !connectionState.connected ? (
          <button onClick={onConnectSerial} className="btn btn-outline" title="Sambungkan lewat kabel data USB">
            <Usb size={15} />
            <span>USB</span>
          </button>
        ) : null}

        {/* Web Bluetooth Connect (BLE Wireless) */}
        {connectionState.connected && connectionState.ble ? (
          <button onClick={onDisconnectBLE} className="btn btn-outline" style={{ borderColor: 'var(--status-crit-border)' }}>
            <Radio size={15} color="var(--status-crit-bright)" />
            <span>Putus BLE</span>
          </button>
        ) : !connectionState.connected ? (
          <button onClick={onConnectBLE} className="btn btn-primary" title="Sambungkan nirkabel lewat Bluetooth (ESP32 colok power/laptop mana saja)">
            <Radio size={15} />
            <span>Bluetooth (BLE)</span>
          </button>
        ) : null}

        {/* Theme Toggle (Light / Dark) */}
        <button
          onClick={onToggleTheme}
          className="btn btn-outline"
          title={theme === 'dark' ? 'Ganti ke Light Mode' : 'Ganti ke Dark Mode'}
          style={{ padding: '0.55rem' }}
        >
          {theme === 'dark' ? <Sun size={16} color="#F5A623" /> : <Moon size={16} color="var(--primary-deep)" />}
        </button>

        {/* Mute Audio Alarm */}
        <button
          onClick={onToggleMute}
          className="btn btn-outline"
          title={isMuted ? 'Nyalakan suara alarm sirine' : 'Bisukan suara alarm'}
          style={{ padding: '0.55rem' }}
        >
          {isMuted ? <VolumeX size={16} color="var(--text-muted)" /> : <Volume2 size={16} color="var(--primary-emerald)" />}
        </button>

        {/* Export Flight Log CSV */}
        <button
          onClick={onExportCSV}
          className="btn btn-outline"
          title="Export seluruh log telemetri ke file CSV"
        >
          <Download size={15} />
          <span>Export CSV</span>
        </button>
      </div>
    </header>
  );
}
