# 🦺 DROWNT — Smart Life Vest with TinyML Edge AI & LoRa

> **Kelompok 33 — Desain Proyek 2 (Teknik Komputer, Fakultas Teknik Universitas Indonesia)**  
> *A Wearable Solution for Early Drowning Detection and Maritime Safety Monitoring*  
> **Dosen Pembimbing:** Siti Fauziyah Rahman, Ph. D

---

## 📌 Ringkasan Proyek

Tenggelam (*drowning*) merupakan salah satu krisis kesehatan publik yang dapat dicegah (*preventable public health crisis*). Lebih dari 50% kasus tenggelam global terjadi di kawasan Asia Pasifik. Dalam konteks rekreasi air, aktivitas nelayan, maupun bencana banjir, korban dapat mengalami penurunan saturasi oksigen (**SpO2**) dan kehilangan kesadaran (*hypoxia-induced unconsciousness*) dalam hitungan menit sebelum tim penyelamat tiba di lokasi.

**DROWNT** adalah sistem rompi pelampung cerdas (*Smart Life Vest*) terintegrasi yang menggabungkan:
1. **Edge AI / TinyML:** Model klasifikasi *Random Forest* yang berjalan secara *on-device* di mikrokontroler **ESP32-S3**, mendeteksi status kegentingan korban (`AMAN`, `WASPADA`, `KRITIS`) dalam waktu < 1 ms tanpa butuh koneksi internet/cloud.
2. **Aktuator Tanggap Darurat Lokal:** Memicu alarm sirine piezo dan mekanisme inflasi tabung CO2 otomatis saat korban berada dalam kondisi kritis/pingsan telungkup.
3. **Telemetri Jarak Jauh LoRa SX1276:** Mentransmisikan koordinat GPS korban dan tanda-tanda vital menembus gelombang laut hingga jangkauan 1–5 km.
4. **Tactical SAR Mission Control Dashboard:** Antarmuka web modern berbasis **React.js** dengan pelacak peta interaktif (Leaflet/OpenStreetMap), pemantauan tanda vital real-time, dan konektivitas langsung via **Web Serial API**.

---

## 🏗️ Arsitektur Alur Sistem (*End-to-End Flow*)

```
[ ROMPI PELAMPUNG (WEARABLE VEST) ]
MAX30102 (SpO2/HR) ──┐
MAX30205 (Suhu)    ──┼─> [ ESP32-S3 Edge AI ] ──> [ TinyML Random Forest ] ──> [ SX1276 LoRa TX ]
MPU6050 (IMU)      ──┤       FreeRTOS Core 1           (drownt_model.h)           (915 MHz Radio)
Water Sensor (Air) ──┤                                                                   │
NEO-M8N (GPS)      ──┘                                                                   │ Gelombang Radio
                                                                                         │ Jarak Jauh (1-5 km)
                                                                                         ▼
[ POSKO PENYELAMAT (BASE STATION) ]                                             [ SX1276 LoRa RX ]
[ React.js Dashboard ] <── Web Serial API <── [ ESP32 Hub Penerima ] <──────────────────┘
  (Leaflet Live Map)        (USB Serial)        (Meneruskan JSON)
```

### ⏱️ Tahapan Kerja Sistem:
1. **Sensors Acquisition (Tiap 100 ms):**
   - **MAX30102:** Mengukur saturasi oksigen darah (SpO2 %) dan denyut nadi (Heart Rate BPM).
   - **MAX30205:** Membaca suhu tubuh klinis (°C) untuk deteksi awal hipotermia.
   - **MPU6050:** Mengukur percepatan 3-sumbu, menghitung sudut kemiringan (*Pitch & Roll*), dan mendeteksi apakah wajah korban tertelungkup menghadap air (**`isFaceDown = 1`**).
   - **Water Sensor:** Mendeteksi kontak air secara konduktif (**`inWater = 1`**).
   - **u-blox NEO-M8N:** Membaca koordinat satelit GPS secara terus-menerus (*Latitude, Longitude, Satellites*).
