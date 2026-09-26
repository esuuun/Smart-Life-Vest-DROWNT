/**
 * @file serialService.js
 * @brief Layanan Web Serial API untuk koneksi port USB ESP32-S3 dan Simulator Skenario SAR
 * Departemen Teknik Elektro & Komputer FTUI - Kelompok 33
 */

class SerialService {
  constructor() {
    this.port = null;
    this.reader = null;
    this.readableStreamClosed = null;
    this.keepReading = false;
    this.simInterval = null;
  }

  isSupported() {
    return 'serial' in navigator;
  }

  async connect(onDataReceived, onStatusChange) {
    if (!this.isSupported()) {
      throw new Error('Web Serial API tidak didukung di browser ini. Gunakan Google Chrome atau Microsoft Edge terbaru.');
    }

    try {
      this.port = await navigator.serial.requestPort();
      await this.port.open({ baudRate: 115200 });

      onStatusChange({ connected: true, portInfo: this.port.getInfo() });
      this.keepReading = true;

      const textDecoder = new TextDecoderStream();
      this.readableStreamClosed = this.port.readable.pipeTo(textDecoder.writable);
      const reader = textDecoder.readable.getReader();
      this.reader = reader;

      let lineBuffer = '';

      while (this.keepReading) {
        const { value, done } = await reader.read();
        if (done) break;
        if (value) {
          lineBuffer += value;
          const lines = lineBuffer.split('\n');
          lineBuffer = lines.pop(); // Sisa potongan kalimat yang belum selesai

          for (const line of lines) {
            const trimmed = line.trim();
            if (!trimmed) continue;
            
            // Coba parse format JSON yang dikirimkan ESP32
            try {
              if (trimmed.startsWith('{') && trimmed.endsWith('}')) {
                const parsed = JSON.parse(trimmed);
                onDataReceived(this.normalizeTelemetry(parsed));
              } else if (trimmed.includes('[TELEMETRY]')) {
                // Alternatif parse log text
                console.log('ESP32 Log:', trimmed);
              }
            } catch (err) {
              console.warn('Gagal parse serial line:', trimmed, err);
            }
          }
        }
      }
    } catch (err) {
      onStatusChange({ connected: false, error: err.message });
      throw err;
    }
  }

  async disconnect(onStatusChange) {
    this.keepReading = false;
    if (this.reader) {
      await this.reader.cancel();
    }
    if (this.readableStreamClosed) {
      await this.readableStreamClosed.catch(() => {});
    }
    if (this.port) {
      await this.port.close();
      this.port = null;
    }
    if (onStatusChange) {
      onStatusChange({ connected: false });
    }
  }

  // Menyeragamkan format data dari hardware atau simulator
  normalizeTelemetry(data) {
    return {
      id: data.id || 'VEST-01',
      seq: data.seq || 0,
      timestamp: new Date().toLocaleTimeString(),
      status: data.status || (data.predictedClass === 2 ? 'KRITIS' : data.predictedClass === 1 ? 'WASPADA' : 'AMAN'),
      riskScore: data.risk ?? data.riskScore ?? 0,
      spo2: Number(data.vit?.spo2 ?? data.spo2 ?? 0),
      heartRate: Number(data.vit?.hr ?? data.heartRate ?? 0),
      waistWater: Number(data.vit?.w_waist ?? data.waistWater ?? (data.vit?.water ? 100 : 0)),
      neckWater: Number(data.vit?.w_neck ?? data.neckWater ?? (data.vit?.sub ? 100 : 0)),
      isSubmerged: Boolean(data.vit?.sub ?? data.isSubmerged ?? false),
      inWater: Boolean(data.vit?.water ?? data.inWater ?? false),
      pitch: Number(data.pitch ?? 0),
      roll: Number(data.roll ?? 0),
      latitude: Number(data.gps?.lat ?? data.latitude ?? -6.3627),
      longitude: Number(data.gps?.lng ?? data.longitude ?? 106.8272),
      satellites: Number(data.gps?.sat ?? data.satellites ?? 8),
      probAman: Number(data.probAman ?? (data.status === 'AMAN' ? 0.92 : 0.05)),
      probWaspada: Number(data.probWaspada ?? (data.status === 'WASPADA' ? 0.85 : 0.10)),
      probKritis: Number(data.probKritis ?? (data.status === 'KRITIS' ? 0.95 : 0.03)),
    };
  }

