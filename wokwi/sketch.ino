/**
 * Proyek: DROWNT - Wearable Early Drowning Detection & Safety Monitoring
 * Tim: Kelompok 33 (Desain Proyek 2 - FTUI)
 * Platform: ESP32 / ESP32-S3 + FreeRTOS Multitasking + TinyML Edge AI
 * Model ML: Random Forest Classifier (Inference on-device via C++ transpiler)
 * Komponen: MPU6050 (IMU), OLED SSD1306, Simulated MAX30102 (SpO2/HR),
 *            Simulated MAX30205 (Temp), Water Sensor, Buzzer, LED Alert.
 */

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include "drownt_model.h"  // Model Machine Learning (TinyML)

// =================== PIN DEFINITIONS ===================
#define PIN_SDA         21
#define PIN_SCL         22
#define PIN_SPO2_ADC    34   // Potentiometer 1 (Simulasi SpO2: 70 - 100%)
#define PIN_TEMP_ADC    35   // Potentiometer 2 (Simulasi Suhu: 30 - 40 C)
#define PIN_WATER_BTN   14   // Pushbutton (Simulasi Sensor Air: LOW = Terendam)
#define PIN_BUZZER      25   // Buzzer Alarm
#define PIN_LED_CRIT    26   // LED Merah (Kritis)
#define PIN_LED_SAFE    27   // LED Hijau (Aman/Normal)

// =================== OLED DISPLAY SETUP ===================
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// =================== SENSOR MPU6050 ===================
Adafruit_MPU6050 mpu;

// =================== DATA STRUKTUR TELEMETRI ===================
struct TelemetryData {
  float spo2;
  int heartRate;
  float temperature;
  float pitch;
  float roll;
  bool isFaceDown;
  bool isInWater;
  float probAman;          // Probabilitas ML Kelas 0
  float probWaspada;       // Probabilitas ML Kelas 1
  float probKritis;        // Probabilitas ML Kelas 2
  int riskScore;           // 0 - 100
  char status[12];         // "AMAN", "WASPADA", "KRITIS"
};

TelemetryData sharedData;
SemaphoreHandle_t dataMutex;

// =================== TASK PROTOTYPES ===================
void TaskSensors(void *pvParameters);
void TaskMLDecision(void *pvParameters);
void TaskAlertUI(void *pvParameters);
void TaskTelemetry(void *pvParameters);

// =================== SETUP ===================
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n==========================================");
  Serial.println("  DROWNT: Smart Life Vest with TinyML AI  ");
  Serial.println("==========================================");

  // Inisialisasi Pin
  pinMode(PIN_WATER_BTN, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_CRIT, OUTPUT);
  pinMode(PIN_LED_SAFE, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED_CRIT, LOW);
  digitalWrite(PIN_LED_SAFE, HIGH);

  // Inisialisasi Bus I2C
  Wire.begin(PIN_SDA, PIN_SCL);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("[WARN] OLED SSD1306 tidak terdeteksi!");
  } else {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(10, 20);
    display.println("DROWNT TinyML v2");
    display.setCursor(5, 35);
    display.println("Edge AI Classifier...");
    display.display();
  }

  // Inisialisasi MPU6050
  if (!mpu.begin()) {
    Serial.println("[WARN] MPU6050 tidak terdeteksi, pastikan pin SDA/SCL benar.");
  } else {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.println("[OK] MPU6050 terdeteksi.");
  }

  // Inisialisasi Mutex
  dataMutex = xSemaphoreCreateMutex();

  // Buat Tasks FreeRTOS
  // Core 1: Sensing, DSP & Edge AI Inference
  xTaskCreatePinnedToCore(TaskSensors, "SensorsTask", 3072, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskMLDecision, "MLDecisionTask", 4096, NULL, 2, NULL, 1);

  // Core 0: Display/Buzzer & Transmisi Telemetri
  xTaskCreatePinnedToCore(TaskAlertUI, "AlertUITask", 3072, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskTelemetry, "TelemetryTask", 3072, NULL, 1, NULL, 0);

  Serial.println("[OK] FreeRTOS & TinyML Multitasking berjalan.");
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}

