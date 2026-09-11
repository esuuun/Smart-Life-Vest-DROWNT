"""
Pelatihan Model Machine Learning (TinyML) untuk Smart Life Vest DROWNT — v2
Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI)

PERUBAHAN DARI v1:
1. Noise sensor ditambahkan ke SEMUA fitur (meniru MAX30102/MAX30205/MPU6050 asli,
   termasuk motion artifact saat gerakan di air) -> kalibrasi kasar dari WESAD
   (ACC, temp, HR real-world noise) dan datasheet sensor.
2. HR tidak lagi independen dari SpO2 -> korelasi fisiologis: makin rendah SpO2,
   makin tinggi HR (kompensasi takikardia), BARU ditambah noise. Ini meniru pola
   yang dilaporkan di studi desaturasi klinis (OpenOximetry) dan kasus submersion
   nyata (penurunan HR drastis pada fase akhir hipoksia berat/near-drowning).
3. Rentang antar kelas dibuat overlap (tidak lagi rentang terpisah bersih) supaya
   classifier tidak "curang" menghafal boundary buatan sendiri.
4. Fungsi generate_scenario() dipakai bareng oleh train_model.py DAN
   simulate_cli.py, supaya kedua model konsisten (v1 punya bug inkonsistensi ini).
5. InWater sekarang punya probabilitas salah baca (bukan biner sempurna tanpa
   noise) -> mencegah model "curang" memisahkan kelas AMAN hanya dari 1 fitur
   biner ini saja tanpa belajar pola sensor lain.

CATATAN JUJUR UNTUK LAPORAN:
Data tetap sintesis. Noise & korelasi di sini adalah upaya mendekatkan distribusi
ke pola fisiologis nyata (referensi: OpenOximetry Dataset untuk rentang SpO2
desaturasi, WESAD untuk noise sensor gerak/suhu), TAPI bukan pengganti data
subjek asli di air. Rekomendasikan uji lanjutan dengan data semi-real
(relawan di kolam renang, diawasi lifeguard) untuk validasi akhir sebelum
klaim akurasi dipakai sebagai hasil utama.

Fitur:
0. SpO2 (%)            : Saturasi oksigen darah (MAX30102)
1. Heart Rate (BPM)    : Denyut jantung (MAX30102)
2. Temperature (C)     : Suhu tubuh klinis (MAX30205)
3. In Water (0/1)      : Sensor pendeteksi air
4. Pitch (deg)         : Kemiringan sudut depan/belakang (MPU6050)
5. Roll (deg)          : Kemiringan sudut samping (MPU6050)
6. Is Face Down (0/1)  : Orientasi tubuh menghadap ke bawah di air

Output Kelas:
0 = AMAN (Normal / Safe)
1 = WASPADA (Warning / Immersion without hypoxia)
2 = KRITIS (Critical Drowning / Severe Hypoxia / Hypothermia / Unconscious)
"""

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
# m2cgen di-import di dalam __main__ saja (bukan di top-level) supaya file ini
# tetap bisa di-import ringan oleh simulate_cli.py tanpa perlu m2cgen terpasang.

np.random.seed(42)

# ---------------------------------------------------------------------------
# Noise level per sensor -- kalibrasi kasar dari datasheet + referensi WESAD
# (motion artifact bikin noise SpO2/HR lebih besar saat in_water/gerakan tinggi)
# ---------------------------------------------------------------------------
NOISE = {
    "spo2_still": 0.6,     # % , kondisi diam/darat
    "spo2_motion": 2.0,    # % , saat di air / gerakan (motion artifact PPG)
    "hr": 4.0,              # BPM
    "temp": 0.15,           # C
    "pitch": 6.0,           # deg
    "roll": 8.0,            # deg
}

# Probabilitas sensor water-detect salah baca (splash/kelembapan di darat,
# atau gap kontak sesaat saat benar-benar di air). Bikin InWater tidak lagi
# jadi shortcut sempurna untuk membedakan kelas.
IN_WATER_FLIP_PROB = 0.04


def noisy_in_water(true_value):
    if np.random.rand() < IN_WATER_FLIP_PROB:
        return 1 - true_value
    return true_value


