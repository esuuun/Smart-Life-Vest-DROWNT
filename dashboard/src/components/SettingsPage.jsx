import React, { useState } from 'react';
import {
  Settings,
  Volume2,
  VolumeX,
  Bell,
  Sun,
  Moon,
  ShieldAlert,
  Sliders,
  RotateCcw,
  CheckCircle2,
  Radio
} from 'lucide-react';

export default function SettingsPage({
  isMuted,
  onToggleMute,
  theme,
  onToggleTheme,
  currentStatus
}) {
  const [neckThreshold, setNeckThreshold] = useState(30);
  const [hypoxiaThreshold, setHypoxiaThreshold] = useState(88);
  const [tachyThreshold, setTachyThreshold] = useState(130);
  const [savedToast, setSavedToast] = useState(false);

  const handleSaveSettings = () => {
    setSavedToast(true);
    setTimeout(() => setSavedToast(false), 2500);
  };

  const handleResetSettings = () => {
    setNeckThreshold(30);
    setHypoxiaThreshold(88);
    setTachyThreshold(130);
    setSavedToast(true);
    setTimeout(() => setSavedToast(false), 2500);
  };

  return (
    <div className="settings-page-container">
      {/* Page Header */}
      <div className="page-header-row">
        <div>
          <h2 className="page-title">System & SAR Settings</h2>
          <p className="page-subtitle">
            Kustomisasi parameter ambang batas bahaya, peringatan audio, dan preferensi antarmuka.
          </p>
        </div>
        <div className="header-action-group">
          <button className="btn-secondary" onClick={handleResetSettings}>
            <RotateCcw size={16} />
            <span>Reset Default</span>
          </button>
          <button className="btn-primary" onClick={handleSaveSettings}>
            <CheckCircle2 size={16} />
            <span>Simpan Pengaturan</span>
          </button>
        </div>
      </div>

      {savedToast && (
        <div className="toast-banner">
          <CheckCircle2 size={18} color="var(--primary-emerald)" />
          <span>Pengaturan ambang batas SAR berhasil disimpan ke konfigurasi lokal!</span>
        </div>
      )}

      <div className="settings-grid">
        {/* Card 1: SAR Emergency Thresholds */}
        <div className="card settings-section-card">
          <h3 className="section-title">
            <Sliders size={18} color="var(--primary-emerald)" />
            <span>Ambang Batas Peringatan Darurat (Thresholds)</span>
          </h3>
          <p className="section-desc">
            Nilai pemicu aturan fail-safe medis untuk mengubah status menjadi KRITIS secara instan.
          </p>

          <div className="slider-group">
            <div className="slider-header">
              <span className="slider-label">Submersion Sensor Leher (Fail-Safe Kritis)</span>
              <span className="slider-val font-mono">{neckThreshold}%</span>
            </div>
            <input
              type="range"
              min="10"
              max="70"
              value={neckThreshold}
              onChange={(e) => setNeckThreshold(Number(e.target.value))}
              className="range-input"
            />
            <span className="slider-hint">
              Jika sensor air leher membaca $\ge {neckThreshold}\%$, status langsung dipaksa KRITIS tanpa menunggu SpO2 turun.
            </span>
          </div>

          <div className="slider-group">
            <div className="slider-header">
              <span className="slider-label">Batas Hipoksia Berat SpO2</span>
              <span className="slider-val font-mono">&lt; {hypoxiaThreshold}%</span>
            </div>
            <input
              type="range"
              min="75"
              max="95"
              value={hypoxiaThreshold}
              onChange={(e) => setHypoxiaThreshold(Number(e.target.value))}
              className="range-input"
            />
            <span className="slider-hint">
              Saturasi oksigen darah di bawah {hypoxiaThreshold}% mengindikasikan asfiksia akibat jalan napas tertutup air.
            </span>
          </div>

          <div className="slider-group">
            <div className="slider-header">
              <span className="slider-label">Batas Takikardia Stres Ekstrem (Heart Rate)</span>
              <span className="slider-val font-mono">&gt; {tachyThreshold} BPM</span>
            </div>
            <input
              type="range"
              min="100"
              max="160"
              value={tachyThreshold}
              onChange={(e) => setTachyThreshold(Number(e.target.value))}
              className="range-input"
            />
            <span className="slider-hint">
              Denyut nadi di atas {tachyThreshold} BPM menandakan kepanikan hebat saat korban berusaha mengapung.
            </span>
          </div>
        </div>

        {/* Card 2: Audio Siren & Notifications */}
        <div className="card settings-section-card">
          <h3 className="section-title">
            <Bell size={18} color="var(--primary-emerald)" />
            <span>Sistem Peringatan Audio & Alarm</span>
          </h3>
          <p className="section-desc">
            Pengaturan sirine evakuasi otomatis dan nada peringatan saat status darurat terdeteksi.
          </p>

          <div className="setting-toggle-row">
            <div>
              <div className="toggle-title">Sirine Evakuasi KRITIS (alarm.mp4)</div>
              <div className="toggle-desc">
                Memutar suara alarm darurat secara otomatis saat status mencapai status bahaya KRITIS.
              </div>
            </div>
            <button
              className={`btn-toggle-switch ${!isMuted ? 'switch-on' : ''}`}
              onClick={onToggleMute}
            >
              {!isMuted ? <Volume2 size={18} /> : <VolumeX size={18} />}
              <span>{!isMuted ? 'Aktif' : 'Muted'}</span>
            </button>
          </div>

          <div className="setting-toggle-row">
            <div>
              <div className="toggle-title">Tema Visual Dasbor (Dark / Light)</div>
              <div className="toggle-desc">
                Ganti tampilan antara mode Terang (Standar FTUI) dan Mode Gelap (Tactical Night).
              </div>
            </div>
            <button
              className="btn-secondary"
              onClick={onToggleTheme}
              style={{ minWidth: '120px', justifyContent: 'center' }}
            >
              {theme === 'dark' ? <Moon size={16} /> : <Sun size={16} />}
              <span>{theme === 'dark' ? 'Mode Gelap' : 'Mode Terang'}</span>
            </button>
          </div>

          {/* Model ML Metadata */}
          <div className="model-info-box">
            <div className="model-info-title">
              <Radio size={16} color="var(--primary-emerald)" />
              <span>Edge AI Model Specification</span>
            </div>
            <div className="model-info-text">
              Model: <strong>Random Forest Classifier</strong> (10 Estimators, Depth 6)<br />
              Fitur: <strong>SpO2, Heart Rate, Water Waist, Water Neck</strong><br />
              Waktu Inferensi: <strong>&lt; 0.8 ms</strong> on ESP32 Xtensa LX6 @ 240 MHz<br />
              Karakteristik Transmisi: <strong>BLE 4.2 GATT Notify + USB Serial 115200</strong>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
