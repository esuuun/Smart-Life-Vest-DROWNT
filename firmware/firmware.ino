/**
 * @file firmware.ino
 * @brief Firmware Utama Smart Life Vest "DROWNT" berbasis ESP32-S3 & TinyML
 * @author Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI)
 * 
 * Target Hardware: ESP32-S3-MINI-1
 * Sensor & Modul:
 *  - I2C (SDA: IO5, SCL: IO4): MAX30102 (SpO2 & HR), MPU6050 (IMU)
 *  - UART (RX: IO18, TX: IO17): u-blox NEO-M8N GPS
 *  - SPI (SCK: IO14, MISO: IO15, MOSI: IO16, NSS: IO13, RST: IO12, DIO0: IO11): SX1276 LoRa
 * 
 * Arsitektur: FreeRTOS Preemptive Multitasking + Mutex Protected Shared Telemetry
 */

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPSPlus.h>
#include <LoRa.h>
#include <ArduinoJson.h>

#include "config_pins.h"
#include "drownt_model.h"

// =============================================================================
// STRUKTUR DATA TELEMETRI KORBAN & PELAMPUNG
// =============================================================================
struct TelemetryPayload {
  // Sensor Fisiologis
  float spo2;              // % (70 - 100)
  float heartRate;         // BPM (40 - 180)
  float temperature;       // Celcius (30 - 40)
  
  // Sensor Lingkungan & Orientasi Fisik
  bool inWater;            // 0 = Kering/Darat, 1 = Di Air
  float pitch;             // Sudut depan-belakang (-90 s/d +90 deg)
  float roll;              // Sudut miring kiri-kanan (-180 s/d +180 deg)
  bool isFaceDown;         // 1 = Wajah korban tenggelam/menghadap air
  
  // Lokasi GPS
  double latitude;
  double longitude;
  float speedKmH;
  uint8_t satellites;
  bool gpsValid;
  
  // Hasil Inferensi TinyML
  float probAman;          // Probabilitas Kelas 0
  float probWaspada;       // Probabilitas Kelas 1
  float probKritis;        // Probabilitas Kelas 2
  uint8_t predictedClass;  // 0 = AMAN, 1 = WASPADA, 2 = KRITIS
  uint8_t riskScore;       // 0 - 100 Skala Bahaya
  
  // Metadata Perangkat
  uint32_t packetCounter;
  uint32_t uptimeSec;
};

// Global Instance & Mutex
TelemetryPayload systemData;
SemaphoreHandle_t telemetryMutex;

// Objek Sensor & Periferal
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1); // Hardware UART1 ESP32-S3
SPIClass SPI_LoRa(FSPI);     // Hardware SPI untuk SX1276

// Flags Status Sensor
bool mpuAvailable = false;
bool loraAvailable = false;
bool max30102Available = false;

// Task Handles FreeRTOS
TaskHandle_t TaskSensorsHandle = NULL;
TaskHandle_t TaskGPSHandle = NULL;
TaskHandle_t TaskMLHandle = NULL;
TaskHandle_t TaskCommsHandle = NULL;

// Forward Declarations
void TaskSensors(void *pvParameters);
void TaskGPS(void *pvParameters);
void TaskMLInference(void *pvParameters);
void TaskLoRaTelemetry(void *pvParameters);