  // Simulator Generator untuk Pengujian Tanpa Hardware Fisik (Demo Sidang)
  startSimulator(scenarioName, onDataReceived) {
    this.stopSimulator();

    let seq = 1;
    // Titik awal: Danau Kenanga Rektorat UI Depok
    let lat = -6.3627;
    let lng = 106.8272;

    this.simInterval = setInterval(() => {
      // Simulasi pergeseran koordinat terbawa arus air (drifting)
      lat += (Math.random() - 0.48) * 0.00008;
      lng += (Math.random() - 0.48) * 0.00008;

      let payload = {
        id: 'VEST-01',
        seq: seq++,
        latitude: lat,
        longitude: lng,
        satellites: 9 + Math.floor(Math.random() * 3),
      };

      if (scenarioName === 'NORMAL') {
        payload = {
          ...payload,
          status: 'AMAN',
          riskScore: Math.floor(4 + Math.random() * 8),
          spo2: Math.floor(97 + Math.random() * 3),
          heartRate: Math.floor(70 + Math.random() * 10),
          temperature: +(36.4 + Math.random() * 0.4).toFixed(1),
          inWater: false,
          isFaceDown: false,
          pitch: +(Math.random() * 6 - 3).toFixed(1),
          roll: +(Math.random() * 6 - 3).toFixed(1),
          probAman: 0.94,
          probWaspada: 0.05,
          probKritis: 0.01
        };
      } else if (scenarioName === 'WASPADA') {
        payload = {
          ...payload,
          status: 'WASPADA',
          riskScore: Math.floor(40 + Math.random() * 15),
          spo2: Math.floor(92 + Math.random() * 3),
          heartRate: Math.floor(105 + Math.random() * 15),
          temperature: +(35.0 + Math.random() * 0.5).toFixed(1),
          inWater: true,
          isFaceDown: false,
          pitch: +(Math.random() * 20 - 10).toFixed(1),
          roll: +(Math.random() * 30 - 15).toFixed(1),
          probAman: 0.15,
          probWaspada: 0.78,
          probKritis: 0.07
        };
      } else if (scenarioName === 'KRITIS_HYPOXIA') {
        payload = {
          ...payload,
          status: 'KRITIS',
          riskScore: Math.floor(88 + Math.random() * 10),
          spo2: Math.floor(76 + Math.random() * 6),
          heartRate: Math.floor(140 + Math.random() * 20),
          temperature: +(32.8 + Math.random() * 0.6).toFixed(1),
          inWater: true,
          isFaceDown: false,
          pitch: +(Math.random() * 35 - 17).toFixed(1),
          roll: +(Math.random() * 45 - 22).toFixed(1),
          probAman: 0.02,
          probWaspada: 0.08,
          probKritis: 0.90
        };
      } else if (scenarioName === 'KRITIS_FACEDOWN') {
        payload = {
          ...payload,
          status: 'KRITIS',
          riskScore: 99,
          spo2: Math.floor(70 + Math.random() * 5),
          heartRate: Math.floor(45 + Math.random() * 8), // Bradikardia / Near-drowning
          temperature: +(31.2 + Math.random() * 0.4).toFixed(1),
          inWater: true,
          isFaceDown: true, // Tengkurap di air
          pitch: +(65.0 + Math.random() * 10).toFixed(1),
          roll: +(Math.random() * 20 - 10).toFixed(1),
          probAman: 0.01,
          probWaspada: 0.02,
          probKritis: 0.97
        };
      }

      onDataReceived(this.normalizeTelemetry(payload));
    }, 1500);
  }

  stopSimulator() {
    if (this.simInterval) {
      clearInterval(this.simInterval);
      this.simInterval = null;
    }
  }
}

export const serialService = new SerialService();