// =================== TASK 1: SENSOR ACQUISITION ===================
void TaskSensors(void *pvParameters) {
  (void) pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    // 1. Baca ADC Potentiometer untuk SpO2 & Heart Rate
    int rawSpo2 = analogRead(PIN_SPO2_ADC);
    float spo2Val = map(rawSpo2, 0, 4095, 70, 100);
    int hrVal = map(rawSpo2, 0, 4095, 120, 72);

    // 2. Baca ADC Potentiometer untuk Suhu Tubuh (MAX30205)
    int rawTemp = analogRead(PIN_TEMP_ADC);
    float tempVal = 30.0 + (rawTemp / 4095.0) * 10.0;

    // 3. Sensor Air (Pushbutton aktif LOW)
    bool inWater = (digitalRead(PIN_WATER_BTN) == LOW);

    // 4. Baca MPU6050 & Hitung Orientasi Tubuh
    sensors_event_t a, g, temp;
    float pitchVal = 0, rollVal = 0;
    bool faceDown = false;

    if (mpu.getEvent(&a, &g, &temp)) {
      pitchVal = atan2(a.acceleration.y, sqrt(a.acceleration.x * a.acceleration.x + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;
      rollVal  = atan2(-a.acceleration.x, a.acceleration.z) * 180.0 / PI;

      // Korban tengkurap/face-down jika akselerasi sumbu Z negatif atau roll terbalik
      if (a.acceleration.z < -2.0 || abs(rollVal) > 120.0) {
        faceDown = true;
      }
    }

    // Update shared struct dengan Mutex
    if (xSemaphoreTake(dataMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      sharedData.spo2 = spo2Val;
      sharedData.heartRate = hrVal;
      sharedData.temperature = tempVal;
      sharedData.pitch = pitchVal;
      sharedData.roll = rollVal;
      sharedData.isFaceDown = faceDown;
      sharedData.isInWater = inWater;
      xSemaphoreGive(dataMutex);
    }

    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100)); // 10 Hz
  }
}

// =================== TASK 2: MACHINE LEARNING INFERENCE ===================
void TaskMLDecision(void *pvParameters) {
  (void) pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    float curSpo2, curTemp, curPitch, curRoll;
    int curHr;
    bool curFaceDown, curInWater;

    if (xSemaphoreTake(dataMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      curSpo2     = sharedData.spo2;
      curHr       = sharedData.heartRate;
      curTemp     = sharedData.temperature;
      curPitch    = sharedData.pitch;
      curRoll     = sharedData.roll;
      curFaceDown = sharedData.isFaceDown;
      curInWater  = sharedData.isInWater;
      xSemaphoreGive(dataMutex);
    }

    // Siapkan vektor fitur untuk model TinyML:
    // [0]=SpO2, [1]=HeartRate, [2]=Temperature, [3]=InWater, [4]=Pitch, [5]=Roll, [6]=IsFaceDown
    double inputFeatures[7] = {
      (double)curSpo2,
      (double)curHr,
      (double)curTemp,
      curInWater ? 1.0 : 0.0,
      (double)curPitch,
      (double)curRoll,
      curFaceDown ? 1.0 : 0.0
    };

    double classProbabilities[3] = {0.0, 0.0, 0.0};
    
    // Jalankan inferensi Machine Learning langsung di chip ESP32 (< 1 ms latency)
    predict_drownt_status(inputFeatures, classProbabilities);

    // Hitung Skor Risiko Kontinu (0 - 100) berdasarkan ekspektasi probabilitas
    // Kelas 0: Aman (0 poin), Kelas 1: Waspada (50 poin), Kelas 2: Kritis (100 poin)
    float risk = (classProbabilities[1] * 50.0) + (classProbabilities[2] * 100.0);
    int finalScore = (int) constrain(risk, 0.0, 100.0);

    // Tentukan Klasifikasi Status
    const char *statusStr;
    if (classProbabilities[2] > 0.45 || finalScore >= 70) {
      statusStr = "KRITIS";
    } else if (classProbabilities[1] > 0.40 || finalScore >= 40) {
      statusStr = "WASPADA";
    } else {
      statusStr = "AMAN";
    }

    // Simpan hasil klasifikasi ML ke shared struct
    if (xSemaphoreTake(dataMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      sharedData.probAman    = classProbabilities[0];
      sharedData.probWaspada = classProbabilities[1];
      sharedData.probKritis  = classProbabilities[2];
      sharedData.riskScore   = finalScore;
      strncpy(sharedData.status, statusStr, sizeof(sharedData.status));
      xSemaphoreGive(dataMutex);
    }

    // Eksekusi inferensi setiap 200 ms (5 Hz)
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(200));
  }
}

