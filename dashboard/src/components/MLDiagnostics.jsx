import React from 'react';
import { Cpu, Compass, BellRing, Flame, ShieldAlert } from 'lucide-react';

export default function MLDiagnostics({ telemetry }) {
  const pAman = Math.round((telemetry.probAman || 0) * 100);
  const pWaspada = Math.round((telemetry.probWaspada || 0) * 100);
  const pKritis = Math.round((telemetry.probKritis || 0) * 100);

  const isKritis = telemetry.status === 'KRITIS';
  const isWaspada = telemetry.status === 'WASPADA';

  return (
    <div className="card" style={{ display: 'flex', flexDirection: 'column', gap: '1rem' }}>
      <div className="card-header" style={{ marginBottom: '0.25rem' }}>
        <span className="card-title">
          <Cpu size={16} color="var(--primary-sage)" />
          Edge AI Inference (TinyML Random Forest)
        </span>
        <span style={{ fontSize: '0.7rem', color: 'var(--text-muted)' }} className="font-mono">
          On-Device ESP32-S3
        </span>
      </div>

      {/* Probability Bars */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: '0.65rem' }}>
        {/* P(AMAN) */}
        <div>
          <div style={{ display: 'flex', justifyContent: 'space-between', fontSize: '0.75rem', marginBottom: '0.25rem' }}>
            <span style={{ color: 'var(--text-secondary)' }}>Kelas 0: AMAN (Safe)</span>
            <span className="font-mono" style={{ color: 'var(--accent-mint)', fontWeight: 600 }}>{pAman}%</span>
          </div>
          <div style={{ width: '100%', height: '6px', background: 'var(--border-subtle)', borderRadius: '3px', overflow: 'hidden' }}>
            <div style={{ width: `${pAman}%`, height: '100%', background: 'var(--primary-emerald)', transition: 'width 0.3s' }} />
          </div>
        </div>

        {/* P(WASPADA) */}
        <div>
          <div style={{ display: 'flex', justifyContent: 'space-between', fontSize: '0.75rem', marginBottom: '0.25rem' }}>
            <span style={{ color: 'var(--text-secondary)' }}>Kelas 1: WASPADA (Warning)</span>
            <span className="font-mono" style={{ color: 'var(--status-warn)', fontWeight: 600 }}>{pWaspada}%</span>
          </div>
          <div style={{ width: '100%', height: '6px', background: 'var(--border-subtle)', borderRadius: '3px', overflow: 'hidden' }}>
            <div style={{ width: `${pWaspada}%`, height: '100%', background: 'var(--status-warn)', transition: 'width 0.3s' }} />
          </div>
        </div>

        {/* P(KRITIS) */}
        <div>
          <div style={{ display: 'flex', justifyContent: 'space-between', fontSize: '0.75rem', marginBottom: '0.25rem' }}>
            <span style={{ color: 'var(--text-secondary)' }}>Kelas 2: KRITIS (Drowning)</span>
            <span className="font-mono" style={{ color: 'var(--status-crit-bright)', fontWeight: 600 }}>{pKritis}%</span>
          </div>
          <div style={{ width: '100%', height: '6px', background: 'var(--border-subtle)', borderRadius: '3px', overflow: 'hidden' }}>
            <div style={{ width: `${pKritis}%`, height: '100%', background: 'var(--status-crit)', transition: 'width 0.3s' }} />
          </div>
        </div>
      </div>

      {/* Actuator & Safety Trigger Status */}
      <div style={{
        marginTop: '0.25rem',
        padding: '0.75rem',
        background: 'var(--bg-app)',
        border: '1px solid var(--border-subtle)',
        borderRadius: 'var(--radius-sm)',
        display: 'grid',
        gridTemplateColumns: '1fr 1fr',
        gap: '0.75rem'
      }}>
        {/* Buzzer Alarm Status */}
        <div>
          <span style={{ fontSize: '0.7rem', color: 'var(--text-muted)', display: 'block', marginBottom: '0.2rem' }}>
            Audible Buzzer
          </span>
          <div style={{ display: 'flex', alignItems: 'center', gap: '0.4rem' }}>
            <BellRing size={14} color={isKritis ? 'var(--status-crit-bright)' : isWaspada ? 'var(--status-warn)' : 'var(--text-muted)'} />
            <strong style={{
              fontSize: '0.75rem',
              color: isKritis ? 'var(--status-crit-bright)' : isWaspada ? 'var(--status-warn)' : 'var(--text-secondary)'
            }}>
              {isKritis ? 'SIREN 100dB' : isWaspada ? 'PULSE BEEP' : 'SILENT'}
            </strong>
          </div>
        </div>

        {/* Solenoid Inflation Trigger */}
        <div>
          <span style={{ fontSize: '0.7rem', color: 'var(--text-muted)', display: 'block', marginBottom: '0.2rem' }}>
            Auto-Inflation Valve
          </span>
          <div style={{ display: 'flex', alignItems: 'center', gap: '0.4rem' }}>
            <Flame size={14} color={isKritis ? 'var(--status-crit-bright)' : 'var(--text-muted)'} />
            <strong style={{
              fontSize: '0.75rem',
              color: isKritis ? 'var(--status-crit-bright)' : 'var(--text-secondary)'
            }}>
              {isKritis ? 'CO2 TRIGGERED' : 'ARMED / STANDBY'}
            </strong>
          </div>
        </div>
      </div>

      {/* Model Spec Note */}
      <div style={{ fontSize: '0.7rem', color: 'var(--text-muted)', lineHeight: 1.4 }}>
        Architecture: <strong>RandomForest(n=15, depth=8)</strong> compiled via m2cgen transpiler into zero-overhead C memory footprint.
      </div>
    </div>
  );
}
