/* ============================================================================
   SMART LIFE VEST (DROWNT) — Standalone All-in-One Firmware (Cara 2)
   Kelompok 33 - Desain Proyek 2 (Teknik Komputer FTUI 2026)
   Board Target: ESP32 Dev Module (WROOM-32)
   
   Fitur Terintegrasi:
     1. TinyML Random Forest On-Device (4 Sensor: SpO2, HR, Air Pinggang, Air Leher)
     2. MAX30102 Pulse Oximeter (I2C: SDA=21, SCL=22)
     3. Dual Water Level Sensors (Pinggang=GPIO 26, Leher=GPIO 27)
     4. GPS NEO-6M (Serial2: RX=16, TX=17)
     5. BLE Wireless Telemetry (Service UUID: 4fafc201-1fb5-459e-8fcc-c5c9c331914b)
     6. USB Serial Telemetry JSON Stream (115200 baud)
   ============================================================================ */

#include <Wire.h>
#include <string.h>
#include "MAX30105.h"
#include <stdio.h>
#include <TinyGPSPlus.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

/* ============================================================================
   BAGIAN 1: TINYML RANDOM FOREST MODEL (C TRANSPILATION ON-DEVICE)
   ============================================================================ */
// Auto-generated TinyML Random Forest Model (n=10, depth=6)
// Input array: input[0]=SpO2, input[1]=HR, input[2]=WaterWaist, input[3]=WaterNeck
// Output: prob[0]=ProbAman, prob[1]=ProbWaspada, prob[2]=ProbKritis

