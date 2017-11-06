// Simple wrapper for Azure IoT-Hub SDK to use MQTT

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ESP8266WiFi.h>

#include <AzureIoTHub.h>
#include <AzureIoTUtility.h>
#include <AzureIoTProtocol_MQTT.h>

#include "myMqtt.h"

const char* ssid = "digitalisierung";
const char* pass = "cloudification";

const char* connectionString = "HostName=i3cmhub.azure-devices.net;DeviceId=gate1;SharedAccessKey=P8hSkpx2U2onChJfdMTaRee7ODyQENW1JTRAHC8W4p4=";

void setup() {
  
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.printf("Try to connect to network %s ",ssid);
  Serial.println();
    
  WiFi.begin(ssid, pass);
  Serial.print(".");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("OK");
  Serial.print("IP address .: ");
  Serial.println(WiFi.localIP());

  Serial.print("Strength ...: ");
  Serial.println(WiFi.RSSI());
  Serial.println(); 

  Serial.println("Try to get time by NTP");
  time_t currentTime = 0;
  configTime(0, 0, "ptbtime1.ptb.de", "ptbtime2.ptb.de", "ptbtime3.ptb.de");
  while (currentTime == 0) 
  {
    currentTime = time(NULL);
    if (currentTime == 0) 
    {
      Serial.println("Did not get a time, yet, retry in a second...");
      delay(1000);
    } 
  }
  Serial.print("Fetched NTP epoch time is: ");
  Serial.println(currentTime);
}

bool initialized = false;


void processMessage(int Count, KeyValuePair Properties[])
{
    Serial.printf("Got %d elements", Count);
    Serial.println();
    for (int i=0; i < Count; i++)
    {
      Serial.print(Properties[i].key);
      Serial.print(":\t");
      Serial.println(Properties[i].value);
    }
}


void loop() {
  if (!initialized)
  {
    Serial.println("Initialize...");
    initialized = init_mqtt(connectionString);
  }
  if (!initialized)
  {
    Serial.println("Initialize failed");
    delay(1000);
    return;
  }

  do_mqtt();
  delay(200);
     
}