// =============================================================================
// SETUP HARDWARE & PERIFERAL
// =============================================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=======================================================");
  Serial.println("  DROWNT: Smart Life Vest Edge AI & LoRa System        ");
  Serial.println("  Departemen Teknik Elektro & Komputer FTUI - 2026     ");
  Serial.println("=======================================================");

  // Inisialisasi Pin Tambahan
  pinMode(PIN_WATER_SENSOR, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_INFLATION_TRIG, OUTPUT);
  pinMode(PIN_LED_STATUS, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_INFLATION_TRIG, LOW);
  digitalWrite(PIN_LED_STATUS, LOW);

  // Buat Mutex untuk akses data aman antar-task
  telemetryMutex = xSemaphoreCreateMutex();

  // Inisialisasi Nilai Awal Telemetri
  systemData.spo2 = 98.0f;
  systemData.heartRate = 75.0f;
  systemData.temperature = 36.5f;
  systemData.inWater = false;
  systemData.pitch = 0.0f;
  systemData.roll = 0.0f;
  systemData.isFaceDown = false;
  systemData.latitude = -6.3627; // Default UI Depok jika GPS belum lock
  systemData.longitude = 106.8272;
  systemData.speedKmH = 0.0f;
  systemData.satellites = 0;
  systemData.gpsValid = false;
  systemData.predictedClass = 0;
  systemData.riskScore = 0;
  systemData.packetCounter = 0;

  // 1. Inisialisasi Bus I2C (SDA = IO5, SCL = IO4)
  Serial.printf("[INIT] Inisialisasi I2C SDA=GPIO%d, SCL=GPIO%d...\n", PIN_I2C_SDA, PIN_I2C_SCL);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000); // Fast mode 400kHz

  // 2. Inisialisasi MPU6050
  if (!mpu.begin(0x68, &Wire)) {
    Serial.println("[WARN] MPU6050 tidak terdeteksi pada 0x68! Cek jalur I2C.");
    mpuAvailable = false;
  } else {
    Serial.println("[OK] MPU6050 berhasil diinisialisasi.");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    mpuAvailable = true;
  }

  // 3. Inisialisasi GPS UART (RX = IO18, TX = IO17)
  Serial.printf("[INIT] Inisialisasi GPS UART1 RX=GPIO%d, TX=GPIO%d baud=%d...\n", 
                PIN_GPS_RX, PIN_GPS_TX, GPS_BAUDRATE);
  SerialGPS.begin(GPS_BAUDRATE, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);

  // 4. Inisialisasi SPI & LoRa SX1276
  Serial.printf("[INIT] Inisialisasi LoRa SX1276 SPI (SCK:%d, MISO:%d, MOSI:%d, NSS:%d)...\n",
                PIN_LORA_SCK, PIN_LORA_MISO, PIN_LORA_MOSI, PIN_LORA_NSS);
  SPI_LoRa.begin(PIN_LORA_SCK, PIN_LORA_MISO, PIN_LORA_MOSI, PIN_LORA_NSS);
  LoRa.setSPI(SPI_LoRa);
  LoRa.setPins(PIN_LORA_NSS, PIN_LORA_RST, PIN_LORA_DIO0);

  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("[WARN] LoRa SX1276 gagal start! Pastikan kabel/jalur SPI benar.");
    loraAvailable = false;
  } else {
    Serial.printf("[OK] LoRa SX1276 Berhasil di frekuensi %.1f MHz.\n", LORA_FREQUENCY / 1E6);
    LoRa.setSyncWord(LORA_SYNC_WORD);
    LoRa.setTxPower(20); // Daya pancar maksimal 20 dBm untuk transmisi laut/danau
    LoRa.setSpreadingFactor(10); // SF10: Jangkauan jauh & andal menembus gelombang
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(5);
    LoRa.enableCrc();
    loraAvailable = true;
  }

  // ===========================================================================
  // BUAT TASK-TASK FREERTOS PADA ESP32-S3 DUAL-CORE
  // Core 0: Komunikasi & GPS (Protokol I/O berat)
  // Core 1: Sensor Sampling & TinyML Inference (Komputasi Matematika Real-Time)
  // ===========================================================================
  Serial.println("[INIT] Meluncurkan FreeRTOS Tasks...");

  xTaskCreatePinnedToCore(
    TaskSensors, "TaskSensors", 4096, NULL, 2, &TaskSensorsHandle, 1
  );

  xTaskCreatePinnedToCore(
    TaskGPS, "TaskGPS", 3072, NULL, 1, &TaskGPSHandle, 0
  );

  xTaskCreatePinnedToCore(
    TaskMLInference, "TaskML", 4096, NULL, 3, &TaskMLHandle, 1
  );

  xTaskCreatePinnedToCore(
    TaskLoRaTelemetry, "TaskLoRa", 4096, NULL, 2, &TaskCommsHandle, 0
  );

  Serial.println("[OK] Seluruh Task berhasil dijalankan. Sistem DROWNT Aktif!\n");
}

void loop() {
  // Semua proses dijalankan di dalam Task FreeRTOS, loop utama dibiarkan idle.
  vTaskDelay(pdMS_TO_TICKS(1000));
}