// =================== TASK 3: OLED DISPLAY & LOCAL ALERTS ===================
void TaskAlertUI(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    TelemetryData d;
    if (xSemaphoreTake(dataMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      d = sharedData;
      xSemaphoreGive(dataMutex);
    }

    // --- Kontrol Aktuator (Buzzer & LED) ---
    if (strcmp(d.status, "KRITIS") == 0) {
      digitalWrite(PIN_LED_SAFE, LOW);
      digitalWrite(PIN_LED_CRIT, HIGH);
      tone(PIN_BUZZER, 2200);
      vTaskDelay(pdMS_TO_TICKS(150));
      digitalWrite(PIN_LED_CRIT, LOW);
      noTone(PIN_BUZZER);
      vTaskDelay(pdMS_TO_TICKS(150));
    } else if (strcmp(d.status, "WASPADA") == 0) {
      digitalWrite(PIN_LED_SAFE, HIGH);
      digitalWrite(PIN_LED_CRIT, HIGH);
      tone(PIN_BUZZER, 1000);
      vTaskDelay(pdMS_TO_TICKS(100));
      noTone(PIN_BUZZER);
      digitalWrite(PIN_LED_CRIT, LOW);
      vTaskDelay(pdMS_TO_TICKS(700));
    } else {
      digitalWrite(PIN_LED_SAFE, HIGH);
      digitalWrite(PIN_LED_CRIT, LOW);
      noTone(PIN_BUZZER);
      vTaskDelay(pdMS_TO_TICKS(500));
    }

    // --- Render Tampilan Layar OLED ---
    display.clearDisplay();

    // Bar Status Klasifikasi AI
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("AI: ");
    display.print(d.status);
    display.print(" (");
    display.print(d.riskScore);
    display.println("%)");

    display.drawLine(0, 10, 128, 10, WHITE);

    // Data Vital Tubuh
    display.setCursor(0, 14);
    display.print("SpO2: ");
    display.print((int)d.spo2);
    display.print("% | HR: ");
    display.print(d.heartRate);

    display.setCursor(0, 26);
    display.print("Temp: ");
    display.print(d.temperature, 1);
    display.println(" C");

    display.setCursor(0, 38);
    display.print("Env : ");
    display.print(d.isInWater ? "IN-WATER" : "DRY");
    display.print(" | ");
    display.print(d.isFaceDown ? "FACE-DN" : "OK");

    // Bar Probabilitas AI
    display.setCursor(0, 52);
    display.print("P(Crit): ");
    display.print((int)(d.probKritis * 100));
    display.println("%");

    display.display();
  }
}

// =================== TASK 4: TELEMETRY DISPATCH (JSON) ===================
void TaskTelemetry(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    TelemetryData d;
    if (xSemaphoreTake(dataMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      d = sharedData;
      xSemaphoreGive(dataMutex);
    }

    // JSON Payload untuk Dashboard SAR / LoRa
    StaticJsonDocument<300> doc;
    doc["device_id"]   = "VEST-33-01";
    doc["ml_model"]    = "RandomForest-TinyML";
    doc["status"]      = d.status;
    doc["risk_score"]  = d.riskScore;

    JsonObject probs   = doc.createNestedObject("ai_probabilities");
    probs["safe"]      = serialized(String(d.probAman, 2));
    probs["warning"]   = serialized(String(d.probWaspada, 2));
    probs["critical"]  = serialized(String(d.probKritis, 2));

    JsonObject vitals  = doc.createNestedObject("vitals");
    vitals["spo2"]     = (int)d.spo2;
    vitals["hr"]       = d.heartRate;
    vitals["temp"]     = serialized(String(d.temperature, 1));

    JsonObject env     = doc.createNestedObject("environment");
    env["in_water"]    = d.isInWater;
    env["face_down"]   = d.isFaceDown;

    JsonObject gps     = doc.createNestedObject("gps");
    gps["lat"]         = -6.2088;
    gps["lon"]         = 106.8456;

    serializeJson(doc, Serial);
    Serial.println();

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
