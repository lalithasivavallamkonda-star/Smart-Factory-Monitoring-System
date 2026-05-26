#include "telemetry.h"
#include "network.h"
#include <stdlib.h>

static char*buffer = NULL;
static uint8_t len=0;

// to convert float value to string
static char* f1( float v,char*dst)
{
    return dtostrf(v,1,1,dst);
}

void telemetry_init(char* buf, uint8_t bufLen)
{
   buffer = buf;
   len = bufLen;
}
void telemetry_publishTelemetry(const SensorData* data, uint8_t relayState)
{
  char t[8], h[8];
    
   f1(data->temperature, t);
   f1(data->humidity, h);
   

   /*put data into json format*/
   
   snprintf_P(buffer, len, PSTR(
  "{\"temperature\":%s,\"humidity\":%s,\"ldrValue\":%u,"
  "\"isDark\":%u,\"motionDetected\":%u,\"relaystate\":%u,"
  "\"doorOpen\":%u,\"sensorError\":%u}"
),t, h,
                                (unsigned)data->ldrValue,
                                (unsigned)data->isDark,
                                (unsigned)data->motionDetected,
                                (unsigned)relayState,
                                (unsigned)data->doorOpen,
                                (unsigned)data->sensorError
                                );
 
    network_publish(TOPIC_TELEMETRY, buffer,0);

}