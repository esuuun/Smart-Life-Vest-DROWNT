import React, { useState, useMemo } from 'react';
import {
  History,
  Search,
  Filter,
  Download,
  Trash2,
  ChevronDown,
  ChevronUp,
  AlertTriangle,
  Heart,
  Wind,
  Droplets,
  MapPin,
  CheckCircle2,
  Clock
} from 'lucide-react';

export default function HistoryPage({ logs, onClearLogs, onExportCSV }) {
  const [searchTerm, setSearchTerm] = useState('');
  const [statusFilter, setStatusFilter] = useState('ALL');
  const [selectedLog, setSelectedLog] = useState(null);
  const [page, setPage] = useState(1);
  const rowsPerPage = 20;

  // Filter logs berdasarkan search & status
  const filteredLogs = useMemo(() => {
    return logs.filter((log) => {
      const matchStatus = statusFilter === 'ALL' || log.status === statusFilter;
      const matchSearch =
        searchTerm === '' ||
        log.timestamp?.toLowerCase().includes(searchTerm.toLowerCase()) ||
        String(log.seq).includes(searchTerm) ||
        log.status?.toLowerCase().includes(searchTerm.toLowerCase());
      return matchStatus && matchSearch;
    });
  }, [logs, statusFilter, searchTerm]);

  // Reverse urutan agar data terbaru di atas
  const displayLogs = useMemo(() => {
    return [...filteredLogs].reverse();
  }, [filteredLogs]);

  const totalPages = Math.max(1, Math.ceil(displayLogs.length / rowsPerPage));
  const paginatedLogs = displayLogs.slice((page - 1) * rowsPerPage, page * rowsPerPage);

  const filterTabs = [
    { id: 'ALL', label: 'Semua Status', count: logs.length },
    { id: 'AMAN', label: 'AMAN', count: logs.filter((l) => l.status === 'AMAN').length },
    { id: 'WASPADA', label: 'WASPADA', count: logs.filter((l) => l.status === 'WASPADA').length },
    { id: 'KRITIS', label: 'KRITIS', count: logs.filter((l) => l.status === 'KRITIS').length },
  ];

  return (
    <div className="history-page-container">
      {/* Page Header */}
      <div className="page-header-row">
        <div>
          <h2 className="page-title">Telemetry History & Records</h2>
          <p className="page-subtitle">
            Daftar lengkap rekaman paket telemetri fisiologis dan geolokasi korban secara kronologis.
          </p>
        </div>
        <div className="header-action-group">
          <button className="btn-secondary" onClick={onExportCSV}>
            <Download size={16} />
            <span>Download CSV ({logs.length})</span>
          </button>
          <button
            className="btn-danger-outline"
            onClick={() => {
              if (window.confirm('Hapus seluruh riwayat log telemetri di sesi ini?')) {
                onClearLogs();
              }
            }}
          >
            <Trash2 size={16} />
            <span>Bersihkan Log</span>
          </button>
        </div>
      </div>

      {/* Filter & Search Bar */}
      <div className="card history-filter-card">
        <div className="filter-tabs-group">
          {filterTabs.map((tab) => (
            <button
              key={tab.id}
              className={`filter-tab-btn ${statusFilter === tab.id ? 'active' : ''}`}
              onClick={() => {
                setStatusFilter(tab.id);
                setPage(1);
              }}
            >
              <span>{tab.label}</span>
              <span className="tab-count-pill">{tab.count}</span>
            </button>
          ))}
        </div>

        <div className="search-input-wrapper">
          <Search size={16} className="search-icon" />
          <input
            type="text"
            className="search-input"
            placeholder="Cari waktu, sequence ID..."
            value={searchTerm}
            onChange={(e) => {
              setSearchTerm(e.target.value);
              setPage(1);
            }}
          />
        </div>
      </div>

      {/* Main Table Card */}
      <div className="card table-container-card">
        <div className="table-wrapper">
          <table className="telemetry-table">
            <thead>
              <tr>
                <th style={{ width: '80px' }}>Seq #</th>
                <th style={{ width: '110px' }}>Waktu</th>
                <th style={{ width: '120px' }}>Status</th>
                <th style={{ width: '100px' }}>Risk Index</th>
                <th>SpO2</th>
                <th>Heart Rate</th>
                <th>Air Pinggang</th>
                <th>Air Leher</th>
                <th>Koordinat GPS</th>
                <th style={{ textAlign: 'center', width: '90px' }}>Detail</th>
              </tr>
            </thead>
            <tbody>
              {paginatedLogs.length === 0 ? (
                <tr>
                  <td colSpan={10} className="table-empty-cell">
                    <History size={32} color="var(--text-muted)" style={{ margin: '0 auto 0.75rem' }} />
                    <p>Tidak ada data telemetri yang cocok dengan filter.</p>
                  </td>
                </tr>
              ) : (
                paginatedLogs.map((row, idx) => {
                  const isKritis = row.status === 'KRITIS';
                  const isWaspada = row.status === 'WASPADA';
                  return (
                    <tr
                      key={row.seq || idx}
                      className={`table-row ${isKritis ? 'row-crit' : isWaspada ? 'row-warn' : ''}`}
                      onClick={() => setSelectedLog(selectedLog?.seq === row.seq ? null : row)}
                    >
                      <td className="font-mono">#{row.seq}</td>
                      <td className="font-mono text-muted">{row.timestamp}</td>
                      <td>
                        <span
                          className={`badge ${
                            isKritis ? 'badge-crit' : isWaspada ? 'badge-warn' : 'badge-safe'
                          }`}
                        >
                          {row.status}
                        </span>
                      </td>
                      <td className="font-mono font-bold">
                        <span
                          style={{
                            color: isKritis
                              ? 'var(--status-crit)'
                              : isWaspada
                              ? 'var(--status-warn)'
                              : 'var(--primary-emerald)',
                          }}
                        >
                          {row.riskScore}%
                        </span>
                      </td>
                      <td className="font-mono">{row.spo2 > 0 ? `${row.spo2}%` : '--'}</td>
                      <td className="font-mono">{row.heartRate > 0 ? `${row.heartRate} BPM` : '--'}</td>
                      <td className="font-mono">{row.waistWater != null ? `${Number(row.waistWater).toFixed(1)}%` : '--'}</td>
                      <td className="font-mono">{row.neckWater != null ? `${Number(row.neckWater).toFixed(1)}%` : '--'}</td>
                      <td className="font-mono text-muted" style={{ fontSize: '0.8rem' }}>
                        {row.latitude ? `${row.latitude.toFixed(5)}, ${row.longitude.toFixed(5)}` : 'No GPS'}
                      </td>
                      <td style={{ textAlign: 'center' }}>
                        <button
                          className="btn-icon-subtle"
                          title="Lihat Detail Paket"
                          onClick={(e) => {
                            e.stopPropagation();
                            setSelectedLog(selectedLog?.seq === row.seq ? null : row);
                          }}
                        >
                          {selectedLog?.seq === row.seq ? <ChevronUp size={16} /> : <ChevronDown size={16} />}
                        </button>
                      </td>
                    </tr>
                  );
                })
              )}
            </tbody>
          </table>
        </div>

        {/* Pagination Bar */}
        {totalPages > 1 && (
          <div className="table-pagination-bar">
            <span className="pagination-info">
              Menampilkan {(page - 1) * rowsPerPage + 1} - {Math.min(page * rowsPerPage, displayLogs.length)} dari {displayLogs.length} paket
            </span>
            <div className="pagination-controls">
              <button
                className="btn-pagination"
                disabled={page <= 1}
                onClick={() => setPage(page - 1)}
              >
                Sebelumnya
              </button>
              <span className="pagination-current font-mono">
                {page} / {totalPages}
              </span>
              <button
                className="btn-pagination"
                disabled={page >= totalPages}
                onClick={() => setPage(page + 1)}
              >
                Berikutnya
              </button>
            </div>
          </div>
        )}
      </div>

      {/* Selected Packet Inspection Modal / Drawer */}
      {selectedLog && (
        <div className="card packet-detail-card">
          <div className="detail-header">
            <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem' }}>
              <span className="detail-title">Inspeksi Paket #{selectedLog.seq}</span>
              <span
                className={`badge ${
                  selectedLog.status === 'KRITIS'
                    ? 'badge-crit'
                    : selectedLog.status === 'WASPADA'
                    ? 'badge-warn'
                    : 'badge-safe'
                }`}
              >
                {selectedLog.status}
              </span>
            </div>
            <button className="btn-icon-subtle" onClick={() => setSelectedLog(null)}>
              ✕
            </button>
          </div>

          <div className="detail-grid">
            <div className="detail-metric">
              <span className="lbl">Waktu Kedatangan</span>
              <span className="val font-mono">{selectedLog.timestamp}</span>
            </div>
            <div className="detail-metric">
              <span className="lbl">Index Bahaya (Risk Score)</span>
              <span className="val font-mono">{selectedLog.riskScore}%</span>
            </div>
            <div className="detail-metric">
              <span className="lbl">SpO2 Oksigen Darah</span>
              <span className="val font-mono">{selectedLog.spo2}%</span>
            </div>
            <div className="detail-metric">
              <span className="lbl">Detak Jantung (PPG)</span>
              <span className="val font-mono">{selectedLog.heartRate} BPM</span>
            </div>
            <div className="detail-metric">
              <span className="lbl">Level Air Pinggang</span>
              <span className="val font-mono">{selectedLog.waistWater}%</span>
            </div>
            <div className="detail-metric">
              <span className="lbl">Level Air Leher</span>
              <span className="val font-mono">{selectedLog.neckWater}%</span>
            </div>
            <div className="detail-metric">
              <span className="lbl">Probabilitas TinyML</span>
              <span className="val font-mono" style={{ fontSize: '0.85rem' }}>
                Aman: {(selectedLog.probAman * 100).toFixed(0)}% | Waspada: {(selectedLog.probWaspada * 100).toFixed(0)}% | Kritis: {(selectedLog.probKritis * 100).toFixed(0)}%
              </span>
            </div>
            <div className="detail-metric">
              <span className="lbl">Koordinat & Satelit GPS</span>
              <span className="val font-mono" style={{ fontSize: '0.85rem' }}>
                {selectedLog.latitude?.toFixed(6)}, {selectedLog.longitude?.toFixed(6)} ({selectedLog.satellites || 0} Sats)
              </span>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
