import React from 'react';
import { PlayCircle, AlertCircle, AlertOctagon, CheckCircle2 } from 'lucide-react';

export default function SimulatorControls({ currentScenario, onSelectScenario }) {
  const scenarios = [
    {
      id: 'NORMAL',
      label: '1. Berenang Normal (Aman)',
      desc: 'SpO2 98%, HR 75, Dek Kering/Berenang Telentang',
      color: 'var(--status-safe)',
      icon: <CheckCircle2 size={16} color="var(--accent-mint)" />
    },
    {
      id: 'WASPADA',
      label: '2. Tercebur / Immersion (Waspada)',
      desc: 'SpO2 92%, HR 110 (Stres Takikardia), Sensor Air Aktif',
      color: 'var(--status-warn)',
      icon: <AlertCircle size={16} color="var(--status-warn)" />
    },
    {
      id: 'KRITIS_HYPOXIA',
      label: '3. Tenggelam Akut & Hipoksia (Kritis)',
      desc: 'SpO2 78%, HR 145, Suhu 32.8°C (Hipotermia Ringan)',
      color: 'var(--status-crit-bright)',
      icon: <AlertOctagon size={16} color="var(--status-crit-bright)" />
    },
    {
      id: 'KRITIS_FACEDOWN',
      label: '4. Korban Pingsan Telungkup (Kritis Ekstrem)',
      desc: 'Wajah Menghadap Air (Face-Down), SpO2 70%, HR 45 (Near-Drowning)',
      color: 'var(--status-crit-bright)',
      icon: <AlertOctagon size={16} color="var(--status-crit-bright)" />
    },
  ];

  return (
    <div className="card" style={{
      background: 'var(--bg-surface-elevated)',
      border: '1px solid var(--border-medium)',
      padding: '1rem 1.25rem'
    }}>
      <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: '0.75rem' }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
          <PlayCircle size={17} color="#D9822B" />
          <strong style={{ fontSize: '0.8rem', textTransform: 'uppercase', letterSpacing: '0.05em', color: 'var(--text-primary)' }}>
            SAR Test Scenario Generator (Demo Sidang Mode)
          </strong>
        </div>
        <span style={{ fontSize: '0.7rem', color: 'var(--text-muted)' }}>
          Pilih skenario simulasi tanpa hardware
        </span>
      </div>

      <div style={{
        display: 'grid',
        gridTemplateColumns: 'repeat(auto-fit, minmax(240px, 1fr))',
        gap: '0.65rem'
      }}>
        {scenarios.map((sc) => {
          const isSelected = currentScenario === sc.id;
          return (
            <button
              key={sc.id}
              onClick={() => onSelectScenario(sc.id)}
              className="btn btn-outline"
              style={{
                display: 'flex',
                alignItems: 'flex-start',
                textAlign: 'left',
                gap: '0.65rem',
                padding: '0.65rem 0.85rem',
                borderColor: isSelected ? sc.color : 'var(--border-subtle)',
                background: isSelected ? 'rgba(40, 134, 97, 0.12)' : 'var(--bg-app)',
                boxShadow: isSelected ? 'var(--shadow-glow-safe)' : 'none'
              }}
            >
              <div style={{ marginTop: '2px' }}>{sc.icon}</div>
              <div>
                <strong style={{ display: 'block', fontSize: '0.75rem', color: isSelected ? 'var(--text-primary)' : 'var(--text-secondary)' }}>
                  {sc.label}
                </strong>
                <span style={{ fontSize: '0.675rem', color: 'var(--text-muted)' }}>
                  {sc.desc}
                </span>
              </div>
            </button>
          );
        })}
      </div>
    </div>
  );
}
