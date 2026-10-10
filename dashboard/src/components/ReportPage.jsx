import React, { useState } from 'react';
import {
  FileText,
  Printer,
  Copy,
  Check,
  AlertTriangle,
  Heart,
  Wind,
  Droplets,
  MapPin,
  Clock,
  ShieldCheck,
  Activity,
  Download
} from 'lucide-react';

export default function ReportPage({ telemetry, logs, currentScenario, onExportCSV }) {
  const [copied, setCopied] = useState(false);

  // Analisis statistik sesi dari rekaman logs
  const totalPackets = logs.length;
  const amanLogs = logs.filter((l) => l.status === 'AMAN').length;
  const waspadaLogs = logs.filter((l) => l.status === 'WASPADA').length;
  const kritisLogs = logs.filter((l) => l.status === 'KRITIS').length;

  const pctAman = totalPackets > 0 ? ((amanLogs / totalPackets) * 100).toFixed(1) : '100.0';
  const pctWaspada = totalPackets > 0 ? ((waspadaLogs / totalPackets) * 100).toFixed(1) : '0.0';
  const pctKritis = totalPackets > 0 ? ((kritisLogs / totalPackets) * 100).toFixed(1) : '0.0';

  // Ekstrak nilai ekstrem
  const validSpo2 = logs.map((l) => Number(l.spo2 || 0)).filter((v) => v > 0);
  const minSpo2 = validSpo2.length > 0 ? Math.min(...validSpo2).toFixed(1) : telemetry?.spo2 > 0 ? telemetry.spo2 : 98.0;
  const avgSpo2 = validSpo2.length > 0 ? (validSpo2.reduce((a, b) => a + b, 0) / validSpo2.length).toFixed(1) : '98.0';

  const validHR = logs.map((l) => Number(l.heartRate || 0)).filter((v) => v > 0);
  const maxHR = validHR.length > 0 ? Math.max(...validHR).toFixed(1) : telemetry?.heartRate > 0 ? telemetry.heartRate : 75.0;
  const minHR = validHR.length > 0 ? Math.min(...validHR).toFixed(1) : telemetry?.heartRate > 0 ? telemetry.heartRate : 75.0;
  const avgHR = validHR.length > 0 ? (validHR.reduce((a, b) => a + b, 0) / validHR.length).toFixed(1) : '75.0';

  const maxRisk = logs.length > 0 ? Math.max(...logs.map((l) => Number(l.riskScore || 0))) : telemetry?.riskScore || 0;
  const maxWaterNeck = logs.length > 0 ? Math.max(...logs.map((l) => Number(l.neckWater || 0))) : telemetry?.neckWater || 0;

  const firstTime = logs.length > 0 ? logs[0].timestamp : new Date().toLocaleTimeString();
  const lastTime = logs.length > 0 ? logs[logs.length - 1].timestamp : new Date().toLocaleTimeString();

  // Status evaluasi akhir
  const worstStatus = kritisLogs > 0 ? 'KRITIS (DROWNING DETECTED)' : waspadaLogs > 0 ? 'WASPADA (FLOATING IN WATER)' : 'AMAN (NORMAL)';

  // Narasi otomatis untuk laporan SAR
  const reportNarrative = `
LAPORAN RESMI KRONOLOGIS OPERASI PENCARIAN & PENYELAMATAN (SAR)
SISTEM SMART LIFE VEST "DROWNT" — UNIT TELEMETRI VEST-01
Departemen Teknik Komputer FTUI (Kelompok 33 UAS Despro 2)

================================================================================
RINGKASAN OPERASIONAL & METADATA
================================================================================
ID Perangkat       : ${telemetry?.id || 'VEST-01'}
Waktu Mulai Sesi   : ${firstTime} WIB
Waktu Terakhir     : ${lastTime} WIB
Total Sampel Data  : ${totalPackets} Transmisi Telemetri
Skenario / Status  : ${worstStatus}
Index Bahaya Puncak: ${maxRisk}%

================================================================================
GEOLOKASI SAR & TITIK KOORDINAT TERAKHIR
================================================================================
Garis Lintang (Lat): ${telemetry?.latitude?.toFixed(6) || '-6.362700'}
Garis Bujur (Lng)  : ${telemetry?.longitude?.toFixed(6) || '106.827200'}
Satelit Terkunci   : ${telemetry?.satellites || 8} GPS Satellites
Radius Presisi     : ±2.5 Meter (u-blox NEO-6M / M8N Engine)

================================================================================
DIAGNOSTIK FISIOLOGIS & KONDISI AIR
================================================================================
- Saturasi Oksigen : Min: ${minSpo2}% | Rata-rata: ${avgSpo2}%
- Detak Jantung    : Rentang: ${minHR} - ${maxHR} BPM (Avg: ${avgHR} BPM)
- Sensor Air Leher : Puncak Submersion: ${maxWaterNeck.toFixed(1)}%
- Distribusi Waktu : Aman (${pctAman}%) | Waspada (${pctWaspada}%) | Kritis (${pctKritis}%)

================================================================================
KESIMPULAN INFERENSI TINYML ON-DEVICE
================================================================================
${kritisLogs > 0
  ? 'PERINGATAN TINGGI: Korban mengalami insiden tenggelam dengan keterlibatan sensor leher terendam air dan/atau desaturasi oksigen kritis. Sistem secara otomatis memicu sirine evakuasi dan mengirimkan sinyal bahaya ke stasiun pantai.'
  : waspadaLogs > 0
  ? 'PERINGATAN RINGAN: Korban terpantau berada di atas permukaan air dalam kondisi mengapung stabil. Parameter vital menunjukkan respons stres ringan. Direkomendasikan pemantauan posisi berkala.'
  : 'KONDISI AMAN: Korban berada di daratan atau di atas kapal. Seluruh parameter fisiologis dan sensor lingkungan berada pada batas normal.'
}
`.trim();

  const handleCopyReport = () => {
    navigator.clipboard.writeText(reportNarrative);
    setCopied(true);
    setTimeout(() => setCopied(false), 2500);
  };

  const handlePrint = () => {
    window.print();
  };

  return (
    <div className="report-page-container">
      {/* Action Header */}
      <div className="page-header-row">
        <div>
          <h2 className="page-title">SAR Incident & Mission Report</h2>
          <p className="page-subtitle">
            Laporan analitik kronologis otomatis hasil pemantauan Edge AI DROWNT untuk evakuasi medis dan tim penyelamat.
          </p>
        </div>
        <div className="header-action-group">
          <button className="btn-secondary" onClick={handleCopyReport}>
            {copied ? <Check size={16} color="var(--primary-emerald)" /> : <Copy size={16} />}
            <span>{copied ? 'Tersalin!' : 'Salin Teks'}</span>
          </button>
          <button className="btn-secondary" onClick={onExportCSV}>
            <Download size={16} />
            <span>Export CSV</span>
          </button>
          <button className="btn-primary" onClick={handlePrint}>
            <Printer size={16} />
            <span>Cetak / Simpan PDF</span>
          </button>
        </div>
      </div>

      {/* Top Incident Summary Cards */}
      <div className="report-summary-grid">
        <div className="card report-metric-card">
          <div className="metric-header">
            <span className="metric-label">Status Terburuk Sesi</span>
            <AlertTriangle size={18} color={kritisLogs > 0 ? 'var(--status-crit)' : waspadaLogs > 0 ? 'var(--status-warn)' : 'var(--primary-emerald)'} />
          </div>
          <div className="metric-val" style={{ color: kritisLogs > 0 ? 'var(--status-crit)' : waspadaLogs > 0 ? 'var(--status-warn)' : 'var(--primary-emerald)' }}>
            {kritisLogs > 0 ? 'KRITIS' : waspadaLogs > 0 ? 'WASPADA' : 'AMAN'}
          </div>
          <div className="metric-desc">Puncak Risk Index: {maxRisk}%</div>
        </div>

        <div className="card report-metric-card">
          <div className="metric-header">
            <span className="metric-label">Saturasi Oksigen Terendah</span>
            <Wind size={18} color="var(--primary-emerald)" />
          </div>
          <div className="metric-val font-mono">{minSpo2}%</div>
          <div className="metric-desc">Rata-rata sesi: {avgSpo2}%</div>
        </div>

        <div className="card report-metric-card">
          <div className="metric-header">
            <span className="metric-label">Rentang Heart Rate</span>
            <Heart size={18} color="var(--status-crit)" />
          </div>
          <div className="metric-val font-mono">{minHR} - {maxHR} <span style={{ fontSize: '0.9rem' }}>BPM</span></div>
          <div className="metric-desc">Rata-rata: {avgHR} BPM</div>
        </div>

        <div className="card report-metric-card">
          <div className="metric-header">
            <span className="metric-label">Submersion Puncak Leher</span>
            <Droplets size={18} color="var(--primary-sage)" />
          </div>
          <div className="metric-val font-mono">{maxWaterNeck.toFixed(1)}%</div>
          <div className="metric-desc">{maxWaterNeck >= 30 ? 'Terendam Air (>30%)' : 'Aman di Atas Air'}</div>
        </div>
      </div>

      {/* Two Column Section: Visual Analytics (Left) & Official Narrative Document (Right) */}
      <div className="report-split-grid">
        {/* Left Column: Analytics Distribution */}
        <div className="report-left-col">
          <div className="card">
            <h3 className="section-title">
              <Activity size={18} color="var(--primary-emerald)" />
              <span>Distribusi Status Waktu SAR</span>
            </h3>
            <p className="section-desc">Persentase durasi korban berada di tiap zona klasifikasi risiko.</p>

            <div className="distribution-bars">
              {/* Aman */}
              <div className="dist-row">
                <div className="dist-info">
                  <span className="badge badge-safe">AMAN (Normal)</span>
                  <span className="font-mono">{pctAman}% ({amanLogs} pkts)</span>
                </div>
                <div className="progress-track">
                  <div className="progress-fill fill-safe" style={{ width: `${pctAman}%` }} />
                </div>
              </div>

              {/* Waspada */}
              <div className="dist-row">
                <div className="dist-info">
                  <span className="badge badge-warn">WASPADA (Di Air)</span>
                  <span className="font-mono">{pctWaspada}% ({waspadaLogs} pkts)</span>
                </div>
                <div className="progress-track">
                  <div className="progress-fill fill-warn" style={{ width: `${pctWaspada}%` }} />
                </div>
              </div>

              {/* Kritis */}
              <div className="dist-row">
                <div className="dist-info">
                  <span className="badge badge-crit">KRITIS (Tenggelam)</span>
                  <span className="font-mono">{pctKritis}% ({kritisLogs} pkts)</span>
                </div>
                <div className="progress-track">
                  <div className="progress-fill fill-crit" style={{ width: `${pctKritis}%` }} />
                </div>
              </div>
            </div>

            {/* Mission Key Info */}
            <div className="mission-info-box">
              <div className="info-item">
                <Clock size={16} color="var(--text-muted)" />
                <div>
                  <div className="item-label">Rentang Waktu Rekaman</div>
                  <div className="item-val">{firstTime} — {lastTime}</div>
                </div>
              </div>
              <div className="info-item">
                <MapPin size={16} color="var(--text-muted)" />
                <div>
                  <div className="item-label">Koordinat GPS Target</div>
                  <div className="item-val font-mono">{telemetry?.latitude?.toFixed(6)}, {telemetry?.longitude?.toFixed(6)}</div>
                </div>
              </div>
              <div className="info-item">
                <ShieldCheck size={16} color="var(--text-muted)" />
                <div>
                  <div className="item-label">Validasi Edge AI</div>
                  <div className="item-val">Model Random Forest (10 Trees, On-Device)</div>
                </div>
              </div>
            </div>
          </div>
        </div>

        {/* Right Column: Formal Report Paper Document */}
        <div className="report-right-col">
          <div className="card report-paper-card">
            <div className="paper-header">
              <div className="paper-seal">DROWNT SAR RESCUE</div>
              <div className="paper-meta">
                <div>DOC REF: SAR-{new Date().getFullYear()}-{telemetry?.id || 'VEST-01'}</div>
                <div>GENERATED: {new Date().toLocaleString()}</div>
              </div>
            </div>
            <pre className="paper-content">{reportNarrative}</pre>
          </div>
        </div>
      </div>
    </div>
  );
}
