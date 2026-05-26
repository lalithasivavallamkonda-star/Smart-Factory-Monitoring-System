#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "config.h"

// ─────────────────────────────────────────────────────────────
//  SensorData — all readings for one sample cycle
// ─────────────────────────────────────────────────────────────
typedef struct {
    float    temperature;      // DHT22 °C
    float    humidity;         // DHT22 %RH
    uint16_t ldrValue;         // Raw ADC (0–1023); lower = darker
    bool     motionDetected;   // PIR: true = motion present
    bool     doorOpen;         // Door sensor: true = door open
    bool     isDark;           // Derived: ldrValue < LDR_DARK_THRESH
    bool     sensorError;      // DHT22 read failure
} SensorData;

// ─────────────────────────────────────────────────────────────
//  SensorManager — POD context struct
//  DHT object is kept as a file-scope static in SensorManager.cpp
// ─────────────────────────────────────────────────────────────
typedef struct {
    float         lastTemp;
    float         lastHumidity;
    bool          motionActive;       // Latched PIR state
    unsigned long motionClearTime;    // When to clear after PIR goes LOW
} sensor;

// ── Module functions ──────────────────────────────────────────
void sensor_init  (sensor* sm);
void sensor_begin ();
bool sensor_read  (SensorData* out,sensor* sm);


#endif // SENSOR_MANAGER_H