2. **Edge AI Inference (Tiap 500 ms):**
   - 7 fitur sensor diproses oleh fungsi `predict_drownt_status()` on-device.
   - Menghasilkan probabilitas kelas:
     - `0 = AMAN` (Mengapung normal telentang, pernapasan stabil).
     - `1 = WASPADA` (Tercebur ke air, tanda vital stabil namun dalam pantauan).
     - `2 = KRITIS` (Hipoksia SpO2 < 85%, takikardia/bradikardia near-drowning, atau pingsan telungkup di air).
3. **Local Safety Triggers:**
   - Kondisi `KRITIS` langsung menyalakan sirine buzzer piezo 100dB dan memicu katup solenoid inflasi kantong udara pelampung.
4. **LoRa Wireless Telemetry:**
   - ESP32-S3 memancarkan paket data JSON melalui frekuensi 915 MHz.
   - Tingkat transmisi adaptif: AMAN (tiap 10 detik), WASPADA (tiap 3 detik), KRITIS (tiap 1 detik).
5. **SAR Mission Control Dashboard:**
   - Diterima oleh Hub LoRa posko pantai yang terhubung via USB ke laptop operator SAR.
   - Peta bergerak real-time, grafik vital signs ter-update, dan alarm sirine browser berbunyi.

---

## 📌 Pemetaan Pinout Hardware (PCB ESP32-S3 KiCad)

| Modul / Komponen | Jalur Antarmuka | Pin ESP32-S3 | Catatan Skematik |
|---|---|---|---|
| **MAX30102** (SpO2 & HR) | I2C SCL | **GPIO 4** | Pull-up 4.7k (R1) ke 3V3 |
| | I2C SDA | **GPIO 5** | Pull-up 4.7k (R2) ke 3V3 |
| | Interrupt | **GPIO 8** | Terhubung ke pin INT MAX30102 |
| **NEO-M8N** (GPS) | UART RX (ESP32) | **GPIO 18** | Terhubung ke pin TXD GPS |
| | UART TX (ESP32) | **GPIO 17** | Terhubung ke pin RXD GPS |
| **SX1276** (LoRa) | SPI SCK | **GPIO 14** | Clock SPI |
| | SPI MISO | **GPIO 15** | Data In |
| | SPI MOSI | **GPIO 16** | Data Out |
| | SPI NSS / CS | **GPIO 13** | Chip Select |
| | RESET | **GPIO 12** | Reset Pin |
| | DIO0 | **GPIO 11** | Packet TX/RX Done Interrupt |
| **MPU6050** (IMU) | I2C | **GPIO 4 (SCL), GPIO 5 (SDA)** | Paralel di bus I2C (Address `0x68`) |
| **Water Detector** | Digital / ADC | **GPIO 1** | Header sensor air |
| **Buzzer / Alarm** | Output | **GPIO 2** | Piezo alarm sirine |
| **Solenoid Inflasi** | Output | **GPIO 21** | Pemicu katup CO2 otomatis |
| **Status LED** | Output | **GPIO 38** | Indikator visual onboard |

---

## 📁 Struktur Repositori