def hr_from_spo2(spo2, base_hr, motion_boost=0.0):
    """
    Korelasi fisiologis kasar: HR naik saat SpO2 turun (kompensasi takikardia),
    lalu jenuh/menurun lagi pada hipoksia sangat berat (dekompensasi).
    Bukan model klinis presisi -- cuma supaya HR tidak independen dari SpO2.
    """
    deficit = max(0.0, 98.0 - spo2)
    compensation = deficit * 1.8 + motion_boost
    hr = base_hr + compensation
    # dekompensasi: pada hipoksia sangat berat, sebagian kasus malah bradikardia
    if spo2 < 80 and np.random.rand() < 0.35:
        hr = np.random.uniform(35, 60)
    return hr


def add_noise(value, std):
    return value + np.random.normal(0, std)


def generate_scenario(scenario):
    """Generate satu baris data (fitur) + label untuk sebuah skenario, dengan
    noise sensor dan korelasi fisiologis, plus rentang yang overlap antar kelas."""

    if scenario == "normal":
        spo2_clean = np.random.uniform(93.0, 100.0)          # was 95-100 (kini overlap ke bawah)
        temp = add_noise(np.random.uniform(36.0, 37.6), NOISE["temp"])
        in_water = noisy_in_water(0)
        pitch = add_noise(np.random.uniform(-20.0, 20.0), NOISE["pitch"])
        roll = add_noise(np.random.uniform(-30.0, 30.0), NOISE["roll"])
        face_down = 0
        base_hr = np.random.uniform(65.0, 90.0)
        hr = hr_from_spo2(spo2_clean, base_hr)
        spo2 = add_noise(spo2_clean, NOISE["spo2_still"])
        label = 0

    elif scenario == "water_safe":
        spo2_clean = np.random.uniform(93.0, 99.0)
        temp = add_noise(np.random.uniform(34.8, 36.8), NOISE["temp"])
        in_water = noisy_in_water(1)
        pitch = add_noise(np.random.uniform(-40.0, 40.0), NOISE["pitch"])
        roll = add_noise(np.random.uniform(-50.0, 50.0), NOISE["roll"])
        face_down = 0
        base_hr = np.random.uniform(80.0, 110.0)
        hr = hr_from_spo2(spo2_clean, base_hr, motion_boost=5)
        spo2 = add_noise(spo2_clean, NOISE["spo2_motion"])
        label = 1

    elif scenario == "hypothermia":
        temp = add_noise(np.random.uniform(28.0, 35.0), NOISE["temp"])   # overlap ke atas
        spo2_clean = np.random.uniform(88.0, 96.0)
        in_water = noisy_in_water(1)
        pitch = add_noise(np.random.uniform(-30.0, 30.0), NOISE["pitch"])
        roll = add_noise(np.random.uniform(-60.0, 60.0), NOISE["roll"])
        face_down = 0 if np.random.rand() > 0.3 else 1
        base_hr = np.random.uniform(45.0, 75.0)
        hr = hr_from_spo2(spo2_clean, base_hr)
        spo2 = add_noise(spo2_clean, NOISE["spo2_motion"])
        label = 2 if (temp < 32.5 or face_down == 1) else 1

    elif scenario == "mild_hypoxia":
        spo2_clean = np.random.uniform(87.0, 94.0)
        temp = add_noise(np.random.uniform(34.5, 36.5), NOISE["temp"])
        in_water = noisy_in_water(int(np.random.choice([0, 1], p=[0.3, 0.7])))
        pitch = add_noise(np.random.uniform(-35.0, 35.0), NOISE["pitch"])
        roll = add_noise(np.random.uniform(-60.0, 60.0), NOISE["roll"])
        face_down = 0
        base_hr = np.random.uniform(95.0, 125.0)
        hr = hr_from_spo2(spo2_clean, base_hr, motion_boost=8)
        spo2 = add_noise(spo2_clean, NOISE["spo2_motion"])
        label = 1

    elif scenario == "drowning_critical":
        spo2_clean = np.random.uniform(68.0, 90.0)             # overlap dgn mild_hypoxia
        temp = add_noise(np.random.uniform(31.0, 35.8), NOISE["temp"])
        in_water = noisy_in_water(1)
        pitch = add_noise(np.random.uniform(-60.0, 60.0), NOISE["pitch"])
        roll = add_noise(np.random.uniform(-180.0, 180.0), NOISE["roll"])
        face_down = 1 if np.random.rand() > 0.25 else 0
        base_hr = np.random.uniform(90.0, 130.0)
        hr = hr_from_spo2(spo2_clean, base_hr, motion_boost=10)
        spo2 = add_noise(spo2_clean, NOISE["spo2_motion"])
        label = 2

    elif scenario == "unconscious_facedown":
        spo2_clean = np.random.uniform(68.0, 87.0)
        temp = add_noise(np.random.uniform(29.5, 35.2), NOISE["temp"])
        in_water = noisy_in_water(1)
        pitch = add_noise(np.random.uniform(-80.0, -5.0), NOISE["pitch"])
        roll_base = np.random.choice([np.random.uniform(110.0, 180.0), np.random.uniform(-180.0, -110.0)])
        roll = add_noise(roll_base, NOISE["roll"])
        face_down = 1
        base_hr = np.random.uniform(40.0, 85.0)
        hr = hr_from_spo2(spo2_clean, base_hr)
        spo2 = add_noise(spo2_clean, NOISE["spo2_motion"])
        label = 2

    else:
        raise ValueError(scenario)

    # Clip ke rentang fisiologis wajar biar noise tidak bikin nilai absurd (SpO2 > 100 dst)
    spo2 = float(np.clip(spo2, 40.0, 100.0))
    hr = float(np.clip(hr, 20.0, 220.0))
    temp = float(np.clip(temp, 20.0, 42.0))
    pitch = float(np.clip(pitch, -180.0, 180.0))
    roll = float(np.clip(roll, -180.0, 180.0))

    return [spo2, hr, temp, in_water, pitch, roll, face_down], label


