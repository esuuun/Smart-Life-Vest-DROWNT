# Dokumentasi Firmware ESP32-S3 DROWNT (Smart Life Vest)

Firmware ini dirancang khusus untuk **ESP32-S3-MINI-1** berdasarkan skematik PCB KiCad tim Despro 2 Kelompok 33.

---

## 📌 Pemetaan Pinout (Sesuai Skematik PCB)

| Komponen / Modul | Antarmuka / Jalur | Pin ESP32-S3 | Keterangan di Skematik |
|---|---|---|---|
| **MAX30102** (SpO2 & HR) | I2C SCL | **GPIO 4** | Pull-up 4.7k (R1) ke 3V3 |
| | I2C SDA | **GPIO 5** | Pull-up 4.7k (R2) ke 3V3 |
| | Interrupt | **GPIO 8** | Terhubung ke pin INT MAX30102 |
| **NEO-M8N** (GPS) | UART RX (ESP32) | **GPIO 18** | Menerima data dari TXD GPS |
| | UART TX (ESP32) | **GPIO 17** | Mengirim sinyal ke RXD GPS |
| **SX1276** (LoRa) | SPI SCK | **GPIO 14** | SCK LoRa |
| | SPI MISO | **GPIO 15** | MISO LoRa |
| | SPI MOSI | **GPIO 16** | MOSI LoRa |
| | SPI NSS / CS | **GPIO 13** | Chip Select |
| | RESET | **GPIO 12** | Reset Pin |
| | DIO0 | **GPIO 11** | Packet TX/RX Done Interrupt |
| **MPU6050** (IMU) | I2C | **GPIO 4 (SCL), GPIO 5 (SDA)** | Paralel di bus I2C (Address `0x68`) |
| **Water Detector** | Digital / ADC | **GPIO 1** | Header cadangan sensor air |
| **Buzzer / Alarm** | Output | **GPIO 2** | Piezo buzzer / sirine |
| **Solenoid Inflasi** | Output | **GPIO 21** | Pemicu katup CO2 otomatis |
| **Status LED** | Output | **GPIO 38** | Indikator visual |

---

## 📦 Library Arduino yang Dibutuhkan

Pastikan library berikut sudah terpasang di Arduino IDE / PlatformIO:
1. `Adafruit MPU6050` & `Adafruit Unified Sensor` (oleh Adafruit)
2. `TinyGPSPlus` (oleh Mikal Hart)
3. `LoRa` (oleh Sandeep Mistry)
4. `ArduinoJson` (oleh Benoit Blanchon - versi 6.x / 7.x)

---

## ⚙️ Cara Flash / Upload ke ESP32-S3

1. **Board Selection:** `ESP32S3 Dev Module`
2. **USB CDC On Boot:** `Enabled` (Jika menggunakan port USB native ESP32-S3)
3. **Flash Size:** `4MB` atau `8MB` (sesuai modul ESP32-S3-MINI-1)
4. **Partition Scheme:** `Default 4MB with spiffs (1.2MB APP)`

---

## ⚠️ Catatan Penting untuk Teman Bagian Hardware:
Pastikan port programming tidak terlewat pada PCB:
- Hubungkan pin **GPIO 19 (USB D-)** dan **GPIO 20 (USB D+)** ke konektor USB Type-C.
- ATAU sediakan pin header UART: **TXD0 (GPIO 43)**, **RXD0 (GPIO 44)**, **IO0 (Boot)**, **EN (Reset)**, **3V3**, dan **GND**.
