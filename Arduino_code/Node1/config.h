//Network
#define NODE_MAC    { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }


//thingsboard
#define TB_SERVER      "mqtt.thingsboard.cloud"
#define TB_PORT        1883
#define ACCESS_TOKEN   "V2HCQe3AVs1gMRVzPogj"
#define CLIENT_ID      "Production007"

//MQTT topic
#define TOPIC_TELEMETRY   "v1/devices/me/telemetry"
#define TOPIC_RPC_REQUEST "v1/devices/me/rpc/request/+"
#define TOPIC_RPC_RESPONSE "v1/devices/me/rpc/response/"

//time delay
#define TELEMETRY_INTERVAL  5000UL
#define RECONNECT_INTERVAL  5000UL


//pins used
#define DHT_TYPE            DHT22

#define PIN_DHT             2
#define PIN_BUTTON          3
#define PIN_LED_GREEN       5
#define PIN_LED_YELLOW      6
#define PIN_LED_RED         7

#define PIN_RELAY           4

#define PIN_VIBRATION   A0
#define PIN_LM35        A1

#define RPC_ID_SIZE     12