import React from 'react';
import {
  LayoutDashboard,
  FileText,
  History,
  Cpu,
  Settings,
  ShieldAlert,
  ChevronLeft,
  ChevronRight,
  Radio,
  Wifi,
  WifiOff,
  Activity,
  Heart
} from 'lucide-react';

export default function Sidebar({
  activePage,
  setActivePage,
  isCollapsed,
  setIsCollapsed,
  connectionState,
  currentStatus,
  packetCount,
  isMobileOpen,
  setIsMobileOpen
}) {
  const navItems = [
    { id: 'overview', label: 'Overview', icon: LayoutDashboard, badge: null },
    { id: 'reports', label: 'SAR Incident Report', icon: FileText, badge: currentStatus === 'KRITIS' ? 'ALERT' : null },
    { id: 'history', label: 'Telemetry History', icon: History, badge: packetCount > 0 ? packetCount : null },
    { id: 'devices', label: 'Hardware & Sensors', icon: Cpu, badge: connectionState?.connected ? 'ONLINE' : null },
    { id: 'settings', label: 'SAR Settings', icon: Settings, badge: null },
  ];

  const handleNavClick = (id) => {
    setActivePage(id);
    if (setIsMobileOpen) {
      setIsMobileOpen(false);
    }
  };

  const isConnected = connectionState?.connected;
  const isKritis = currentStatus === 'KRITIS';
  const isWaspada = currentStatus === 'WASPADA';

  return (
    <>
      {/* Mobile Backdrop Overlay */}
      {isMobileOpen && (
        <div
          className="sidebar-backdrop"
          onClick={() => setIsMobileOpen(false)}
        />
      )}

      <aside className={`sidebar-container ${isCollapsed ? 'collapsed' : ''} ${isMobileOpen ? 'mobile-open' : ''}`}>
        {/* Sidebar Header Brand */}
        <div className="sidebar-header">
          <div className="sidebar-brand" onClick={() => handleNavClick('overview')}>
            <div className={`brand-icon ${isKritis ? 'brand-crit' : isWaspada ? 'brand-warn' : ''}`}>
              <ShieldAlert size={22} color="#FFFFFF" />
            </div>
            {!isCollapsed && (
              <div className="brand-text">
                <div className="brand-title">DROWNT</div>
                <div className="brand-subtitle">EDGE AI SAR TELEMETRY</div>
              </div>
            )}
          </div>
          
          <button
            className="collapse-toggle-btn"
            onClick={() => setIsCollapsed(!isCollapsed)}
            title={isCollapsed ? 'Perluas Sidebar' : 'Ciutkan Sidebar'}
            aria-label="Toggle Sidebar"
          >
            {isCollapsed ? <ChevronRight size={16} /> : <ChevronLeft size={16} />}
          </button>
        </div>

        {/* Real-time Status Card (Visible when expanded) */}
        {!isCollapsed && (
          <div className="sidebar-status-card">
            <div className="status-header">
              <span className="status-label">KORBAN STATUS</span>
              <span className={`status-badge-mini ${isKritis ? 'badge-crit' : isWaspada ? 'badge-warn' : 'badge-safe'}`}>
                {currentStatus || 'AMAN'}
              </span>
            </div>
            <div className="status-footer">
              <span className="pulse-indicator">
                <span className={`ping-dot ${isConnected ? 'dot-active' : ''}`} />
                <span className="source-label">
                  {isConnected ? (connectionState.ble ? 'BLE 4.2' : 'USB Serial') : 'Standby / Offline'}
                </span>
              </span>
              <span className="packet-counter font-mono">{packetCount} pkts</span>
            </div>
          </div>
        )}

        {/* Navigation Items */}
        <nav className="sidebar-nav">
          <div className="nav-group-label">{!isCollapsed ? 'MENU UTAMA' : '•••'}</div>
          {navItems.map((item) => {
            const Icon = item.icon;
            const isActive = activePage === item.id;
            return (
              <button
                key={item.id}
                className={`nav-item ${isActive ? 'active' : ''}`}
                onClick={() => handleNavClick(item.id)}
                title={isCollapsed ? item.label : undefined}
              >
                <div className="nav-icon-wrapper">
                  <Icon size={19} className="nav-icon" />
                </div>
                {!isCollapsed && (
                  <span className="nav-label">{item.label}</span>
                )}
                {!isCollapsed && item.badge && (
                  <span className={`nav-badge ${item.badge === 'ALERT' ? 'badge-alert' : item.badge === 'ONLINE' ? 'badge-online' : ''}`}>
                    {item.badge}
                  </span>
                )}
              </button>
            );
          })}
        </nav>

        {/* Sidebar Footer Link / System Info */}
        <div className="sidebar-footer">
          {!isCollapsed ? (
            <div className="footer-system-info">
              <div className="info-title">FTUI Kelompok 33</div>
              <div className="info-desc">Despro 2 • Teknik Komputer</div>
              <div className="system-pill">
                <Radio size={12} />
                <span>TinyML On-Device RF-10</span>
              </div>
            </div>
          ) : (
            <div className="footer-collapsed-dot" title="DROWNT SAR System Active">
              <Activity size={16} color="var(--primary-emerald)" />
            </div>
          )}
        </div>
      </aside>
    </>
  );
}
