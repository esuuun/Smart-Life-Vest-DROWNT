"""
Interactive Terminal Simulator for Smart Life Vest DROWNT (Edge AI) — v2
Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI)

PERUBAHAN DARI v1:
- Model sekarang dilatih memakai build_dataset() dari train_model_v2.py,
  bukan generator terpisah -> menjamin CLI simulator dan model yang
  di-export ke ESP32 (drownt_model.h) punya karakter yang SAMA PERSIS.
  Di v1, dua model ini diam-diam berbeda (pitch/roll di-hardcode di CLI,
  di-random di train_model.py) -- bug ini sekarang hilang.
"""

import sys
import json

# Force UTF-8 on Windows console if supported
if sys.platform == "win32":
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:
        pass

from sklearn.ensemble import RandomForestClassifier
from train_model import build_dataset


def train_quick_model():
    X, y = build_dataset(n=6000, seed=42)
    clf = RandomForestClassifier(n_estimators=15, max_depth=6, random_state=42)
    clf.fit(X, y)
    return clf


clf = train_quick_model()

PRESETS = {
    "1": ("Normal (Di Darat / Aman)", [98.0, 75.0, 36.6, 0, 5.0, 0.0, 0]),
    "2": ("Mengapung di Air (Sadar)", [96.0, 92.0, 36.0, 1, 10.0, -15.0, 0]),
    "3": ("Hipotermia Air Dingin (30.5 C)", [92.0, 52.0, 30.5, 1, 0.0, 10.0, 0]),
    "4": ("Hipoksia Akut Drowning (SpO2 78%)", [78.0, 145.0, 34.2, 1, -20.0, 30.0, 0]),
    "5": ("Pingsan Tengkurap (Face-Down)", [74.0, 48.0, 33.0, 1, -45.0, 160.0, 1]),
}


def display_oled_ascii(d):
    print("+------------------------------------------------------------+")
    print(f"|  AI STATUS: {d['status']:<7} (Risk: {d['risk_score']:>2}/100)                         |")
    print("+------------------------------------------------------------+")
    print(f"|  SpO2 : {d['spo2']:>3.0f}%   |  Heart Rate: {d['hr']:>3} BPM                         |")
    print(f"|  Temp : {d['temp']:>4.1f} C  |  Air: {'TERENDAM' if d['in_water'] else 'KERING  ':<8}                        |")
    print(f"|  Post.: {'TENGKURAP (FACE-DOWN)' if d['face_down'] else 'TELENTANG / NORMAL ':<24}                       |")
    print("+------------------------------------------------------------+")
    print(f"|  P(AMAN): {d['p_safe']:>4.1f}% | P(WASPADA): {d['p_warn']:>4.1f}% | P(KRITIS): {d['p_crit']:>4.1f}%  |")
    print("+------------------------------------------------------------+")


def run_simulation(feat):
    probs = clf.predict_proba([feat])[0]
    p_safe, p_warn, p_crit = probs[0] * 100, probs[1] * 100, probs[2] * 100
    risk = int(probs[1] * 50.0 + probs[2] * 100.0)

    # CATATAN: threshold di bawah ini masih tebakan awal (belum dikalibrasi
    # dari data validasi nyata). Perlu direvisi setelah ada data semi-real.
    if probs[2] > 0.45 or risk >= 70:
        status = "KRITIS"
        buzzer = "[ALARM AKTIF] BIP CEPAT 2200 Hz"
        led = "[MERAH] BERKEDIP CEPAT"
    elif probs[1] > 0.40 or risk >= 40:
        status = "WASPADA"
        buzzer = "[WASPADA] Bip periodik 1000 Hz"
        led = "[KUNING / MERAH+HIJAU]"
    else:
        status = "AMAN"
        buzzer = "[SILENT] Mati"
        led = "[HIJAU] Menyala tenang"

    data = {
        "status": status,
        "risk_score": risk,
        "spo2": feat[0],
        "hr": int(feat[1]),
        "temp": feat[2],
        "in_water": bool(feat[3]),
        "face_down": bool(feat[6]),
        "p_safe": p_safe,
        "p_warn": p_warn,
        "p_crit": p_crit,
    }

    print("\n[TAMPILAN DISPLAY OLED LIFE VEST]:")
    display_oled_ascii(data)
    print(f"Status Aktuator : Buzzer -> {buzzer}")
    print(f"                  LED    -> {led}")

    payload = {
        "device_id": "VEST-33-01",
        "ml_status": status,
        "risk_score": risk,
        "ai_probabilities": {"safe": f"{p_safe:.1f}%", "warning": f"{p_warn:.1f}%", "critical": f"{p_crit:.1f}%"},
        "vitals": {"spo2": int(feat[0]), "hr": int(feat[1]), "temp_c": round(feat[2], 1)},
        "environment": {"in_water": bool(feat[3]), "face_down": bool(feat[6])},
        "gps": {"lat": -6.2088, "lon": 106.8456},
    }
    print("\n[TELEMETRI SAR (JSON DISPATCH)]:")
    print(json.dumps(payload, indent=2))
    print()


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] in PRESETS:
        name, feat = PRESETS[sys.argv[1]]
        print(f"=== Menjalankan Skenario: {name} ===")
        run_simulation(feat)
    else:
        print("==========================================================")
        print("  DROWNT INTERACTIVE SIMULATOR (TINYML / EDGE AI)         ")
        print("==========================================================")
        print("Pilih skenario uji:")
        for k, v in PRESETS.items():
            print(f"  [{k}] {v[0]}")
        choice = input("\nMasukkan nomor skenario [1-5] (atau 'q' untuk keluar): ").strip()
        if choice in PRESETS:
            name, feat = PRESETS[choice]
            print(f"\n>>> Skenario Terpilih: {name}")
            run_simulation(feat)
        else:
            print("Keluar.")