#include <string.h>
static inline void set_vec3(double *arr, double a, double b, double c) {
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
}
void add_vectors(double *v1, double *v2, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] + v2[i];
}
void mul_vector_number(double *v1, double num, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] * num;
}
void predict_drownt(double * input, double * output) {
    double var0[3];
    double var1[3];
    double var2[3];
    double var3[3];
    double var4[3];
    double var5[3];
    double var6[3];
    double var7[3];
    double var8[3];
    double var9[3];
    double var10[3];
    if (input[3] <= 16.912599563598633) {
        if (input[0] <= 96.21861267089844) {
            if (input[0] <= 87.0) {
                set_vec3(var10, 0.0, 0.0, 1.0);
            } else {
                if (input[0] <= 95.11266326904297) {
                    if (input[2] <= 19.601022243499756) {
                        set_vec3(var10, 1.0, 0.0, 0.0);
                    } else {
                        set_vec3(var10, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[2] <= 24.879436492919922) {
                        set_vec3(var10, 1.0, 0.0, 0.0);
                    } else {
                        set_vec3(var10, 0.0, 1.0, 0.0);
                    }
                }
            }
        } else {
            if (input[0] <= 98.00188827514648) {
                if (input[2] <= 27.502238750457764) {
                    set_vec3(var10, 1.0, 0.0, 0.0);
                } else {
                    set_vec3(var10, 0.0, 1.0, 0.0);
                }
            } else {
                set_vec3(var10, 1.0, 0.0, 0.0);
            }
        }
    } else {
        if (input[0] <= 93.27442932128906) {
            if (input[3] <= 22.580631256103516) {
                if (input[3] <= 22.473576545715332) {
                    if (input[3] <= 18.08793830871582) {
                        if (input[2] <= 72.53097534179688) {
                            set_vec3(var10, 0.0, 0.6666666666666666, 0.3333333333333333);
                        } else {
                            set_vec3(var10, 0.0, 0.0, 1.0);
                        }
                    } else {
                        set_vec3(var10, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var10, 0.0, 1.0, 0.0);
                }
            } else {
                set_vec3(var10, 0.0, 0.0, 1.0);
            }
        } else {
            set_vec3(var10, 0.0, 1.0, 0.0);
        }
    }
    double var11[3];
    if (input[2] <= 22.15372085571289) {
        if (input[3] <= 32.90376853942871) {
            set_vec3(var11, 1.0, 0.0, 0.0);
        } else {
            set_vec3(var11, 0.0, 0.0, 1.0);
        }
    } else {
        if (input[0] <= 88.97673416137695) {
            set_vec3(var11, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 30.841583251953125) {
                set_vec3(var11, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var11, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var10, var11, 3, var9);
    double var12[3];
    if (input[2] <= 17.524185180664062) {
        if (input[3] <= 34.53039360046387) {
            set_vec3(var12, 1.0, 0.0, 0.0);
        } else {
            set_vec3(var12, 0.0, 0.0, 1.0);
        }
    } else {
        if (input[3] <= 16.03221607208252) {
            if (input[3] <= 6.479576349258423) {
                if (input[0] <= 85.88521194458008) {
                    set_vec3(var12, 0.0, 0.0, 1.0);
                } else {
                    set_vec3(var12, 0.0, 1.0, 0.0);
                }
            } else {
                if (input[1] <= 130.46627807617188) {
                    if (input[0] <= 87.0) {
                        set_vec3(var12, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var12, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[0] <= 87.07321166992188) {
                        set_vec3(var12, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var12, 0.0, 1.0, 0.0);
                    }
                }
            }
        } else {
            if (input[3] <= 17.98166847229004) {
                if (input[2] <= 70.91705703735352) {
                    set_vec3(var12, 0.0, 1.0, 0.0);
                } else {
                    if (input[1] <= 151.16582489013672) {
                        if (input[0] <= 88.50648880004883) {
                            set_vec3(var12, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var12, 0.0, 1.0, 0.0);
                        }
                    } else {
                        set_vec3(var12, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[0] <= 93.39421844482422) {
                    if (input[3] <= 22.580631256103516) {
                        if (input[1] <= 100.38983154296875) {
                            set_vec3(var12, 0.0, 1.0, 0.0);
                        } else {
                            set_vec3(var12, 0.0, 0.019230769230769232, 0.9807692307692307);
                        }
                    } else {
                        set_vec3(var12, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var12, 0.0, 1.0, 0.0);
                }
            }
        }
    }
    add_vectors(var9, var12, 3, var8);
    double var13[3];
    if (input[2] <= 22.15372085571289) {
        if (input[0] <= 93.68829345703125) {
            set_vec3(var13, 0.0, 0.0, 1.0);
        } else {
            set_vec3(var13, 1.0, 0.0, 0.0);
        }
    } else {
        if (input[1] <= 82.42146301269531) {
            set_vec3(var13, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 16.034945487976074) {
                if (input[0] <= 87.0) {
                    set_vec3(var13, 0.0, 0.0, 1.0);
                } else {
                    set_vec3(var13, 0.0, 1.0, 0.0);
                }
            } else {
                if (input[0] <= 93.39421844482422) {
                    if (input[3] <= 18.041781425476074) {
                        if (input[0] <= 87.14458465576172) {
                            set_vec3(var13, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var13, 0.0, 1.0, 0.0);
                        }
                    } else {
                        if (input[1] <= 96.99796295166016) {
                            set_vec3(var13, 0.0, 0.2, 0.8);
                        } else {
                            set_vec3(var13, 0.0, 0.0, 1.0);
                        }
                    }
                } else {
                    set_vec3(var13, 0.0, 1.0, 0.0);
                }
            }
        }
    }
    add_vectors(var8, var13, 3, var7);
    double var14[3];
    if (input[3] <= 15.099550247192383) {
        if (input[2] <= 22.157761573791504) {
            set_vec3(var14, 1.0, 0.0, 0.0);
        } else {
            if (input[1] <= 135.52609252929688) {
                if (input[2] <= 81.87349700927734) {
                    if (input[0] <= 86.6869125366211) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[0] <= 87.0) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[3] <= 6.361717700958252) {
                    if (input[0] <= 84.9917106628418) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[1] <= 155.33686065673828) {
                        if (input[3] <= 7.322883367538452) {
                            set_vec3(var14, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var14, 0.0, 0.5189873417721519, 0.4810126582278481);
                        }
                    } else {
                        if (input[1] <= 158.06736755371094) {
                            set_vec3(var14, 0.0, 0.2, 0.8);
                        } else {
                            set_vec3(var14, 0.0, 0.0, 1.0);
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] <= 93.27442932128906) {
            if (input[3] <= 18.93958568572998) {
                if (input[2] <= 62.07185745239258) {
                    set_vec3(var14, 0.0, 1.0, 0.0);
                } else {
                    if (input[0] <= 87.51628112792969) {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[3] <= 22.70266056060791) {
                    if (input[2] <= 65.60127639770508) {
                        set_vec3(var14, 0.0, 1.0, 0.0);
                    } else {
                        set_vec3(var14, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var14, 0.0, 0.0, 1.0);
                }
            }
        } else {
            set_vec3(var14, 0.0, 1.0, 0.0);
        }
    }
    add_vectors(var7, var14, 3, var6);
    double var15[3];
    if (input[2] <= 17.524185180664062) {
        if (input[0] <= 93.68829345703125) {
            set_vec3(var15, 0.0, 0.0, 1.0);
        } else {
            set_vec3(var15, 1.0, 0.0, 0.0);
        }
    } else {
        if (input[0] <= 88.99232864379883) {
            set_vec3(var15, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 31.574199676513672) {
                set_vec3(var15, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var15, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var6, var15, 3, var5);
    double var16[3];
    if (input[0] <= 90.29013442993164) {
        if (input[0] <= 88.99232864379883) {
            set_vec3(var16, 0.0, 0.0, 1.0);
        } else {
            if (input[3] <= 30.2672700881958) {
                set_vec3(var16, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var16, 0.0, 0.0, 1.0);
            }
        }
    } else {
        if (input[2] <= 22.15372085571289) {
            if (input[3] <= 40.43387031555176) {
                set_vec3(var16, 1.0, 0.0, 0.0);
            } else {
                set_vec3(var16, 0.0, 0.0, 1.0);
            }
        } else {
            if (input[3] <= 31.789849281311035) {
                set_vec3(var16, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var16, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var5, var16, 3, var4);
    double var17[3];
    if (input[0] <= 90.6403923034668) {
        if (input[3] <= 9.415399551391602) {
            if (input[0] <= 87.0) {
                set_vec3(var17, 0.0, 0.0, 1.0);
            } else {
                set_vec3(var17, 0.0, 1.0, 0.0);
            }
        } else {
            if (input[2] <= 61.623783111572266) {
                if (input[2] <= 60.9774112701416) {
                    if (input[3] <= 31.647231101989746) {
                        if (input[1] <= 111.3760986328125) {
                            set_vec3(var17, 0.0, 1.0, 0.0);
                        } else {
                            set_vec3(var17, 0.0, 0.0, 1.0);
                        }
                    } else {
                        set_vec3(var17, 0.0, 0.0, 1.0);
                    }
                } else {
                    set_vec3(var17, 0.0, 1.0, 0.0);
                }
            } else {
                if (input[0] <= 89.41382217407227) {
                    set_vec3(var17, 0.0, 0.0, 1.0);
                } else {
                    if (input[3] <= 40.624691009521484) {
                        set_vec3(var17, 0.0, 1.0, 0.0);
                    } else {
                        set_vec3(var17, 0.0, 0.0, 1.0);
                    }
                }
            }
        }
    } else {
        if (input[0] <= 96.17595672607422) {
            if (input[3] <= 37.8552885055542) {
                if (input[2] <= 20.047212600708008) {
                    set_vec3(var17, 1.0, 0.0, 0.0);
                } else {
                    set_vec3(var17, 0.0, 1.0, 0.0);
                }
            } else {
                set_vec3(var17, 0.0, 0.0, 1.0);
            }
        } else {
            if (input[2] <= 26.221489906311035) {
                set_vec3(var17, 1.0, 0.0, 0.0);
            } else {
                set_vec3(var17, 0.0, 1.0, 0.0);
            }
        }
    }
    add_vectors(var4, var17, 3, var3);
    double var18[3];
    if (input[0] <= 89.91395950317383) {
        if (input[2] <= 71.30355834960938) {
            if (input[3] <= 14.253886699676514) {
                if (input[1] <= 119.79433822631836) {
                    if (input[3] <= 5.939317464828491) {
                        if (input[2] <= 68.88050079345703) {
                            set_vec3(var18, 0.0, 1.0, 0.0);
                        } else {
                            set_vec3(var18, 0.0, 0.0, 1.0);
                        }
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[0] <= 85.92390823364258) {
                        set_vec3(var18, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                }
            } else {
                if (input[3] <= 23.4641752243042) {
                    if (input[3] <= 20.97260284423828) {
                        set_vec3(var18, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                } else {
                    set_vec3(var18, 0.0, 0.0, 1.0);
                }
            }
        } else {
            if (input[3] <= 11.520169734954834) {
                if (input[1] <= 130.6210479736328) {
                    if (input[3] <= 10.588211059570312) {
                        if (input[0] <= 87.0) {
                            set_vec3(var18, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var18, 0.0, 1.0, 0.0);
                        }
                    } else {
                        set_vec3(var18, 0.0, 1.0, 0.0);
                    }
                } else {
                    if (input[2] <= 83.05875396728516) {
                        if (input[0] <= 86.66640853881836) {
                            set_vec3(var18, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var18, 0.0, 1.0, 0.0);
                        }
                    } else {
                        set_vec3(var18, 0.0, 0.0, 1.0);
                    }
                }
            } else {
                set_vec3(var18, 0.0, 0.0, 1.0);
            }
        }
    } else {
        if (input[2] <= 22.15372085571289) {
            if (input[3] <= 38.55550956726074) {
                set_vec3(var18, 1.0, 0.0, 0.0);
            } else {
                set_vec3(var18, 0.0, 0.0, 1.0);
            }
        } else {
            if (input[3] <= 32.269317626953125) {
                set_vec3(var18, 0.0, 1.0, 0.0);
            } else {
                set_vec3(var18, 0.0, 0.0, 1.0);
            }
        }
    }
    add_vectors(var3, var18, 3, var2);
    double var19[3];
    if (input[3] <= 15.375060081481934) {
        if (input[1] <= 93.85237503051758) {
            if (input[2] <= 26.769408226013184) {
                set_vec3(var19, 1.0, 0.0, 0.0);
            } else {
                if (input[0] <= 86.98477554321289) {
                    set_vec3(var19, 0.0, 0.0, 1.0);
                } else {
                    set_vec3(var19, 0.0, 1.0, 0.0);
                }
            }
        } else {
            if (input[2] <= 18.768545627593994) {
                set_vec3(var19, 1.0, 0.0, 0.0);
            } else {
                if (input[1] <= 135.444091796875) {
                    if (input[3] <= 8.787459373474121) {
                        if (input[0] <= 87.0) {
                            set_vec3(var19, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var19, 0.0, 1.0, 0.0);
                        }
                    } else {
                        if (input[3] <= 8.873868942260742) {
                            set_vec3(var19, 0.0, 0.0, 1.0);
                        } else {
                            set_vec3(var19, 0.0, 0.8643410852713178, 0.13565891472868216);
                        }
                    }
                } else {
                    if (input[0] <= 87.0) {
                        set_vec3(var19, 0.0, 0.0, 1.0);
                    } else {
                        set_vec3(var19, 0.0, 1.0, 0.0);
                    }
                }
            }
        }
    } else {
        if (input[3] <= 18.939433097839355) {
            if (input[0] <= 87.14458465576172) {
                set_vec3(var19, 0.0, 0.0, 1.0);
            } else {
                set_vec3(var19, 0.0, 1.0, 0.0);
            }
        } else {
            if (input[0] <= 93.46842193603516) {
                if (input[0] <= 88.99232864379883) {
                    set_vec3(var19, 0.0, 0.0, 1.0);
                } else {
                    if (input[0] <= 89.01523971557617) {
                        set_vec3(var19, 0.0, 1.0, 0.0);
                    } else {
                        set_vec3(var19, 0.0, 0.0, 1.0);
                    }
                }
            } else {
                set_vec3(var19, 0.0, 1.0, 0.0);
            }
        }
    }
    add_vectors(var2, var19, 3, var1);
    mul_vector_number(var1, 0.1, 3, var0);
    output[0] = var0[0]; output[1] = var0[1]; output[2] = var0[2];
}
/* ============================================================================
   BAGIAN 2: KONFIGURASI PIN & PERIFERAL HARDWARE
   ============================================================================ */
#define DEVICE_NAME         "LifeVest-01"
#define BLE_SERVICE_UUID    "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define BLE_CHAR_UUID       "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// I2C Pin (MAX30102)
#define I2C_SDA_PIN         21
#define I2C_SCL_PIN         22

// Water Level Sensors (ADC)
#define PIN_WATER_WAIST     26
#define PIN_WATER_NECK      27

// GPS NEO-6M (Hardware Serial2 ESP32)
#define GPS_RX_PIN          16   // Ke TX Modul GPS
#define GPS_TX_PIN          17   // Ke RX Modul GPS
#define GPS_BAUD            9600

// Parameter Sensor MAX30102
#define LED_POWER           0x3F // Arus LED (0x1F - 0x7F)
#define FINGER_MIN_IR       8000 // Ambang IR deteksi jari menempel
#define FINGER_RELEASE_IR   3500 // Ambang lepas jari

/* ============================================================================
   BAGIAN 3: OBJEK & VARIABEL GLOBAL
   ============================================================================ */
MAX30105 particleSensor;
TinyGPSPlus gps;
HardwareSerial SerialGPS(2);

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

// Callbacks BLE Server
class LifeVestServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.println("[BLE] Client Web Dashboard Terhubung!");
    }
    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("[BLE] Client Terputus, Memulai Advertising Ulang...");
    }
};

// Variabel Pengukuran Vital
long lastBeatTime = 0;
float currentBPM = 0.0;
float currentSpO2 = 0.0;
float pctWaterWaist = 0.0;
float pctWaterNeck = 0.0;

// Anti-Floor Hysteresis
bool fingerDetected = false;
uint32_t beatCount = 0;

// Variabel Output Inferensi ML
double mlInput[4];  // [SpO2, HR, WaterWaist, WaterNeck]
double mlProb[3];   // [ProbAman, ProbWaspada, ProbKritis]
int predictedClass = 0; // 0=AMAN, 1=WASPADA, 2=KRITIS
int riskScore = 0;      // 0-100
const char* statusStr = "AMAN";

uint32_t packetSeq = 0;
unsigned long lastTelemetryTime = 0;


/* ============================================================================
   DETEKTOR DENYUT NADI 32-BIT ADAPTIF (ANTI-OVERFLOW ESP32 & MAX30102)
   ============================================================================ */
float irDC = 0.0;
float irAC = 0.0;
float irAC_prev = 0.0;
bool isRising = false;
unsigned long lastBeatMs = 0;
float bpmHistory[4] = {0, 0, 0, 0};
int bpmHistIdx = 0;

bool detectHeartBeat(long sample) {
  if (sample < FINGER_MIN_IR) {
    irDC = 0.0;
    irAC = 0.0;
    return false;
  }

  if (irDC == 0.0) {
    irDC = (float)sample;
    return false;
  }

  // 1. IIR DC Tracking (Baseline Follower)
  irDC = (irDC * 0.95f) + ((float)sample * 0.05f);

  // 2. Ekstrak sinyal AC
  float rawAC = (float)sample - irDC;

  // 3. IIR Low-pass filter (~4 Hz) untuk meredam jitter/noise
  irAC_prev = irAC;
  irAC = (irAC * 0.70f) + (rawAC * 0.30f);

  bool beatDetected = false;

  // 4. Deteksi Puncak Gelombang Sistolik (Peak Detection):
  float minPeak = max(20.0f, irDC * 0.0008f);
  if (irAC > minPeak && irAC < irAC_prev && isRising) {
    unsigned long now = millis();
    unsigned long delta = now - lastBeatMs;

    // Rentang fisiologis denyut nadi: 40 s/d 200 BPM (300ms s/d 1500ms)
    if (delta >= 300 && delta <= 1500) {
      float instantBPM = 60000.0f / (float)delta;

      bpmHistory[bpmHistIdx] = instantBPM;
      bpmHistIdx = (bpmHistIdx + 1) % 4;

      float sum = 0;
      int count = 0;
      for (int i = 0; i < 4; i++) {
        if (bpmHistory[i] > 30.0f) {
          sum += bpmHistory[i];
          count++;
        }
      }
      if (count > 0) {
        currentBPM = sum / count;
      }
      beatCount++;
      lastBeatMs = now;
      beatDetected = true;
    } else if (delta > 1500) {
      lastBeatMs = now;
    }
    isRising = false;
  } else if (irAC > irAC_prev) {
    isRising = true;
  }

  return beatDetected;
}

/* ============================================================================
   BAGIAN 4: SETUP
   ============================================================================ */
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("");
  Serial.println("========================================================");
  Serial.println("   SMART LIFE VEST (DROWNT) - EDGE AI REVOLUTION        ");
  Serial.println("   Departemen Teknik Komputer FTUI - Kelompok 33        ");
  Serial.println("========================================================");

  // Inisialisasi Pin Sensor Air
  pinMode(PIN_WATER_WAIST, INPUT);
  pinMode(PIN_WATER_NECK, INPUT);

  // Inisialisasi I2C & MAX30102
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(100000); // 100 kHz standard speed

  Serial.print("[INIT] Menghubungkan ke MAX30102...");
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println(" GAGAL! Periksa kabel SDA=21, SCL=22 dan power 3V3.");
  } else {
    Serial.println(" BERHASIL!");
    // Konfigurasi MAX30102: power, sampleAverage=1 (100Hz real-time), mode=2(Red+IR), sampleRate=100, pulseWidth=411, adcRange=4096
    particleSensor.setup(LED_POWER, 1, 2, 100, 411, 4096);
    particleSensor.setPulseAmplitudeRed(LED_POWER);
    particleSensor.setPulseAmplitudeIR(LED_POWER);
    particleSensor.setPulseAmplitudeGreen(0);
  }

  // Inisialisasi GPS NEO-6M
  Serial.printf("[INIT] GPS NEO-6M pada Serial2 RX=%d, TX=%d @%d bps...\n", GPS_RX_PIN, GPS_TX_PIN, GPS_BAUD);
  SerialGPS.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  // Inisialisasi BLE
  Serial.printf("[INIT] Memulai BLE Server '%s'...\n", DEVICE_NAME);
  BLEDevice::init(DEVICE_NAME);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new LifeVestServerCallbacks());

  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      BLE_CHAR_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("[OK] BLE Advertising aktif. Siap dikoneksikan ke Dashboard!");
}

/* ============================================================================
   BAGIAN 5: LOOP UTAMA
   ============================================================================ */
void loop() {
  // 1. Baca aliran data GPS secara kontinu
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  // 2. Baca Sensor MAX30102
  long irValue = particleSensor.getIR();
  long redValue = particleSensor.getRed();

  if (irValue > FINGER_MIN_IR) {
    fingerDetected = true;

    // Deteksi Denyut Jantung dengan 32-bit Adaptive Peak Detector
    detectHeartBeat(irValue);

    // Estimasi SpO2 Sederhana dari Rasio AC/DC Red & IR
    if (irValue > 1000 && redValue > 1000) {
      double ratio = (double)redValue / (double)irValue;
      // Formula kalibrasi empiris standar oximeter
      double spo2Est = 104.0 - (17.0 * ratio);
      spo2Est = constrain(spo2Est, 70.0, 100.0);

      if (currentSpO2 == 0.0) {
        currentSpO2 = spo2Est;
      } else {
        currentSpO2 = (currentSpO2 * 0.85) + (spo2Est * 0.15);
      }
    }
  } else if (irValue < FINGER_RELEASE_IR) {
    // Jari benar-benar dilepas
    fingerDetected = false;
    currentBPM = 0.0;
    currentSpO2 = 0.0;
    beatCount = 0;
    irDC = 0.0;
    irAC = 0.0;
  }

  // 3. Baca Sensor Air (ADC 12-bit: 0 - 4095)
  // Normalisasi ke persentase 0 - 100%
  int rawWaist = analogRead(PIN_WATER_WAIST);
  int rawNeck  = analogRead(PIN_WATER_NECK);

  pctWaterWaist = constrain((rawWaist / 4095.0f) * 100.0f, 0.0f, 100.0f);
  pctWaterNeck  = constrain((rawNeck / 4095.0f) * 100.0f, 0.0f, 100.0f);

  // 4. Eksekusi Edge AI Inferensi & Telemetri Setiap 500 ms
  if (millis() - lastTelemetryTime >= 500) {
    lastTelemetryTime = millis();
    packetSeq++;

    // Nilai Default jika jari belum terpasang (diasumsikan fisiologis netral agar tidak false-alarm)
    double effectiveSpO2 = (currentSpO2 > 50.0) ? currentSpO2 : 98.0;
    double effectiveHR   = (currentBPM > 30.0)  ? currentBPM  : 75.0;

    // Siapkan Input Fitur untuk Model TinyML:
    // [0]=SpO2, [1]=HeartRate, [2]=WaterWaist, [3]=WaterNeck
    mlInput[0] = effectiveSpO2;
    mlInput[1] = effectiveHR;
    mlInput[2] = (double)pctWaterWaist;
    mlInput[3] = (double)pctWaterNeck;

    // Eksekusi On-Device Random Forest!
    predict_drownt(mlInput, mlProb);

    // Tentukan Kelas Prediksi (Argmax dari probabilitas)
    if (mlProb[2] >= mlProb[1] && mlProb[2] >= mlProb[0]) {
      predictedClass = 2; // KRITIS
    } else if (mlProb[1] >= mlProb[0]) {
      predictedClass = 1; // WASPADA
    } else {
      predictedClass = 0; // AMAN
    }

    // =========================================================================
    // ATURAN FAIL-SAFE MEDIS KESELAMATAN TENGGELAM
    // =========================================================================
    // Jika leher terendam air (pctWaterNeck >= 30%), ini darurat hidup & mati!
    // Walaupun sensor pinggang putus/rusak (0%) atau SpO2 belum sempat drop,
    // sistem WAJIB memaksa status KRITIS secara instan.
    if (pctWaterNeck >= 30.0f) {
      predictedClass = 2;
      mlProb[0] = 0.01;
      mlProb[1] = 0.01;
      mlProb[2] = 0.98;
    }

    // Hitung Risk Score (0 - 100)
    riskScore = (int)((mlProb[1] * 40.0) + (mlProb[2] * 100.0));
    riskScore = constrain(riskScore, 0, 100);

    // Label String
    if (predictedClass == 2) {
      statusStr = "KRITIS";
    } else if (predictedClass == 1) {
      statusStr = "WASPADA";
    } else {
      statusStr = "AMAN";
    }

    // Koordinat GPS
    double lat = gps.location.isValid() ? gps.location.lat() : -6.3627;
    double lng = gps.location.isValid() ? gps.location.lng() : 106.8272;
    int sat    = gps.satellites.isValid() ? gps.satellites.value() : 0;

    // Format Telemetri JSON
    char jsonBuffer[256];
    snprintf(jsonBuffer, sizeof(jsonBuffer),
      "{\"id\":\"VEST-01\",\"seq\":%lu,\"status\":\"%s\",\"risk\":%d,"
      "\"spo2\":%.1f,\"hr\":%.1f,\"waistWater\":%.1f,\"neckWater\":%.1f,"
      "\"lat\":%.6f,\"lng\":%.6f,\"sat\":%d,"
      "\"probAman\":%.2f,\"probWaspada\":%.2f,\"probKritis\":%.2f}",
      packetSeq, statusStr, riskScore,
      currentSpO2, currentBPM, pctWaterWaist, pctWaterNeck,
      lat, lng, sat,
      mlProb[0], mlProb[1], mlProb[2]
    );

    // Kirim via USB Serial ke Laptop / Dashboard
    Serial.println(jsonBuffer);

    // Kirim via BLE jika terhubung
    if (deviceConnected) {
      pCharacteristic->setValue(jsonBuffer);
      pCharacteristic->notify();
    }
  }

  // Handle reconnecting BLE
  if (!deviceConnected && oldDeviceConnected) {
    delay(200);
    pServer->startAdvertising();
    oldDeviceConnected = deviceConnected;
  }
  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
}
