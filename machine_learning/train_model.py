"""
Pelatihan Model Machine Learning (TinyML) untuk Smart Life Vest DROWNT
Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI)

Fitur Fisiologis & Lingkungan:
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
import m2cgen as m2c

# 1. Synthesize Clinical & Disaster Ground Truth Data
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
        spo2 = np.random.uniform(95.0, 100.0)
        hr = np.random.uniform(65.0, 95.0)
        temp = np.random.uniform(36.2, 37.5)
        in_water = 0
        pitch = np.random.uniform(-20.0, 20.0)
        roll = np.random.uniform(-30.0, 30.0)
        face_down = 0
        label = 0 # AMAN
        
    elif scenario == 'water_safe':
        spo2 = np.random.uniform(94.0, 99.0)
        hr = np.random.uniform(80.0, 115.0)
        temp = np.random.uniform(35.0, 36.8)
        in_water = 1
        pitch = np.random.uniform(-40.0, 40.0)
        roll = np.random.uniform(-50.0, 50.0)
        face_down = 0
        label = 1 # WASPADA
        
    elif scenario == 'hypothermia':
        spo2 = np.random.uniform(90.0, 96.0)
        hr = np.random.uniform(45.0, 75.0)
        temp = np.random.uniform(28.0, 34.5)
        in_water = 1
        pitch = np.random.uniform(-30.0, 30.0)
        roll = np.random.uniform(-60.0, 60.0)
        face_down = 0 if np.random.rand() > 0.3 else 1
        label = 2 if temp < 32.0 or face_down == 1 else 1
        
    elif scenario == 'mild_hypoxia':
        spo2 = np.random.uniform(89.0, 93.0)
        hr = np.random.uniform(100.0, 135.0)
        temp = np.random.uniform(34.8, 36.5)
        in_water = np.random.choice([0, 1], p=[0.3, 0.7])
        pitch = np.random.uniform(-35.0, 35.0)
        roll = np.random.uniform(-60.0, 60.0)
        face_down = 0
        label = 1 # WASPADA
        
    elif scenario == 'drowning_critical':
        spo2 = np.random.uniform(70.0, 88.0)
        hr = np.random.choice([np.random.uniform(130.0, 165.0), np.random.uniform(35.0, 55.0)])
        temp = np.random.uniform(31.0, 35.5)
        in_water = 1
        pitch = np.random.uniform(-60.0, 60.0)
        roll = np.random.uniform(-180.0, 180.0)
        face_down = 1 if np.random.rand() > 0.25 else 0
        label = 2 # KRITIS
        
    elif scenario == 'unconscious_facedown':
        spo2 = np.random.uniform(70.0, 85.0)
        hr = np.random.uniform(40.0, 80.0)
        temp = np.random.uniform(30.0, 35.0)
        in_water = 1
        pitch = np.random.uniform(-80.0, -10.0)
        roll = np.random.choice([np.random.uniform(120.0, 180.0), np.random.uniform(-180.0, -120.0)])
        face_down = 1
        label = 2 # KRITIS
        
    records.append([spo2, hr, temp, in_water, pitch, roll, face_down])
    labels.append(label)

feature_names = ['SpO2', 'HeartRate', 'Temperature', 'InWater', 'Pitch', 'Roll', 'IsFaceDown']
X = np.array(records)
y = np.array(labels)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

# 2. Train Random Forest (15 trees, depth 6 -> highly efficient for ESP32)
clf = RandomForestClassifier(n_estimators=15, max_depth=6, random_state=42)
clf.fit(X_train, y_train)

# 3. Evaluation
y_pred = clf.predict(X_test)
print(f"Accuracy: {accuracy_score(y_test, y_pred) * 100:.2f}%\n")
print("Classification Report:")
print(classification_report(y_test, y_pred, target_names=['AMAN', 'WASPADA', 'KRITIS']))

print("\nFeature Importances:")
for name, imp in zip(feature_names, clf.feature_importances_):
    print(f" - {name:12s}: {imp * 100:.2f}%")

# 4. Transpile to C Code for TinyML on ESP32
c_code = m2c.export_to_c(clf, function_name='predict_drownt_status')
with open('drownt_model.h', 'w') as f:
    f.write('// Auto-generated TinyML Random Forest Model for ESP32\n')
    f.write('// Features: [0]=SpO2, [1]=HeartRate, [2]=Temperature, [3]=InWater, [4]=Pitch, [5]=Roll, [6]=IsFaceDown\n')
    f.write('// Output: output[0]=P(AMAN), output[1]=P(WASPADA), output[2]=P(KRITIS)\n\n')
    f.write('#ifndef DROWNT_MODEL_H\n#define DROWNT_MODEL_H\n\n')
    f.write(c_code)
    f.write('\n\n#endif // DROWNT_MODEL_H\n')

print("\nModel successfully transpiled to C header file: drownt_model.h")
