# 🦺 DROWNT - Smart Life Vest System (TinyML Edge AI & Wokwi)
> **Kelompok 33 — Desain Proyek 2 (Teknik Komputer FTUI)**  
> *A Wearable Solution for Early Drowning Detection and Human Safety Monitoring*

Proyek ini telah dikembangkan dengan arsitektur **Edge AI / TinyML (Machine Learning on ESP32)** menggunakan model **Random Forest Classifier** yang ditranspilasi langsung ke bahasa C/C++. Model melakukan inferensi on-device secara *real-time* di ESP32 tanpa butuh ketergantungan koneksi cloud.

---

## 📁 Struktur Repositori

```text
Proyek Lifevest/
│
├── wokwi/                          # Folder Simulasi & Firmware ESP32
│   ├── diagram.json                # Tata letak sirkuit Wokwi (ESP32, MPU6050, OLED, Pot, Buzzer, LED)
│   ├── sketch.ino                  # Firmware FreeRTOS multitasking + Edge AI integration
│   ├── drownt_model.h              # Header C++ model Random Forest siap compile di ESP32
│   ├── libraries.txt               # Daftar library Arduino untuk Wokwi
│   └── README.md                   # Panduan step-by-step Wokwi
│
├── machine_learning/               # Folder Pelatihan & Verifikasi Machine Learning
│   ├── train_model.py              # Script training Random Forest (evaluasi akurasi, F1, & export C++)
│   ├── drownt_model.h              # Model hasil transpilasi C++ murni
│   ├── simulate_cli.py             # Simulator visual interaktif di terminal
│   ├── test_model.cpp              # Script pengujian native C++
│   ├── test_model.exe              # Executable pengujian validasi C++
│   └── fix_header.py               # Tool helper perbaikan sintaks C++
│
└── README.md                       # Dokumentasi utama proyek
```

---

## 🧪 Cara Menjalankan Uji Coba Lokal

### 1. Interactive Terminal Simulator:
```powershell
python .\machine_learning\simulate_cli.py
```
Atau uji skenario instan:
- `python .\machine_learning\simulate_cli.py 1` (Aman / Normal)
- `python .\machine_learning\simulate_cli.py 2` (Waspada / Mengapung di air)
- `python .\machine_learning\simulate_cli.py 3` (Kritis / Hipotermia air dingin)
- `python .\machine_learning\simulate_cli.py 4` (Kritis / Hipoksia SpO2 78%)
- `python .\machine_learning\simulate_cli.py 5` (Kritis / Pingsan tengkurap di air)

### 2. Validasi C++ Header ESP32:
```powershell
.\machine_learning\test_model.exe
```

---

## 🚀 Cara Menjalankan di Wokwi:
1. Buka [wokwi.com/projects/new/esp32](https://wokwi.com/projects/new/esp32).
2. Copas isi file [`wokwi/diagram.json`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/wokwi/diagram.json) ke tab `diagram.json`.
3. Tambahkan tab baru **`drownt_model.h`** di Wokwi dan copas isi [`wokwi/drownt_model.h`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/wokwi/drownt_model.h).
4. Copas isi file [`wokwi/sketch.ino`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/wokwi/sketch.ino) ke tab `sketch.ino`.
5. Masukkan library dari [`wokwi/libraries.txt`](file:///c:/Users/esun/College/Semester%207/Despro%202/Proyek%20Lifevest/wokwi/libraries.txt) ke Library Manager.
6. Klik **Play ▶**!
"# Smart-Life-Vest-DROWNT" 
