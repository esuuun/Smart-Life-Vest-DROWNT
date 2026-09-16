import React from 'react';
import { 
  Heart, 
  Wind, 
  Thermometer, 
  Droplets, 
  AlertTriangle, 
  ShieldCheck, 
  Rotate3d
} from 'lucide-react';

export default function StatsBar({ telemetry }) {
  const isKritis = telemetry.status === 'KRITIS';
  const isWaspada = telemetry.status === 'WASPADA';

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

  // Warna aksen untuk Suhu Tubuh
  const tempColor = telemetry.temperature < 33.0 
    ? 'var(--status-crit-bright)' 
    : telemetry.temperature < 35.0 
    ? 'var(--status-warn)' 
    : 'var(--text-primary)';

  return (
    <div style={{
      display: 'grid',
      gridTemplateColumns: 'repeat(auto-fit, minmax(220px, 1fr))',
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
            {telemetry.status}
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
          <span className="font-mono" style={{ fontSize: '1.85rem', fontWeight: 700, color: spo2Color }}>
            {telemetry.spo2}
          </span>
          <span style={{ fontSize: '1rem', fontWeight: 600, color: 'var(--text-muted)' }}>%</span>
        </div>

        <p style={{ fontSize: '0.75rem', color: telemetry.spo2 < 88 ? 'var(--status-crit-bright)' : 'var(--text-muted)', marginTop: '0.35rem' }}>
          {telemetry.spo2 >= 95 ? 'Normal Perfusion' : telemetry.spo2 >= 90 ? 'Mild Hypoxia' : 'Critical Hypoxia Alert'}
        </p>
      </div>

      {/* 3. HEART RATE */}
      <div className="card">
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.5rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            Heart Rate (PPG)
          </span>
          <Heart size={16} color="var(--primary-sage)" style={{ animation: 'pulse-radar 1.2s infinite' }} />
        </div>

        <div style={{ display: 'flex', alignItems: 'baseline', gap: '0.35rem' }}>
          <span className="font-mono" style={{ fontSize: '1.85rem', fontWeight: 700, color: 'var(--text-primary)' }}>
            {telemetry.heartRate}
          </span>
          <span style={{ fontSize: '0.8rem', color: 'var(--text-muted)' }}>BPM</span>
        </div>

        <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.35rem' }}>
          {telemetry.heartRate > 120 ? 'Tachycardia (Stress)' : telemetry.heartRate < 50 ? 'Bradycardia (Submersion)' : 'Sinus Rhythm Normal'}
        </p>
      </div>

      {/* 4. CORE TEMPERATURE */}
      <div className="card">
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.5rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            Core Temperature
          </span>
          <Thermometer size={16} color="var(--primary-sage)" />
        </div>

        <div style={{ display: 'flex', alignItems: 'baseline', gap: '0.35rem' }}>
          <span className="font-mono" style={{ fontSize: '1.85rem', fontWeight: 700, color: tempColor }}>
            {Number(telemetry.temperature).toFixed(1)}
          </span>
          <span style={{ fontSize: '1rem', fontWeight: 600, color: 'var(--text-muted)' }}>&deg;C</span>
        </div>

        <p style={{ fontSize: '0.75rem', color: telemetry.temperature < 34 ? 'var(--status-crit-bright)' : 'var(--text-muted)', marginTop: '0.35rem' }}>
          {telemetry.temperature >= 36 ? 'Normothermia' : telemetry.temperature >= 34 ? 'Mild Hypothermia' : 'Severe Hypothermia Risk'}
        </p>
      </div>

      {/* 5. WATER & ORIENTATION POSTURE */}
      <div className="card">
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.5rem' }}>
          <span style={{ fontSize: '0.75rem', fontWeight: 600, color: 'var(--text-muted)', textTransform: 'uppercase', letterSpacing: '0.05em' }}>
            State & Posture
          </span>
          <Rotate3d size={16} color="var(--primary-sage)" />
        </div>

        <div style={{ display: 'flex', gap: '0.5rem', marginTop: '0.25rem' }}>
          <span className={`badge ${telemetry.inWater ? 'badge-warn' : 'badge-neutral'}`} style={{ fontSize: '0.7rem' }}>
            <Droplets size={12} />
            {telemetry.inWater ? 'Submerged' : 'Dry Deck'}
          </span>

          <span className={`badge ${telemetry.isFaceDown ? 'badge-crit' : 'badge-safe'}`} style={{ fontSize: '0.7rem' }}>
            {telemetry.isFaceDown ? 'Face-Down Danger' : 'Face-Up Safe'}
          </span>
        </div>

        <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.65rem' }}>
          Pitch: <span className="font-mono">{telemetry.pitch}&deg;</span> &bull; Roll: <span className="font-mono">{telemetry.roll}&deg;</span>
        </p>
      </div>
    </div>
  );
}