// =============================================================================
// TASK 1: AKUISISI SENSOR I2C & WATER DETECTOR (Core 1, Interval: 100ms)
// =============================================================================
void TaskSensors(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(100);

  for (;;) {
    // 1. Baca Kemiringan IMU MPU6050
    float rawPitch = 0.0f;
    float rawRoll = 0.0f;
    bool faceDownCondition = false;

    if (mpuAvailable) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      float ax = a.acceleration.x;
      float ay = a.acceleration.y;
      float az = a.acceleration.z;

      // Kalkulasi sudut kemiringan pitch dan roll
      rawPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / PI;
      rawRoll  = atan2(ay, az) * 180.0f / PI;

      // Deteksi posisi tengkurap (Face-Down): 
      // Vektor gravitasi z mengarah negatif (punggung menghadap ke atas langit)
      if (az < -2.0f || (fabs(rawPitch) > 45.0f && az < 0.0f)) {
        faceDownCondition = true;
      }
    }

    // 2. Baca Sensor Air (Water Detector)
    // Sensor aktif LOW (terhubung ke GND ketika elektroda terendam air konduktif)
    bool currentInWater = (digitalRead(PIN_WATER_SENSOR) == LOW);

    // 3. Simpan ke Global Telemetry Payload dengan aman (Mutex)
    if (xSemaphoreTake(telemetryMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
      systemData.pitch = rawPitch;
      systemData.roll = rawRoll;
      systemData.isFaceDown = faceDownCondition;
      systemData.inWater = currentInWater;
      xSemaphoreGive(telemetryMutex);
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

// =============================================================================
// TASK 2: PARSING NMEA GPS NEO-M8N (Core 0, Non-Blocking Streaming)
// =============================================================================
void TaskGPS(void *pvParameters) {
  for (;;) {
    while (SerialGPS.available() > 0) {
      char c = SerialGPS.read();
      gps.encode(c);
    }

    if (gps.location.isUpdated()) {
      if (xSemaphoreTake(telemetryMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        systemData.latitude = gps.location.lat();
        systemData.longitude = gps.location.lng();
        systemData.speedKmH = gps.speed.kmph();
        systemData.satellites = gps.satellites.value();
        systemData.gpsValid = gps.location.isValid();
        xSemaphoreGive(telemetryMutex);
      }
    }

    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// =============================================================================
// TASK 3: PRE-PROCESSING & TINYML INFERENCE (Core 1, Interval: 500ms)
// =============================================================================
void TaskMLInference(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(500);

  // Buffer input model: 7 Fitur
  // [0]=SpO2, [1]=HeartRate, [2]=Temperature, [3]=InWater, [4]=Pitch, [5]=Roll, [6]=IsFaceDown
  double mlInput[7];
  double mlOutput[3]; // [0]=AMAN, [1]=WASPADA, [2]=KRITIS

  for (;;) {
    // Ambil data sensor terkini
    if (xSemaphoreTake(telemetryMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
      mlInput[0] = (double)systemData.spo2;
      mlInput[1] = (double)systemData.heartRate;
      mlInput[2] = (double)systemData.temperature;
      mlInput[3] = systemData.inWater ? 1.0 : 0.0;
      mlInput[4] = (double)systemData.pitch;
      mlInput[5] = (double)systemData.roll;
      mlInput[6] = systemData.isFaceDown ? 1.0 : 0.0;
      xSemaphoreGive(telemetryMutex);
    }

    // Eksekusi Model TinyML Random Forest On-Device
    predict_drownt_status(mlInput, mlOutput);

    // Tentukan kelas prediksi (Argmax)
    uint8_t bestClass = 0;
    double maxProb = mlOutput[0];
    for (int i = 1; i < 3; i++) {
      if (mlOutput[i] > maxProb) {
        maxProb = mlOutput[i];
        bestClass = i;
      }
    }

    // Hitung Risk Score (0 - 100)
    int calculatedRisk = (int)((mlOutput[1] * 40.0) + (mlOutput[2] * 100.0));
    if (calculatedRisk > 100) calculatedRisk = 100;
    if (calculatedRisk < 0) calculatedRisk = 0;

    // Update Telemetri & Kontrol Aktuator Tanggap Darurat
    if (xSemaphoreTake(telemetryMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
      systemData.probAman = (float)mlOutput[0];
      systemData.probWaspada = (float)mlOutput[1];
      systemData.probKritis = (float)mlOutput[2];
      systemData.predictedClass = bestClass;
      systemData.riskScore = calculatedRisk;
      systemData.uptimeSec = millis() / 1000;
      xSemaphoreGive(telemetryMutex);
    }

    // Kontrol Aktuator Darurat
    if (bestClass == 2) {
      // KONDISI KRITIS: Sirine Aktif, Picu Inflasi Otomatis
      digitalWrite(PIN_BUZZER, HIGH);
      digitalWrite(PIN_INFLATION_TRIG, HIGH);
      digitalWrite(PIN_LED_STATUS, HIGH);
    } else if (bestClass == 1) {
      // KONDISI WASPADA: Beep Berkedip
      digitalWrite(PIN_INFLATION_TRIG, LOW);
      digitalWrite(PIN_BUZZER, (millis() % 400 < 200) ? HIGH : LOW);
      digitalWrite(PIN_LED_STATUS, (millis() % 400 < 200) ? HIGH : LOW);
    } else {
      // KONDISI AMAN
      digitalWrite(PIN_BUZZER, LOW);
      digitalWrite(PIN_INFLATION_TRIG, LOW);
      digitalWrite(PIN_LED_STATUS, LOW);
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

// =============================================================================
// TASK 4: TRANSMISI TELEMETRI LoRa & LOGGING SERIAL (Core 0)
// Adaptive Interval: KRITIS = 1s, WASPADA = 3s, AMAN = 10s
// =============================================================================
void TaskLoRaTelemetry(void *pvParameters) {
  for (;;) {
    TelemetryPayload localData;
    if (xSemaphoreTake(telemetryMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
      localData = systemData;
      systemData.packetCounter++;
      xSemaphoreGive(telemetryMutex);
    }

    // Format Pesan JSON Ringkas untuk transmisi LoRa & Serial Base Station
    StaticJsonDocument<320> doc;
    doc["id"] = "VEST-01";
    doc["seq"] = localData.packetCounter;
    
    // Status
    const char* statusStr = (localData.predictedClass == 2) ? "KRITIS" : 
                            (localData.predictedClass == 1) ? "WASPADA" : "AMAN";
    doc["status"] = statusStr;
    doc["risk"] = localData.riskScore;

    // Vital Signs & Posisi
    JsonObject vitals = doc.createNestedObject("vit");
    vitals["spo2"] = (int)localData.spo2;
    vitals["hr"] = (int)localData.heartRate;
    vitals["temp"] = serialized(String(localData.temperature, 1));
    vitals["fdown"] = localData.isFaceDown ? 1 : 0;
    vitals["water"] = localData.inWater ? 1 : 0;

    // Koordinat GPS untuk Tim Penyelamat (SAR)
    JsonObject pos = doc.createNestedObject("gps");
    pos["lat"] = serialized(String(localData.latitude, 6));
    pos["lng"] = serialized(String(localData.longitude, 6));
    pos["sat"] = localData.satellites;

    String jsonString;
    serializeJson(doc, jsonString);

    // 1. Output ke Serial Monitor (Debug USB)
    Serial.printf("[TELEMETRY] [%s | Risk:%d%%] SpO2:%d%% HR:%d Temp:%.1fC Water:%d FaceDown:%d | Lat:%.6f Lon:%.6f\n",
                  statusStr, localData.riskScore, (int)localData.spo2, (int)localData.heartRate,
                  localData.temperature, localData.inWater, localData.isFaceDown,
                  localData.latitude, localData.longitude);

    // 2. Transmisi Radio LoRa SX1276
    if (loraAvailable) {
      LoRa.beginPacket();
      LoRa.print(jsonString);
      LoRa.endPacket();
    }

    // Adaptive Delay berdasarkan status bahaya
    uint32_t delayMs = 10000; // Normal/Aman kirim tiap 10 detik
    if (localData.predictedClass == 2) {
      delayMs = 1000;         // Kritis kirim tiap 1 detik (Real-time SAR beacon)
    } else if (localData.predictedClass == 1) {
      delayMs = 3000;         // Waspada kirim tiap 3 detik
    }

    vTaskDelay(pdMS_TO_TICKS(delayMs));
  }
}