```text
Smart-Life-Vest-DROWNT/
│
├── dashboard/                      # Tactical SAR Web Dashboard (React.js + Vite)
│   ├── src/
│   │   ├── components/
│   │   │   ├── Header.jsx          # Bar navigasi, Web Serial, Theme Toggle, CSV Export
│   │   │   ├── StatsBar.jsx        # HUD tanda vital (SpO2, HR, Suhu, Postur, Risk Index)
│   │   │   ├── LiveMap.jsx         # Peta interaktif Leaflet + OpenStreetMap + Breadcrumbs
│   │   │   ├── MLDiagnostics.jsx   # Visualisasi probabilitas TinyML Random Forest
│   │   │   ├── TelemetryLog.jsx    # Monospace terminal log paket LoRa/Serial real-time
│   │   │   └── SimulatorControls.jsx# Panel skenario demo instan tanpa hardware
│   │   ├── services/
│   │   │   └── serialService.js    # Web Serial API driver & Simulator generator
│   │   ├── App.jsx                 # Komponen utama aplikasi
│   │   └── index.css               # Design system palet Deep Forest Green & Sage
│   ├── package.json
│   └── README.md
│
├── firmware/                       # Firmware Produksi ESP32-S3 (Physical Hardware)
│   ├── config_pins.h               # Definisi pemetaan pinout skematik PCB KiCad
│   ├── drownt_model.h              # Header C model TinyML Random Forest siap pakai
│   ├── firmware.ino                # Firmware utama Dual-Core FreeRTOS + LoRa + GPS + AI
│   └── README.md                   # Panduan build & flash firmware
│
├── machine_learning/               # Training & Validasi Model AI
│   ├── train_model.py              # Script training model Random Forest & export ke C
│   ├── drownt_model.h              # Model terkompilasi dalam bahasa C
│   ├── simulate_cli.py             # Simulator visual interaktif di terminal (CLI)
│   ├── test_model.cpp              # Script pengujian native C++
│   └── test_model.exe              # Executable validasi model
│
├── wokwi/                          # Simulasi Sirkuit Virtual Wokwi
│   ├── diagram.json                # Skematik virtual Wokwi
│   ├── sketch.ino                  # Sketch simulasi Wokwi
│   └── drownt_model.h
│
├── .gitignore
└── README.md                       # Dokumentasi utama proyek
```

---

## 🚀 Panduan Menjalankan Sistem

### 1. Menjalankan Dashboard React.js (SAR Console)
Pastikan Node.js sudah terpasang di komputer Anda.
```bash
# Pindah ke direktori dashboard
cd dashboard

# Pasang dependensi
npm install

# Jalankan local development server
npm run dev
```
Buka browser di **`http://localhost:5173/`**.  
* **Light / Dark Mode:** Klik tombol ikon Matahari/Bulan di bar atas.
* **Demo Sidang (Tanpa Hardware):** Klik tombol **"Demo Simulator"** dan pilih salah satu skenario pengujian.
* **Koneksi ke Alat Asli:** Colok ESP32 ke port USB laptop, lalu klik tombol **"Connect ESP32"**.

### 2. Memprogram Firmware ke ESP32-S3 (Physical PCB)
1. Buka Arduino IDE.
2. Buka berkas [`firmware/firmware.ino`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/firmware/firmware.ino).
3. Pasang library yang dibutuhkan via Library Manager:
   - `Adafruit MPU6050` & `Adafruit Unified Sensor`
   - `TinyGPSPlus`
   - `LoRa` (oleh Sandeep Mistry)
   - `ArduinoJson` (v6 / v7)
4. Pilih Board: **ESP32S3 Dev Module**.
5. Pilih Port COM perangkat Anda dan klik **Upload ▶**.

### 3. Menguji Model Machine Learning di Komputer
```bash
# Jalankan simulator terminal interaktif
python .\machine_learning\simulate_cli.py

# Atau uji skenario instan:
python .\machine_learning\simulate_cli.py 1   # Aman (Berenang normal)
python .\machine_learning\simulate_cli.py 2   # Waspada (Tercebur ke air)
python .\machine_learning\simulate_cli.py 3   # Kritis (Hipotermia)
python .\machine_learning\simulate_cli.py 4   # Kritis (Hipoksia berat SpO2 < 80%)
python .\machine_learning\simulate_cli.py 5   # Kritis (Pingsan telungkup di air)
```

---

## 👥 Tim Pengembang (Kelompok 33 FTUI)
* **Departemen Teknik Elektro & Komputer, Fakultas Teknik Universitas Indonesia**
* Desain Proyek 2 — 2026
