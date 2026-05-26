#include"network.h"
#include "config.h"

static PubSubClient* mqtt             =NULL;
static byte          mac[6]           =NODE_MAC;
static unsigned long lastReconnectTime    =0;

static void doConnect(void)
{
  //connect to thingsboard
  if(mqtt->connect( CLIENT_ID ,ACCESS_TOKEN, NULL))
  {
     Serial.println("connected");
  }
   else
   {
     Serial.println("mqtt failed");
   
   }
}

void    network_begin(PubSubClient* mqttClient)
{
  mqtt    =  mqttClient;

  // connect board to the internet
  Ethernet.begin(mac);
  delay(2000);

  //connect to things board
  mqtt->setServer(TB_SERVER,TB_PORT);
  doConnect();

}

void    network_maintain(void)
{
  Ethernet.maintain();

   //if board connected to things board try to reconnect every 5 secs
   if(mqtt->connected())
   {
     mqtt->loop();
   }
   else
   {
      unsigned long now =millis();
      if (now - lastReconnectTime >= RECONNECT_INTERVAL )
      {
        lastReconnectTime=now;
        doConnect();
      }
   }
}
//return the status of mqtt connection
uint8_t network_isConnected(void)
{
   return (uint8_t) mqtt->connected();
}



uint8_t network_publish(const char* topic, const char* payload, uint8_t retain)
{
     return(uint8_t)mqtt->publish(topic,payload, (bool)retain);

}