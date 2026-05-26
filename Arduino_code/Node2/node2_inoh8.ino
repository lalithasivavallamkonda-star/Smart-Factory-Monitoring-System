//include required libraries
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "config.h"
#include "sensor.h"
#include "actuator.h"
#include "network.h"
#include "telemetry.h"
#include "rpc.h"


static char sharedBuf[200];

//create object of type ethernet pubsubclient
static EthernetClient ethClient;
static PubSubClient  mqttClient(ethClient);

unsigned long lastTelemetry =0;

static sensor   sensors;

void setup() 
{
  Serial.begin(9600);
  Serial.print("Node2 is booting...");

  // put your setup code here, to run once:
   // initilase sensor 
   sensor_begin();
   sensor_init(&sensors);
   //initialise actutors
   actuators_begin();

   telemetry_init(sharedBuf,sizeof(sharedBuf));
   //rpc_init(&mqttClient,sharedBuf,sizeof(sharedBuf));  
   // coonect board to internet and mqtt
   network_begin( &mqttClient);

   
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //keep checking if board is connected to things board
  network_maintain();

  //read data from the sensors
  SensorData data; 
  sensor_read( &data,&sensors); // humidty,tem,ldr,door status,motion status 
  
  //if humidity is more than 85 turn on the relay is off
  if(data.humidity >= HUMIDITY_CRIT && !actuators_getRelayState())
  {
      actuators_setRelay(1);
  }

  //publish to the cloud 
  //check if network availble then push data to TB
  if(network_isConnected())
  {   unsigned long now = millis();
     //publish data to things  every 5 secs
     if(now-lastTelemetry >=TELEMETRY_INTERVAL) //if 5sec is over
       
      {
          lastTelemetry = now;
          telemetry_publishTelemetry(&data,actuators_getRelayState); // converting sensor into json and publish
      } 
  }
  
  actuators_updateStatusLEDs(network_isConnected(),data.sensorError);
}