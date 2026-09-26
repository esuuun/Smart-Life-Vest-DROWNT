import React from 'react';
import { 
  Heart, 
  Wind, 
  Droplets, 
  AlertTriangle, 
  ShieldCheck, 
  Waves
} from 'lucide-react';

export default function StatsBar({ telemetry }) {
  const isKritis = telemetry.status === 'KRITIS' || telemetry.isSubmerged;
  const isWaspada = telemetry.status === 'WASPADA' && !isKritis;

  const statusBadgeClass = isKritis 
    ? 'badge badge-crit' 
    : isWaspada 
    ? 'badge badge-warn' 
    : 'badge badge-safe';

  // Warna aksen untuk SpO2
  const spo2Color = telemetry.spo2 < 85 
    ? 'var(--status-crit-bright)' 
    : telemetry.spo2 < 92 
    ? 'var(--status-warn)' 
    : 'var(--accent-mint)';

  const waistPct = telemetry.waistWater || 0;
  const neckPct = telemetry.neckWater || 0;
  const isSubmerged = telemetry.isSubmerged || (waistPct > 50 && neckPct > 50);

  return (
    <div style={{
      display: 'grid',
      gridTemplateColumns: 'repeat(auto-fit, minmax(260px, 1fr))',
      gap: '1rem'
    }}>
      {/* 1. DROWNING STATUS & RISK SCORE */}
      <div className="card" style={{
        borderColor: isKritis ? 'var(--status-crit-border)' : isWaspada ? 'var(--status-warn-border)' : 'var(--border-subtle)',
        boxShadow: isKritis ? 'var(--shadow-glow-crit)' : 'var(--shadow-sm)'
      }}>
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.5rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            Drowning Risk Level
          </span>
          <span className={statusBadgeClass}>
            {isKritis ? <AlertTriangle size={12} /> : <ShieldCheck size={12} />}
            {isKritis ? 'KRITIS' : telemetry.status}
          </span>
        </div>

        <div style={{ display: 'flex', alignItems: 'baseline', gap: '0.5rem' }}>
          <span className="font-mono" style={{
            fontSize: '1.85rem',
            fontWeight: 700,
            color: isKritis ? 'var(--status-crit-bright)' : isWaspada ? 'var(--status-warn)' : 'var(--accent-mint)'
          }}>
            {telemetry.riskScore}%
          </span>
          <span style={{ fontSize: '0.8rem', color: 'var(--text-muted)' }}>Index Bahaya</span>
        </div>

        {/* Progress Bar */}
        <div style={{
          width: '100%',
          height: '6px',
          background: 'var(--border-subtle)',
          borderRadius: '3px',
          marginTop: '0.65rem',
          overflow: 'hidden'
        }}>
          <div style={{
            width: `${Math.min(100, Math.max(5, telemetry.riskScore))}%`,
            height: '100%',
            background: isKritis ? 'var(--status-crit)' : isWaspada ? 'var(--status-warn)' : 'var(--primary-emerald)',
            transition: 'width 0.4s ease, background-color 0.3s ease'
          }} />
        </div>
      </div>

      {/* 2. SpO2 OXYGEN SATURATION */}
      <div className="card">
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.5rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            Oxygen (SpO2)
          </span>
          <Wind size={16} color="var(--primary-sage)" />
        </div>

        <div style={{ display: 'flex', alignItems: 'baseline', gap: '0.35rem' }}>
          <span className="font-mono" style={{ fontSize: '1.85rem', fontWeight: 700, color: telemetry.spo2 === 0 ? 'var(--text-muted)' : spo2Color }}>
            {telemetry.spo2 === 0 ? '--' : telemetry.spo2}
          </span>
          <span style={{ fontSize: '1rem', fontWeight: 600, color: 'var(--text-muted)' }}>%</span>
        </div>

        <p style={{ fontSize: '0.75rem', color: telemetry.spo2 === 0 ? 'var(--text-muted)' : telemetry.spo2 < 88 ? 'var(--status-crit-bright)' : 'var(--primary-sage)', marginTop: '0.35rem' }}>
          {telemetry.spo2 === 0 ? 'Menunggu Jari Menempel...' : telemetry.spo2 >= 95 ? 'Normal Perfusion' : telemetry.spo2 >= 90 ? 'Mild Hypoxia' : 'Critical Hypoxia Alert'}
        </p>
      </div>

      {/* 3. HEART RATE */}
      <div className="card">
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.5rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            Heart Rate (PPG)
          </span>
          <Heart size={16} color="var(--primary-sage)" style={{ animation: telemetry.heartRate > 0 ? 'pulse-radar 1.2s infinite' : 'none' }} />
        </div>

        <div style={{ display: 'flex', alignItems: 'baseline', gap: '0.35rem' }}>
          <span className="font-mono" style={{ fontSize: '1.85rem', fontWeight: 700, color: telemetry.heartRate === 0 ? 'var(--text-muted)' : 'var(--text-primary)' }}>
            {telemetry.heartRate === 0 ? '--' : telemetry.heartRate}
          </span>
          <span style={{ fontSize: '0.8rem', color: 'var(--text-muted)' }}>BPM</span>
        </div>

        <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.35rem' }}>
          {telemetry.heartRate === 0 ? 'Mencari Denyut Nadi...' : telemetry.heartRate > 120 ? 'Tachycardia (Stress)' : telemetry.heartRate < 50 ? 'Bradycardia (Submersion)' : 'Sinus Rhythm Normal'}
        </p>
      </div>

      {/* 4. DUAL WATER DETECTION (PINGGANG & LEHER) */}
      <div className="card" style={{
        borderColor: isSubmerged ? 'var(--status-crit-border)' : waistPct > 30 ? 'var(--status-warn-border)' : 'var(--border-subtle)',
        boxShadow: isSubmerged ? 'var(--shadow-glow-crit)' : 'var(--shadow-sm)'
      }}>
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.4rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            Dual Water Sensors
          </span>
          <span className={`badge ${isSubmerged ? 'badge-crit' : waistPct > 30 ? 'badge-warn' : 'badge-neutral'}`} style={{ fontSize: '0.675rem' }}>
            <Droplets size={11} />
            {isSubmerged ? 'TENGGELAM TOTAL!' : waistPct > 30 ? 'Mengapung / Berenang' : 'Kering di Darat'}
          </span>
        </div>

        {/* Level Pinggang */}
        <div style={{ marginTop: '0.4rem' }}>
          <div style={{ display: 'flex', justifyContent: 'space-between', fontSize: '0.7rem', color: 'var(--text-secondary)', marginBottom: '0.2rem' }}>
            <span>Sensor Pinggang:</span>
            <strong className="font-mono" style={{ color: waistPct > 30 ? 'var(--status-warn)' : 'var(--text-muted)' }}>
              {waistPct}% ({waistPct > 30 ? 'Terendam Air' : 'Kering'})
            </strong>
          </div>
          <div style={{ width: '100%', height: '5px', background: 'var(--border-subtle)', borderRadius: '3px', overflow: 'hidden' }}>
            <div style={{ width: `${waistPct}%`, height: '100%', background: waistPct > 50 ? 'var(--status-crit-bright)' : waistPct > 20 ? 'var(--status-warn)' : 'var(--primary-emerald)', transition: 'width 0.3s' }} />
          </div>
        </div>

        {/* Level Leher */}
        <div style={{ marginTop: '0.5rem' }}>
          <div style={{ display: 'flex', justifyContent: 'space-between', fontSize: '0.7rem', color: 'var(--text-secondary)', marginBottom: '0.2rem' }}>
            <span>Sensor Leher:</span>
            <strong className="font-mono" style={{ color: neckPct > 30 ? 'var(--status-crit-bright)' : 'var(--text-muted)' }}>
              {neckPct}% ({neckPct > 30 ? 'BAHAYA TERENDAM' : 'Aman'})
            </strong>
          </div>
          <div style={{ width: '100%', height: '5px', background: 'var(--border-subtle)', borderRadius: '3px', overflow: 'hidden' }}>
            <div style={{ width: `${neckPct}%`, height: '100%', background: neckPct > 30 ? 'var(--status-crit-bright)' : 'var(--primary-emerald)', transition: 'width 0.3s' }} />
          </div>
        </div>
      </div>
    </div>
  );
}
