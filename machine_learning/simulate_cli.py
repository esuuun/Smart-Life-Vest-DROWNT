"""
Interactive Terminal Simulator for Smart Life Vest DROWNT (Edge AI)
Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI)
"""

import sys
import json
import numpy as np

# Force UTF-8 on Windows console if supported
if sys.platform == "win32":
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:
        pass

from sklearn.ensemble import RandomForestClassifier

def train_quick_model():
    np.random.seed(42)
    N = 6000
    records = []
    labels = []
    for _ in range(N):
        scenario = np.random.choice(
            ['normal', 'water_safe', 'hypothermia', 'mild_hypoxia', 'drowning_critical', 'unconscious_facedown'], 
            p=[0.30, 0.20, 0.12, 0.13, 0.15, 0.10]
        )
        if scenario == 'normal':
            records.append([np.random.uniform(95, 100), np.random.uniform(65, 95), np.random.uniform(36.2, 37.5), 0, 0, 0, 0])
            labels.append(0)
        elif scenario == 'water_safe':
            records.append([np.random.uniform(94, 99), np.random.uniform(80, 115), np.random.uniform(35.0, 36.8), 1, 10, -10, 0])
            labels.append(1)
        elif scenario == 'hypothermia':
            temp = np.random.uniform(28.0, 34.5)
            fd = 0 if np.random.rand() > 0.3 else 1
            records.append([np.random.uniform(90, 96), np.random.uniform(45, 75), temp, 1, 0, 0, fd])
            labels.append(2 if temp < 32.0 or fd == 1 else 1)
        elif scenario == 'mild_hypoxia':
            records.append([np.random.uniform(89, 93), np.random.uniform(100, 135), np.random.uniform(34.8, 36.5), 1, 0, 0, 0])
            labels.append(1)
        elif scenario == 'drowning_critical':
            records.append([np.random.uniform(70, 88), np.random.uniform(130, 160), np.random.uniform(31, 35.5), 1, 0, 0, 1 if np.random.rand() > 0.3 else 0])
            labels.append(2)
        elif scenario == 'unconscious_facedown':
            records.append([np.random.uniform(70, 85), np.random.uniform(40, 80), np.random.uniform(30, 35), 1, -45, 160, 1])
            labels.append(2)
            
    clf = RandomForestClassifier(n_estimators=15, max_depth=6, random_state=42)
    clf.fit(records, labels)
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
    p_safe, p_warn, p_crit = probs[0]*100, probs[1]*100, probs[2]*100
    risk = int(probs[1]*50.0 + probs[2]*100.0)
    
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
        "p_crit": p_crit
    }
    
    print("\n[TAMPILAN DISPLAY OLED LIFE VEST]:")
    display_oled_ascii(data)
    print(f"Status Aktuator : Buzzer -> {buzzer}")
    print(f"                  LED    -> {led}")
    
    # Telemetri SAR
    payload = {
        "device_id": "VEST-33-01",
        "ml_status": status,
        "risk_score": risk,
        "ai_probabilities": {"safe": f"{p_safe:.1f}%", "warning": f"{p_warn:.1f}%", "critical": f"{p_crit:.1f}%"},
        "vitals": {"spo2": int(feat[0]), "hr": int(feat[1]), "temp_c": round(feat[2], 1)},
        "environment": {"in_water": bool(feat[3]), "face_down": bool(feat[6])},
        "gps": {"lat": -6.2088, "lon": 106.8456}
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
