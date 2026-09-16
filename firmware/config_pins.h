/**
 * @file config_pins.h
 * @brief Definisi Pinout ESP32-S3-MINI-1 sesuai Skematik PCB Smart Life Vest DROWNT
 * Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI)
 */

#ifndef CONFIG_PINS_H
#define CONFIG_PINS_H

// =============================================================================
// 1. BUS I2C (MAX30102, MAX30205, MPU6050)
// Di skematik: IO4 -> SCL, IO5 -> SDA, IO8 -> INT MAX30102
// Catatan: Bus I2C dapat dibagi bersama oleh MAX30102 (0x57), 
//          MPU6050 (0x68), dan MAX30205 (0x48).
// =============================================================================
#define PIN_I2C_SDA         5    // ESP32-S3 IO5 (Pull-up 4.7k R2 di skematik)
#define PIN_I2C_SCL         4    // ESP32-S3 IO4 (Pull-up 4.7k R1 di skematik)
#define PIN_MAX30102_INT    8    // ESP32-S3 IO8 (Interrupt MAX30102 pin 13)

// =============================================================================
// 2. GPS NEO-M8N (UART)
// Di skematik: 
//   IO17 terhubung ke pin 20 NEO-M8N (RXD) -> ESP32 bertindak sebagai TX
//   IO18 terhubung ke pin 21 NEO-M8N (TXD) -> ESP32 bertindak sebagai RX
// =============================================================================
#define PIN_GPS_RX          18   // ESP32-S3 IO18 (Menerima NMEA dari TX GPS)
#define PIN_GPS_TX          17   // ESP32-S3 IO17 (Mengirim konfigurasi ke RX GPS)
#define GPS_BAUDRATE        9600 // Default baudrate u-blox NEO-M8N

// =============================================================================
// 3. LoRa TRANSCEIVER SX1276 (SPI Bus & Control Pins)
// Di skematik:
//   Pin 16 (SCK)   -> IO14
//   Pin 17 (MISO)  -> IO15
//   Pin 18 (MOSI)  -> IO16
//   Pin 19 (NSS)   -> IO13 (Chip Select)
//   Pin 7  (RESET) -> IO12
//   Pin 8  (DIO0)  -> IO11 (Interrupt RX/TX Done)
// =============================================================================
#define PIN_LORA_SCK        14   // ESP32-S3 IO14
#define PIN_LORA_MISO       15   // ESP32-S3 IO15
#define PIN_LORA_MOSI       16   // ESP32-S3 IO16
#define PIN_LORA_NSS        13   // ESP32-S3 IO13 (CS / Slave Select)
#define PIN_LORA_RST        12   // ESP32-S3 IO12 (Reset)
#define PIN_LORA_DIO0       11   // ESP32-S3 IO11 (DIO0 Interrupt)

// Frekuensi LoRa Indonesia (AS923 / ISM 915-923 MHz)
#define LORA_FREQUENCY      915E6 // 915.0 MHz (atau 923E6 sesuai alokasi regulasi SDPPI)
#define LORA_SYNC_WORD      0xF3  // Private sync word DROWNT network

// =============================================================================
// 4. SENSOR & AKTUATOR TAMBAHAN (RESERVED / HEADER EKSTERNAL)
// Jika temanmu menambahkan pin header di PCB revisi:
// =============================================================================
#define PIN_WATER_SENSOR    1    // ESP32-S3 IO1 (Digital / ADC Water Detection probe)
#define PIN_BUZZER          2    // ESP32-S3 IO2 (Alarm piezo speaker)
#define PIN_INFLATION_TRIG  21   // ESP32-S3 IO21 (Pemicu solenoid inflasi pelampung otomatis)
#define PIN_LED_STATUS      38   // ESP32-S3 IO38 (RGB / Status LED)

#endif // CONFIG_PINS_H
