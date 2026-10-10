"""
Pelatihan Model TinyML Random Forest untuk Smart Life Vest DROWNT (4 Sensor)
Departemen Teknik Komputer FTUI - Kelompok 33

Fitur Input:
0. SpO2 (%)            : 70 - 100
1. Heart Rate (BPM)    : 35 - 190
2. Water Waist (%)     : 0 - 100
3. Water Neck (%)      : 0 - 100

Output:
Kelas 0 = AMAN
Kelas 1 = WASPADA
Kelas 2 = KRITIS
"""

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, accuracy_score
import m2cgen as m2c

np.random.seed(42)
N_SAMPLES_PER_CLASS = 1500

# ---------------------------------------------------------------------------
# SINTESIS DATASET BERDASARKAN POLA FISIOLOGIS & MULTI-WATER LEVEL
# ---------------------------------------------------------------------------

def generate_dataset():
    records = []

    # 1. KELAS 0: AMAN (Darat / Di Atas Kapal)
    for _ in range(N_SAMPLES_PER_CLASS):
        spo2 = np.clip(np.random.normal(98.0, 1.2), 94.0, 100.0)
        hr = np.clip(np.random.normal(78.0, 9.0), 55.0, 105.0)
        water_waist = np.clip(np.random.normal(2.0, 4.0), 0.0, 20.0)
        water_neck = np.clip(np.random.normal(1.0, 3.0), 0.0, 15.0)
        records.append([spo2, hr, water_waist, water_neck, 0])

    # 2. KELAS 1: WASPADA (Badan di Air / Mengapung Normal / Panik Awal)
    for _ in range(N_SAMPLES_PER_CLASS):
        # Pinggang basah, leher masih di atas air
        water_waist = np.clip(np.random.normal(75.0, 15.0), 30.0, 100.0)
        water_neck = np.clip(np.random.normal(5.0, 6.0), 0.0, 24.0)
        # HR cenderung naik karena berenang/panik, SpO2 masih relatif aman
        hr = np.clip(np.random.normal(118.0, 16.0), 85.0, 165.0)
        spo2 = np.clip(np.random.normal(94.5, 2.5), 89.0, 98.0)
        records.append([spo2, hr, water_waist, water_neck, 1])

    # 3. KELAS 2: KRITIS (Tenggelam / Air di Leher / Hipoksia Berat)
    for _ in range(N_SAMPLES_PER_CLASS):
        # Skenario A: Leher terendam air (entah pinggang basah atau rusak)
        # Skenario B: Hipoksia berat di air
        is_neck_submerged = np.random.rand() > 0.25
        if is_neck_submerged:
            water_neck = np.clip(np.random.normal(80.0, 15.0), 30.0, 100.0)
            # Pinggang bisa basah normal atau rusak (0%)
            water_waist = np.clip(np.random.normal(85.0, 20.0), 0.0, 100.0) if np.random.rand() > 0.1 else 0.0
            spo2 = np.clip(np.random.normal(84.0, 6.0), 70.0, 93.0)
            # HR bisa takikardia berat atau anjlok bradikardia near-drowning
            hr = np.random.choice([np.random.normal(145, 15), np.random.normal(44, 6)])
        else:
            # Di air dengan hipoksia berat
            water_waist = np.clip(np.random.normal(85.0, 12.0), 35.0, 100.0)
            water_neck = np.clip(np.random.normal(15.0, 8.0), 0.0, 28.0)
            spo2 = np.clip(np.random.normal(78.0, 4.0), 70.0, 85.0)
            hr = np.clip(np.random.normal(135.0, 20.0), 40.0, 175.0)

        hr = np.clip(hr, 35.0, 190.0)
        records.append([spo2, hr, water_waist, water_neck, 2])

    df = pd.DataFrame(records, columns=['spo2', 'hr', 'water_waist', 'water_neck', 'target'])
    return df

if __name__ == '__main__':
    print("Mempersiapkan dataset...")
    df = generate_dataset()

    X = df[['spo2', 'hr', 'water_waist', 'water_neck']].values
    y = df['target'].values

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

    print("Melatih Random Forest Classifier (n_estimators=10, max_depth=6)...")
    clf = RandomForestClassifier(n_estimators=10, max_depth=6, random_state=42)
    clf.fit(X_train, y_train)

    y_pred = clf.predict(X_test)
    acc = accuracy_score(y_test, y_pred)
    print(f"Akurasi Model: {acc * 100:.2f}%")
    print(classification_report(y_test, y_pred, target_names=['AMAN', 'WASPADA', 'KRITIS']))

    # Transpile ke C code untuk ESP32
    print("Mentranspile model ke C Code via m2cgen...")
    c_code = m2c.export_to_c(clf, function_name='predict_drownt')

    # Buat header C
    header_content = f"""#ifndef DROWNT_MODEL_4F_H
#define DROWNT_MODEL_4F_H

// Auto-generated TinyML Random Forest Model (n=10, depth=6)
// Input array: input[0]=SpO2, input[1]=HR, input[2]=WaterWaist, input[3]=WaterNeck
// Output: prob[0]=ProbAman, prob[1]=ProbWaspada, prob[2]=ProbKritis

{c_code}

#endif // DROWNT_MODEL_4F_H
"""

    with open('c:/Users/esun/College/Semester 7/Despro 2/Proyek Lifevest/firmware/drownt_model_4f.h', 'w') as f:
        f.write(header_content)

    print("Header drownt_model_4f.h berhasil dibuat di folder firmware!")
