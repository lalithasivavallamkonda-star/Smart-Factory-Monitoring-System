#ifndef NETWORK_H
#define NETWORK_H

/*
 * network.h — Ethernet + MQTT connection management.
 *
 * Call network_begin() once in setup() with the PubSubClient pointer
 * and a callback to run each time MQTT connects.
 * Call network_maintain() every loop iteration.
 */

#include <Arduino.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "config.h"

/* Pass the PubSubClient created in the main sketch */
void    network_begin(PubSubClient* mqtt);
void    network_maintain(void);
uint8_t network_isConnected(void);
uint8_t network_publish(const char* topic, const char* payload, uint8_t retain);
uint8_t network_subscribe(const char* topic);

#endif /* NETWORK_H */