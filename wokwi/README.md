# 🦺 DROWNT - Smart Life Vest Wokwi Simulation Guide
> **Kelompok 33 — Desain Proyek 2 (FTUI)**

File proyek ini sudah siap 100% untuk dijalankan di simulator **Wokwi** (ESP32).

---

## 📁 File yang Tersedia di Proyek Ini:
1. **[`diagram.json`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/diagram.json)**: Tata letak rangkaian sirkuit Wokwi (ESP32, MPU6050, Layar OLED, Potentiometer SpO2, Potentiometer Suhu, Pushbutton Sensor Air, Buzzer, LED Merah & Hijau).
2. **[`sketch.ino`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/sketch.ino)**: Firmware ESP32 berbasis **FreeRTOS Multitasking** (Sensing, Filtering, Weighted Risk Scoring, Alert UI, JSON Telemetry).
3. **[`libraries.txt`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/libraries.txt)**: Daftar pustaka Arduino yang dibutuhkan di Wokwi.

---

## 🚀 Cara Menjalankan di Wokwi:

1. Buka browser dan pergi ke **[https://wokwi.com](https://wokwi.com)**.
2. Pilih project **ESP32** (atau buka [wokwi.com/projects/new/esp32](https://wokwi.com/projects/new/esp32)).
3. **Copas Diagram Sirkuit:**
   - Buka tab file `diagram.json` di Wokwi.
   - Hapus semua isinya, lalu copas isi file **[`diagram.json`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/diagram.json)** ke sana.
4. **Copas Kode Firmware:**
   - Buka tab `sketch.ino` di Wokwi.
   - Hapus isinya, lalu copas isi file **[`sketch.ino`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/sketch.ino)** ke sana.
5. **Tambahkan Libraries:**
   - Di tab **Library Manager** (ikon buku atau file `libraries.txt`), tambahkan baris berikut:
     ```text
     Adafruit MPU6050
     Adafruit SSD1306
     Adafruit GFX Library
     Adafruit Unified Sensor
     ArduinoJson
     ```
6. Tekan tombol **Play ▶ (Start Simulation)** di Wokwi!

---

## 🧪 Skenario Pengujian Interaktif di Wokwi:

| Skenario | Aksi di Simulator | Reaksi Sistem |
| :--- | :--- | :--- |
| **1. Kondisi Normal (AMAN)** | Biarkan slider SpO2 di atas 95%, suhu normal 36.5°C, tombol air tidak ditekan. | LED Hijau menyala tenang, Buzzer mati, status OLED: `AMAN (Skor < 40)`. |
| **2. Deteksi Terendam Air** | Tekan/tahan tombol **Water Sensor** (biru). | Skor risiko naik +20 poin, status berubah menjadi **WASPADA**, Buzzer mulai berbunyi bip pendek perlahan. |
| **3. Posisi Tengkurap (Face-Down)** | Klik sensor **MPU6050**, putar sudut roll atau rotasi ke arah bawah. | OLED menampilkan `Post.: FACE-DOWN!`. |
| **4. Kondisi Fatal Drowning (KRITIS)** | Tekan tombol air + putar MPU6050 tengkurap + turunkan slider SpO2 ke <90%. | **Skor Risiko melonjak $\ge 70$ (KRITIS)**: LED Merah berkedip cepat, Buzzer berbunyi sirine nada tinggi terus-menerus, Serial Monitor mengirim alert darurat! |
