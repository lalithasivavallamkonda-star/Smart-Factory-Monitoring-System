#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "config.h"
#include "network.h"
#include "SensorManager.h"
#include "telemetry.h"
#include "actuator.h"
#include "rpc.h"

/* MQTT + Ethernet */
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

/* Buffer */
#define BUF_SIZE 128
char buffer[BUF_SIZE];

/* Sensor data */
SensorData data;

/* Timing */
unsigned long lastTelemetryTime = 0;

/*  Manual control variables */
uint8_t manualMode = 0;   // 0 = AUTO, 1 = MANUAL
uint8_t manualRelay = 0;  // value from ThingsBoard

void setup()
{
    Serial.begin(9600);

    sensor_begin();
    actuators_begin();

    network_begin(&mqttClient);

    telemetry_init(buffer, BUF_SIZE);
    rpc_init(&mqttClient, buffer, BUF_SIZE);

    mqttClient.setCallback(rpc_mqttCallback);

    Serial.println("System Started...");
}

void loop()
{
    network_maintain();

    actuators_updateStatusLEDs(
        network_isConnected(),
        data.sensorError
    );

    unsigned long now = millis();

    if (now - lastTelemetryTime >= TELEMETRY_INTERVAL)
    {
        lastTelemetryTime = now;

        if (sensors_read(&data))
        {
            /*  AUTO mode (humidity based) */
            static uint8_t autoRelay = 0;

            if (data.humidity > 70)
            {
              autoRelay = 1;
            }
            else if (data.humidity < 65)
            {
              autoRelay = 0;
            }
            /*  FINAL relay control */
            if (manualMode)
            {
                actuators_setRelay(manualRelay);   // switch control
            }
            else
            {
                actuators_setRelay(autoRelay);     // humidity control
            }

            /* Debug */
            Serial.print("Humidity: ");
            Serial.println(data.humidity);

            Serial.print("Relay State: ");
            Serial.println(actuators_getRelayState());

            /* Send telemetry */
            telemetry_publishTelemetry(&data, actuators_getRelayState());
        }
        else
        {
            Serial.println("Sensor Error!");
            actuators_setRelay(0);
        }
    }
}