#ifndef TELEMETRY_H
#define TELEMETRY_H

/*
 * telemetry.h — builds and publishes JSON payloads to ThingsBoard.
 *
 * Call telemetry_init() once in setup() with the shared JSON buffer.
 * Uses network_publish() internally — no extra dependencies needed.
 */

#include <Arduino.h>
#include "config.h"
#include "sensor.h"

void telemetry_init(char* buf, uint8_t bufLen);
void telemetry_publishTelemetry(const SensorData* data, uint8_t relayState);
void telemetry_publishAttributes(void);

#endif /* TELEMETRY_H */