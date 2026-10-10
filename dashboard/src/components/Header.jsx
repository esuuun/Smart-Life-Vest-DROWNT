import React from 'react';
import {
  Menu,
  Radio,
  Usb,
  Bluetooth,
  Volume2,
  VolumeX,
  Download,
  Play,
  Square,
  Sun,
  Moon,
  AlertTriangle,
  ChevronRight,
  ShieldAlert
} from 'lucide-react';

export default function Header({
  activePage,
  onToggleMobileSidebar,
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
  const isKritis = currentStatus === 'KRITIS';
  const isWaspada = currentStatus === 'WASPADA';

  const pageNames = {
    overview: 'Mission Overview',
    reports: 'SAR Incident Report',
    history: 'Telemetry History & Records',
    devices: 'Hardware & Sensor Diagnostics',
    settings: 'System & SAR Settings',
  };

  const currentPageTitle = pageNames[activePage] || 'Command Center';

  return (
    <>
      {/* Top Banner Critical Emergency Alert (if victim is submerged) */}
      {isKritis && (
        <div className="emergency-alert-banner">
          <div className="banner-content">
            <AlertTriangle size={18} className="banner-alert-icon" />
            <span className="banner-text">
              <strong>PERINGATAN KRITIS:</strong> KORBAN TENGGELAM TERDETEKSI! SENSOR AIR LEHER AKTIF & DESATURASI HIPOKSIA!
            </span>
          </div>
        </div>
      )}

      <header className="topbar-container">
        {/* Left Section: Mobile Menu Trigger + Breadcrumb */}
        <div className="topbar-left">
          <button
            className="mobile-menu-btn"
            onClick={onToggleMobileSidebar}
            aria-label="Buka Menu Navigasi"
          >
            <Menu size={20} />
          </button>

          <div className="topbar-breadcrumb">
            <span className="breadcrumb-root">DROWNT SAR</span>
            <ChevronRight size={14} className="breadcrumb-sep" />
            <span className="breadcrumb-current">{currentPageTitle}</span>
          </div>
        </div>

        {/* Center: Live Source & Packet Status Indicator */}
        <div className="topbar-center">
          <div className="connection-pill">
            <span
              className={`connection-dot ${
                connectionState.connected
                  ? 'dot-live'
                  : isSimulatorActive
                  ? 'dot-sim'
                  : 'dot-idle'
              }`}
            />
            <span className="connection-source-text">
              {connectionState.connected
                ? connectionState.ble
                  ? 'ESP32 BLE Wireless'
                  : 'ESP32 USB Serial'
                : isSimulatorActive
                ? 'SAR SIMULATOR'
                : 'OFFLINE / STANDBY'}
            </span>
            <span className="connection-divider">|</span>
            <span className="connection-packets font-mono">
              {packetCount} pkts
            </span>
          </div>
        </div>

        {/* Right Section: Quick Action Controls */}
        <div className="topbar-right">
          {/* Simulator Toggle */}
          <button
            onClick={onToggleSimulator}
            className={`btn-action ${isSimulatorActive ? 'btn-active-sim' : 'btn-subtle'}`}
            title="Nyalakan/matikan generator skenario darurat"
          >
            {isSimulatorActive ? <Square size={15} /> : <Play size={15} />}
            <span className="btn-label">{isSimulatorActive ? 'Stop Sim' : 'Demo Sim'}</span>
          </button>

          {/* Web Serial (USB) */}
          {connectionState.connected && !connectionState.ble ? (
            <button
              onClick={onDisconnectSerial}
              className="btn-action btn-danger-subtle"
              title="Putus koneksi USB Serial"
            >
              <Usb size={15} />
              <span className="btn-label">Putus USB</span>
            </button>
          ) : !connectionState.connected ? (
            <button
              onClick={onConnectSerial}
              className="btn-action btn-subtle"
              title="Hubungkan via kabel USB"
            >
              <Usb size={15} />
              <span className="btn-label">USB</span>
            </button>
          ) : null}

          {/* Web Bluetooth (BLE) */}
          {connectionState.connected && connectionState.ble ? (
            <button
              onClick={onDisconnectBLE}
              className="btn-action btn-danger-subtle"
              title="Putus koneksi Bluetooth BLE"
            >
              <Bluetooth size={15} />
              <span className="btn-label">Putus BLE</span>
            </button>
          ) : !connectionState.connected ? (
            <button
              onClick={onConnectBLE}
              className="btn-action btn-subtle"
              title="Hubungkan tanpa kabel lewat Bluetooth BLE"
            >
              <Bluetooth size={15} />
              <span className="btn-label">BLE</span>
            </button>
          ) : null}

          {/* Audio Alarm Siren Mute Toggle */}
          <button
            onClick={onToggleMute}
            className={`btn-icon ${isMuted ? 'icon-muted' : 'icon-active'}`}
            title={isMuted ? 'Bunyikan Alarm Sirine' : 'Bisukan Alarm Sirine'}
            aria-label="Toggle Audio Alarm"
          >
            {!isMuted ? <Volume2 size={16} /> : <VolumeX size={16} />}
          </button>

          {/* Theme Toggle */}
          <button
            onClick={onToggleTheme}
            className="btn-icon btn-theme"
            title={`Ganti ke mode ${theme === 'dark' ? 'terang' : 'gelap'}`}
            aria-label="Toggle Dark/Light Mode"
          >
            {theme === 'dark' ? <Sun size={16} /> : <Moon size={16} />}
          </button>

          {/* Quick Export CSV */}
          <button
            onClick={onExportCSV}
            className="btn-icon btn-export"
            title="Download Rekaman Telemetri CSV"
            aria-label="Export CSV"
          >
            <Download size={16} />
          </button>
        </div>
      </header>
    </>
  );
}
