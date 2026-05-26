#ifndef RPC_H
#define RPC_H

/*
 * rpc.h — handles incoming ThingsBoard RPC commands over MQTT.
 *
 * Supported commands:
 *   setRelay  {"method":"setRelay","params":true}
 *   setLED    {"method":"setLED","params":{"pin":5,"state":true}}
 *   getStatus {"method":"getStatus","params":null}
 *   reboot    {"method":"reboot","params":null}
 *
 * Call rpc_init() once in setup().
 * Pass rpc_mqttCallback to mqttClient.setCallback().
 */

#include <Arduino.h>
#include <PubSubClient.h>
#include "config.h"

void rpc_init(PubSubClient* mqtt, char* buf, uint8_t bufLen);

/* This is the function to pass to mqttClient.setCallback() */
void rpc_mqttCallback(char* topic, byte* payload, unsigned int length);

#endif /* RPC_H */
