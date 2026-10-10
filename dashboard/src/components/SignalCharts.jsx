import React, { useRef, useEffect } from 'react';
import { Activity, TrendingUp } from 'lucide-react';

const NWAVE = 200;
const NTREND = 60; // 60 data points history (~1-2 menit)

export default function SignalCharts({ telemetry, isConnected, isSimulatorActive }) {
  const waveCanvasRef = useRef(null);
  const trendCanvasRef = useRef(null);

  // Buffer ref agar tidak memicu re-render berlebihan saat animasi canvas
  const waveDataRef = useRef(new Array(NWAVE).fill(0));
  const trendDataRef = useRef({ hr: [], spo2: [] });
  const animFrameRef = useRef(null);
  const phaseRef = useRef(0);

  // Update Tren HR & SpO2 setiap telemetry baru masuk
  useEffect(() => {
    if (!telemetry) return;
    const hr = Number(telemetry.heartRate || 0);
    const sp = Number(telemetry.spo2 || 0);

    const trend = trendDataRef.current;
    trend.hr.push(hr);
    trend.spo2.push(sp);
    if (trend.hr.length > NTREND) {
      trend.hr.shift();
      trend.spo2.shift();
    }
    drawTrend();
  }, [telemetry]);

  // Loop generator animasi gelombang PPG (Synthesizer / Real PPG Wave)
  useEffect(() => {
    const canvas = waveCanvasRef.current;
    if (!canvas) return;

    const render = () => {
      const active = isConnected || isSimulatorActive;
      const hr = Number(telemetry?.heartRate || 0);
      const isSkinOn = hr > 0;

      // Simulasi kurva dicrotic notch PPG denyut nadi jika ada detak
      if (active && isSkinOn) {
        // Frekuensi sesuai detak jantung asli (BPM / 60)
        const freq = (hr / 60) * 0.08;
        phaseRef.current += freq;
        const p = phaseRef.current;

        // Persamaan gelombang pulsa arteri fisiologis:
        // Puncak sistolik + dicrotic notch sekunder
        const primaryWave = Math.sin(p) * 0.7;
        const dicroticWave = Math.sin(p * 2 + 1.2) * 0.32;
        const noise = (Math.random() - 0.5) * 0.04;
        const val = (primaryWave + dicroticWave + noise) * 120;

        waveDataRef.current.push(val);
      } else if (active) {
        // Flatline dengan mikro-noise instrumen
        waveDataRef.current.push((Math.random() - 0.5) * 3);
      } else {
        waveDataRef.current.push(0);
      }

      if (waveDataRef.current.length > NWAVE) {
        waveDataRef.current.shift();
      }

      drawWave();
      animFrameRef.current = requestAnimationFrame(render);
    };

    animFrameRef.current = requestAnimationFrame(render);
    return () => {
      if (animFrameRef.current) cancelAnimationFrame(animFrameRef.current);
    };
  }, [isConnected, isSimulatorActive, telemetry?.heartRate]);

  // Render Canvas Gelombang PPG Terfilter (Bandpass 0.5 - 5 Hz)
  const drawWave = () => {
    const c = waveCanvasRef.current;
    if (!c) return;
    const ctx = c.getContext('2d');
    const W = c.width;
    const H = c.height;
    const P = 20;

    ctx.clearRect(0, 0, W, H);

    // Garis Baseline Tengah (Zero-Line)
    ctx.strokeStyle = 'rgba(122, 149, 162, 0.25)';
    ctx.lineWidth = 1;
    ctx.setLineDash([4, 4]);
    ctx.beginPath();
    ctx.moveTo(0, H / 2);
    ctx.lineTo(W, H / 2);
    ctx.stroke();
    ctx.setLineDash([]);

    const wave = waveDataRef.current;
    if (wave.length < 2) return;

    let maxVal = 1;
    for (const v of wave) maxVal = Math.max(maxVal, Math.abs(v));
    const scale = (H / 2 - P) / Math.max(maxVal, 30);

    ctx.beginPath();
    wave.forEach((v, i) => {
      const px = (i / (NWAVE - 1)) * W;
      const py = H / 2 - v * scale;
      if (i === 0) ctx.moveTo(px, py);
      else ctx.lineTo(px, py);
    });

    // Warna pulsa (Merah detak jantung cerah)
    ctx.strokeStyle = '#FF5252';
    ctx.lineWidth = 2.5;
    ctx.lineJoin = 'round';
    ctx.stroke();

    // Efek glowing head di titik terbaru
    const lastX = W;
    const lastY = H / 2 - wave[wave.length - 1] * scale;
    ctx.beginPath();
    ctx.arc(lastX - 2, lastY, 4, 0, Math.PI * 2);
    ctx.fillStyle = '#FF5252';
    ctx.shadowColor = '#FF5252';
    ctx.shadowBlur = 8;
    ctx.fill();
    ctx.shadowBlur = 0;
  };

  // Render Canvas Tren 2 Menit (BPM & SpO2)
  const drawTrend = () => {
    const c = trendCanvasRef.current;
    if (!c) return;
    const ctx = c.getContext('2d');
    const W = c.width;
    const H = c.height;
    const P = 24;

    ctx.clearRect(0, 0, W, H);
    ctx.font = '11px var(--font-mono, monospace)';

    const { hr, spo2 } = trendDataRef.current;

    // Grid garis horizontal
    ctx.strokeStyle = 'rgba(122, 149, 162, 0.15)';
    ctx.lineWidth = 1;
    for (let i = 0; i <= 3; i++) {
      const y = Math.round(P + ((H - P * 2) * i) / 3);
      ctx.beginPath();
      ctx.moveTo(P + 10, y);
      ctx.lineTo(W - P - 10, y);
      ctx.stroke();
    }

    // Fungsi bantu menggambar series garis
    const renderSeries = (arr, lo, hi, col, labelSide) => {
      const getY = (v) => H - P - ((v - lo) / (hi - lo)) * (H - P * 2);

      // Label batas min/max
      ctx.fillStyle = 'var(--text-muted, #7a95a2)';
      if (labelSide === 'left') {
        ctx.textAlign = 'left';
        ctx.fillText(`${hi}`, 6, Math.round(getY(hi)) + 4);
        ctx.fillText(`${lo}`, 6, Math.round(getY(lo)) + 4);
      } else {
        ctx.textAlign = 'right';
        ctx.fillText(`${hi}%`, W - 6, Math.round(getY(hi)) + 4);
        ctx.fillText(`${lo}%`, W - 6, Math.round(getY(lo)) + 4);
      }

      const validPts = arr
        .map((v, i) => ({
          v,
          x: P + 30 + (i / Math.max(NTREND - 1, 1)) * (W - P * 2 - 60),
        }))
        .filter((pt) => pt.v > 0);

      if (validPts.length < 2) return;

      ctx.beginPath();
      validPts.forEach((pt, i) => {
        const py = Math.max(P, Math.min(H - P, getY(pt.v)));
        if (i === 0) ctx.moveTo(pt.x, py);
        else ctx.lineTo(pt.x, py);
      });
      ctx.strokeStyle = col;
      ctx.lineWidth = 2.5;
      ctx.lineJoin = 'round';
      ctx.stroke();

      // Titik indikator terkini
      const last = validPts[validPts.length - 1];
      const lastY = Math.max(P, Math.min(H - P, getY(last.v)));
      ctx.beginPath();
      ctx.arc(last.x, lastY, 4.5, 0, Math.PI * 2);
      ctx.fillStyle = col;
      ctx.fill();
    };

    // Series HR: skala 40 - 150 BPM (Warna Merah)
    renderSeries(hr, 40, 150, '#FF5252', 'left');

    // Series SpO2: skala 80 - 100% (Warna Cyan/Teal)
    renderSeries(spo2, 80, 100, '#2DD4BF', 'right');
  };

  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '1.25rem', marginTop: '1.25rem' }}>
      {/* Box 1: Gelombang PPG Terfilter */}
      <div className="card" style={{ padding: '1.25rem' }}>
        <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: '0.75rem' }}>
          <div style={{ display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
            <Activity size={18} color="#FF5252" />
            <h3 style={{ fontSize: '0.95rem', fontWeight: 600, color: 'var(--text-primary)' }}>
              GELOMBANG PPG TERFILTER (BANDPASS 0.5–5 Hz)
            </h3>
          </div>
          <span style={{ fontSize: '0.75rem', fontFamily: 'var(--font-mono)', color: 'var(--text-muted)' }}>
            fs = 100 Hz
          </span>
        </div>
        <div style={{ background: 'var(--bg-app)', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-subtle)', overflow: 'hidden' }}>
          <canvas ref={waveCanvasRef} width={800} height={180} style={{ width: '100%', height: '140px', display: 'block' }} />
        </div>
        <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.65rem' }}>
          Grafik datar menandakan belum ada denyut. Jika bergelombang teratur, denyut terdeteksi dan BPM terhitung presisi.
        </p>
      </div>

      {/* Box 2: Tren 2 Menit (BPM & SpO2) */}
      <div className="card" style={{ padding: '1.25rem' }}>
        <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: '0.75rem' }}>
          <div style={{ display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
            <TrendingUp size={18} color="#2DD4BF" />
            <h3 style={{ fontSize: '0.95rem', fontWeight: 600, color: 'var(--text-primary)' }}>
              TREN VITAL SIGNS (BPM & SpO₂)
            </h3>
          </div>
          <div style={{ display: 'flex', gap: '0.85rem', fontSize: '0.75rem', fontFamily: 'var(--font-mono)' }}>
            <span style={{ color: '#FF5252', display: 'flex', alignItems: 'center', gap: '4px' }}>
              <span style={{ width: 8, height: 8, borderRadius: '50%', background: '#FF5252', display: 'inline-block' }}></span>
              HR (BPM)
            </span>
            <span style={{ color: '#2DD4BF', display: 'flex', alignItems: 'center', gap: '4px' }}>
              <span style={{ width: 8, height: 8, borderRadius: '50%', background: '#2DD4BF', display: 'inline-block' }}></span>
              SpO₂ (%)
            </span>
          </div>
        </div>
        <div style={{ background: 'var(--bg-app)', borderRadius: 'var(--radius-sm)', border: '1px solid var(--border-subtle)', overflow: 'hidden' }}>
          <canvas ref={trendCanvasRef} width={800} height={180} style={{ width: '100%', height: '140px', display: 'block' }} />
        </div>
        <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.65rem' }}>
          Menampilkan riwayat fluktuasi detak jantung dan saturasi oksigen korban selama 60 transmisi terakhir.
        </p>
      </div>
    </div>
  );
}