def build_dataset(n=6000, seed=42):
    rng = np.random.RandomState(seed)
    scenarios = ['normal', 'water_safe', 'hypothermia', 'mild_hypoxia',
                 'drowning_critical', 'unconscious_facedown']
    probs = [0.30, 0.20, 0.12, 0.13, 0.15, 0.10]

    records, labels = [], []
    for _ in range(n):
        scenario = rng.choice(scenarios, p=probs)
        feat, label = generate_scenario(scenario)
        records.append(feat)
        labels.append(label)
    return np.array(records), np.array(labels)


if __name__ == "__main__":
    import m2cgen as m2c

    feature_names = ['SpO2', 'HeartRate', 'Temperature', 'InWater', 'Pitch', 'Roll', 'IsFaceDown']

    X, y = build_dataset(n=6000, seed=42)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42, stratify=y
    )

    clf = RandomForestClassifier(n_estimators=15, max_depth=6, random_state=42)
    clf.fit(X_train, y_train)

    y_pred = clf.predict(X_test)
    print(f"Accuracy: {accuracy_score(y_test, y_pred) * 100:.2f}%\n")
    print("Classification Report:")
    print(classification_report(y_test, y_pred, target_names=['AMAN', 'WASPADA', 'KRITIS']))

    print("\nConfusion Matrix:")
    print(confusion_matrix(y_test, y_pred))

    print("\nFeature Importances:")
    for name, imp in zip(feature_names, clf.feature_importances_):
        print(f" - {name:12s}: {imp * 100:.2f}%")

    c_code = m2c.export_to_c(clf, function_name='predict_drownt_status')
    with open('drownt_model.h', 'w') as f:
        f.write('// Auto-generated TinyML Random Forest Model for ESP32 (v2 - noisy + correlated data)\n')
        f.write('// Features: [0]=SpO2, [1]=HeartRate, [2]=Temperature, [3]=InWater, [4]=Pitch, [5]=Roll, [6]=IsFaceDown\n')
        f.write('// Output: output[0]=P(AMAN), output[1]=P(WASPADA), output[2]=P(KRITIS)\n\n')
        f.write('#ifndef DROWNT_MODEL_H\n#define DROWNT_MODEL_H\n\n')
        f.write(c_code)
        f.write('\n\n#endif // DROWNT_MODEL_H\n')

    print("\nModel successfully transpiled to C header file: drownt_model.h")