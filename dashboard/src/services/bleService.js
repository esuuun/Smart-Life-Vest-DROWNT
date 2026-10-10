/**
 * @file bleService.js
 * @brief Layanan Web Bluetooth API (BLE) untuk koneksi nirkabel LifeVest-01
 * Departemen Teknik Elektro & Komputer FTUI - Kelompok 33
 */

const SVC_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const CHR_TELEM = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

class BLEService {
  constructor() {
    this.device = null;
    this.server = null;
    this.characteristic = null;
  }

  isSupported() {
    return 'bluetooth' in navigator;
  }

  async connect(onDataReceived, onStatusChange) {
    if (!this.isSupported()) {
      throw new Error('Web Bluetooth API tidak didukung di browser ini. Gunakan Google Chrome atau Microsoft Edge terbaru di HTTPS/Localhost.');
    }

    try {
      onStatusChange({ connecting: true });

      // Request device dengan nama prefix LifeVest
      this.device = await navigator.bluetooth.requestDevice({
        filters: [{ namePrefix: 'LifeVest' }],
        optionalServices: [SVC_UUID, 0x180D]
      });

      this.device.addEventListener('gattserverdisconnected', () => {
        console.log('BLE Device terputus');
        onStatusChange({ connected: false, ble: true });
      });

      this.server = await this.device.gatt.connect();
      const service = await this.server.getPrimaryService(SVC_UUID);
      this.characteristic = await service.getCharacteristic(CHR_TELEM);

      await this.characteristic.startNotifications();
      this.characteristic.addEventListener('characteristicvaluechanged', (event) => {
        const rawText = new TextDecoder().decode(event.target.value);
        try {
          const parsed = JSON.parse(rawText);
          onDataReceived(this.normalizeTelemetry(parsed));
        } catch (err) {
          console.warn('Gagal parse BLE JSON:', rawText, err);
        }
      });

      onStatusChange({ connected: true, ble: true, deviceName: this.device.name });
    } catch (err) {
      onStatusChange({ connected: false, ble: true, error: err.message });
      throw err;
    }
  }

  async disconnect(onStatusChange) {
    if (this.device && this.device.gatt.connected) {
      await this.device.gatt.disconnect();
    }
    this.device = null;
    this.server = null;
    this.characteristic = null;
    if (onStatusChange) {
      onStatusChange({ connected: false, ble: true });
    }
  }

  normalizeTelemetry(data) {
    return {
      id: data.id || 'VEST-01',
      seq: data.seq || 0,
      timestamp: new Date().toLocaleTimeString(),
      status: data.status || data.st || 'AMAN',
      riskScore: data.risk ?? data.rk ?? 0,
      spo2: Number(data.vit?.spo2 ?? data.sp ?? data.spo2 ?? 0),
      heartRate: Number(data.vit?.hr ?? data.hr ?? data.heartRate ?? 0),
      waistWater: Number(data.vit?.w_waist ?? data.ww ?? data.waistWater ?? 0),
      neckWater: Number(data.vit?.w_neck ?? data.wn ?? data.neckWater ?? 0),
      isSubmerged: Boolean(data.vit?.sub ?? data.sub ?? data.isSubmerged ?? false),
      inWater: Boolean(data.vit?.water ?? data.inWater ?? false),
      latitude: Number(data.gps?.lat ?? data.lat ?? data.latitude ?? -6.3627),
      longitude: Number(data.gps?.lng ?? data.lon ?? data.longitude ?? 106.8272),
      satellites: Number(data.gps?.sat ?? data.sat ?? data.satellites ?? 0),
      probAman: Number(data.probAman ?? (data.status === 'AMAN' ? 0.92 : 0.05)),
      probWaspada: Number(data.probWaspada ?? (data.status === 'WASPADA' ? 0.85 : 0.10)),
      probKritis: Number(data.probKritis ?? (data.status === 'KRITIS' ? 0.95 : 0.03)),
    };
  }
}

export const bleService = new BLEService();
