import React from 'react';
import {
  Cpu,
  Radio,
  Activity,
  Droplets,
  Navigation,
  Bluetooth,
  CheckCircle2,
  AlertCircle,
  Zap,
  HardDrive,
  ShieldAlert,
  Server
} from 'lucide-react';

export default function DevicesPage({ telemetry, connectionState }) {
  const isConnected = connectionState?.connected;
  const isBle = connectionState?.ble;

  const devicesList = [
    {
      id: 'mcu',
      name: 'ESP32 Dev Module (WROOM-32)',
      role: 'Main System Controller & TinyML Execution',
      icon: Cpu,
      status: isConnected ? 'Online (Active)' : 'Standby',
      isOnline: isConnected,
      specs: [
        { label: 'Core Architecture', val: 'Xtensa Dual-Core 32-bit @ 240 MHz' },
        { label: 'SRAM / Flash', val: '520 KB SRAM / 4 MB SPI Flash' },
        { label: 'OS Kernel', val: 'FreeRTOS Preemptive Multitasking' },
        { label: 'Model ML', val: 'Random Forest 10 Trees (C-Transpiled)' },
      ],
    },
    {
      id: 'max30102',
      name: 'MAX30102 Pulse Oximeter (MH-ET Live)',
      role: 'Biometric PPG SpO2 & Heart Rate Monitoring',
      icon: Activity,
      status: telemetry?.spo2 > 0 ? 'Optimal (Finger Detected)' : isConnected ? 'Monitoring (No Finger)' : 'Standby',
      isOnline: isConnected,
      specs: [
        { label: 'Interface & Address', val: 'I2C @ 100 kHz (SDA: 21, SCL: 22)' },
        { label: 'Current Reading', val: `${telemetry?.spo2 > 0 ? `${telemetry.spo2}% SpO2` : 'Waiting'} | ${telemetry?.heartRate > 0 ? `${telemetry.heartRate} BPM` : 'Waiting'}` },
        { label: 'LED Drive Current', val: '0x3F (~12.5 mA Pulsed Red & IR)' },
        { label: 'Sampling Rate', val: '100 Hz Raw Optical Acquisition' },
      ],
    },
    {
      id: 'water',
      name: 'Dual-Level Submersion Sensors',
      role: 'Redundant Waist & Neck Water Detection',
      icon: Droplets,
      status: telemetry?.neckWater >= 30 ? 'CRITICAL SUBMERGED!' : telemetry?.waistWater > 30 ? 'Floating in Water' : 'Dry / Normal',
      isOnline: isConnected,
      specs: [
        { label: 'Sensor Pinggang', val: `GPIO 26 (ADC1_CH9) — ${Number(telemetry?.waistWater || 0).toFixed(1)}%` },
        { label: 'Sensor Leher', val: `GPIO 27 (ADC1_CH7) — ${Number(telemetry?.neckWater || 0).toFixed(1)}%` },
        { label: 'Resolution', val: '12-bit ADC (0 - 4095 range)' },
        { label: 'Fail-Safe Mode', val: 'Forced Critical when Neck >= 30%' },
      ],
    },
    {
      id: 'gps',
      name: 'u-blox NEO-6M / NEO-M8N GPS',
      role: 'High-Precision SAR Geographic Locator',
      icon: Navigation,
      status: telemetry?.satellites > 0 ? `Locked (${telemetry.satellites} Sats)` : isConnected ? 'Searching Satellites' : 'Standby',
      isOnline: isConnected,
      specs: [
        { label: 'Interface', val: 'Hardware UART2 (RX: 16, TX: 17)' },
        { label: 'Baud Rate', val: '9600 bps NMEA-0183' },
        { label: 'Current Position', val: `${telemetry?.latitude?.toFixed(6) || '-6.3627'}, ${telemetry?.longitude?.toFixed(6) || '106.8272'}` },
        { label: 'Update Interval', val: '1 Hz Continuous GPS Fix' },
      ],
    },
    {
      id: 'ble',
      name: 'BLE 4.2 Wireless Telemetry Link',
      role: 'Real-time Wireless Broadcast to Web Dashboard',
      icon: Bluetooth,
      status: isConnected && isBle ? 'Connected & Notifying' : 'Advertising (LifeVest-01)',
      isOnline: isConnected && isBle,
      specs: [
        { label: 'Device Name', val: 'LifeVest-01' },
        { label: 'Service UUID', val: '4fafc201-1fb5-459e-8fcc-c5c9c331914b' },
        { label: 'Characteristic UUID', val: 'beb5483e-36e1-4688-b7f5-ea07361b26a8' },
        { label: 'Payload Format', val: 'JSON String Telemetry Stream (500 ms)' },
      ],
    },
  ];

  return (
    <div className="devices-page-container">
      {/* Page Header */}
      <div className="page-header-row">
        <div>
          <h2 className="page-title">Hardware & Sensors Diagnostics</h2>
          <p className="page-subtitle">
            Status operasional, pinout konfigurasi, dan kesehatan periferal modul Smart Life Vest DROWNT.
          </p>
        </div>
        <div className="header-action-group">
          <span className={`badge ${isConnected ? 'badge-safe' : 'badge-neutral'}`} style={{ padding: '0.45rem 0.85rem' }}>
            <Server size={14} />
            <span>{isConnected ? 'NODE CONNECTED' : 'NODE DISCONNECTED'}</span>
          </span>
        </div>
      </div>

      {/* Hardware Architecture Overview Cards */}
      <div className="devices-grid">
        {devicesList.map((dev) => {
          const Icon = dev.icon;
          return (
            <div key={dev.id} className="card device-card">
              <div className="device-card-header">
                <div className="device-icon-box">
                  <Icon size={24} color="var(--primary-emerald)" />
                </div>
                <div className="device-title-box">
                  <h3 className="device-name">{dev.name}</h3>
                  <p className="device-role">{dev.role}</p>
                </div>
                <span className={`badge ${dev.isOnline ? 'badge-safe' : 'badge-neutral'}`} style={{ marginLeft: 'auto' }}>
                  {dev.status}
                </span>
              </div>

              {/* Specs Grid */}
              <div className="device-specs-grid">
                {dev.specs.map((s, idx) => (
                  <div key={idx} className="spec-item">
                    <span className="spec-label">{s.label}</span>
                    <span className="spec-val font-mono">{s.val}</span>
                  </div>
                ))}
              </div>
            </div>
          );
        })}
      </div>

      {/* Pinout Reference Card */}
      <div className="card pinout-card">
        <h3 className="section-title">
          <Zap size={18} color="var(--primary-emerald)" />
          <span>Skema Pinout & Pengkabelan ESP32 DevKit</span>
        </h3>
        <p className="section-desc">Peta koneksi kabel GPIO perangkat keras pelampung DROWNT.</p>

        <div className="pinout-table-wrapper">
          <table className="pinout-table">
            <thead>
              <tr>
                <th>Modul / Sensor</th>
                <th>Fungsi Sinyal</th>
                <th>Pin ESP32</th>
                <th>Level Tegangan</th>
                <th>Keterangan Teknis</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td><strong>MAX30102</strong></td>
                <td>I2C SDA</td>
                <td className="font-mono">GPIO 21</td>
                <td>3.3V</td>
                <td>Data line bus I2C (kecepatan 100 kHz)</td>
              </tr>
              <tr>
                <td><strong>MAX30102</strong></td>
                <td>I2C SCL</td>
                <td className="font-mono">GPIO 22</td>
                <td>3.3V</td>
                <td>Clock line bus I2C</td>
              </tr>
              <tr>
                <td><strong>Sensor Air Pinggang</strong></td>
                <td>Analog Output</td>
                <td className="font-mono">GPIO 26</td>
                <td>3.3V (ADC)</td>
                <td>Deteksi awal saat tubuh masuk ke air</td>
              </tr>
              <tr>
                <td><strong>Sensor Air Leher</strong></td>
                <td>Analog Output</td>
                <td className="font-mono">GPIO 27</td>
                <td>3.3V (ADC)</td>
                <td>Indikator bahaya fatal tenggelam (fail-safe)</td>
              </tr>
              <tr>
                <td><strong>GPS NEO-6M</strong></td>
                <td>UART RX (ESP Terima)</td>
                <td className="font-mono">GPIO 16</td>
                <td>3.3V</td>
                <td>Tersambung ke pin TX modul GPS (Serial2)</td>
              </tr>
              <tr>
                <td><strong>GPS NEO-6M</strong></td>
                <td>UART TX (ESP Kirim)</td>
                <td className="font-mono">GPIO 17</td>
                <td>3.3V</td>
                <td>Tersambung ke pin RX modul GPS (Serial2)</td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
}
