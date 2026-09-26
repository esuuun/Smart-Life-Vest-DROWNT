import React, { useState } from 'react';
import { Terminal, Filter, Trash2 } from 'lucide-react';

export default function TelemetryLog({ logs, onClearLogs }) {
  const [filterCriticalOnly, setFilterCriticalOnly] = useState(false);

  const displayedLogs = filterCriticalOnly 
    ? logs.filter(l => l.status === 'KRITIS' || l.status === 'WASPADA')
    : logs;

  return (
    <div className="card" style={{ display: 'flex', flexDirection: 'column', height: '100%' }}>
      <div className="card-header">
        <span className="card-title">
          <Terminal size={16} color="var(--primary-sage)" />
          Real-Time LoRa / Serial Stream
        </span>

        <div style={{ display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
          <button
            onClick={() => setFilterCriticalOnly(!filterCriticalOnly)}
            className={`btn ${filterCriticalOnly ? 'btn-danger' : 'btn-outline'}`}
            style={{ padding: '0.25rem 0.6rem', fontSize: '0.7rem' }}
          >
            <Filter size={12} />
            <span>{filterCriticalOnly ? 'Filtered: Warn/Crit' : 'Filter: All'}</span>
          </button>

          <button
            onClick={onClearLogs}
            className="btn btn-outline"
            style={{ padding: '0.25rem 0.5rem', fontSize: '0.7rem' }}
            title="Bersihkan log riwayat"
          >
            <Trash2 size={12} />
          </button>
        </div>
      </div>

      {/* Terminal Log Area */}
      <div style={{
        flex: 1,
        maxHeight: '220px',
        overflowY: 'auto',
        background: 'var(--bg-app)',
        borderRadius: 'var(--radius-sm)',
        border: '1px solid var(--border-subtle)',
        padding: '0.65rem 0.85rem',
        fontSize: '0.725rem',
        lineHeight: 1.6
      }} className="font-mono">
        {displayedLogs.length === 0 ? (
          <div style={{ color: 'var(--text-muted)', textAlign: 'center', padding: '1.5rem 0' }}>
            Menunggu data telemetri dari ESP32 atau Simulator...
          </div>
        ) : (
          displayedLogs.slice(-40).reverse().map((entry, idx) => {
            const isCrit = entry.status === 'KRITIS';
            const isWarn = entry.status === 'WASPADA';
            const color = isCrit ? 'var(--status-crit-bright)' : isWarn ? 'var(--status-warn)' : 'var(--accent-mint)';

            return (
              <div
                key={idx}
                style={{
                  display: 'flex',
                  gap: '0.65rem',
                  borderBottom: '1px solid rgba(28, 43, 34, 0.4)',
                  padding: '0.25rem 0',
                  color: 'var(--text-secondary)'
                }}
              >
                <span style={{ color: 'var(--text-muted)' }}>[{entry.timestamp}]</span>
                <span style={{ color: 'var(--text-primary)', fontWeight: 600 }}>#{entry.seq}</span>
                <span style={{ color, fontWeight: 700 }}>{entry.status}</span>
                <span>SpO2:{entry.spo2 > 0 ? `${entry.spo2}%` : '--'}</span>
                <span>HR:{entry.heartRate > 0 ? entry.heartRate : '--'}</span>
                <span>Pinggang:{entry.waistWater ?? 0}%</span>
                <span>Leher:{entry.neckWater ?? 0}%</span>
                <span style={{ color: 'var(--text-muted)', marginLeft: 'auto' }}>
                  {entry.latitude.toFixed(4)}, {entry.longitude.toFixed(4)}
                </span>
              </div>
            );
          })
        )}
      </div>
    </div>
  );
}
