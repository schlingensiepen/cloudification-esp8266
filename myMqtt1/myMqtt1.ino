// Simple wrapper for Azure IoT-Hub SDK to use MQTT

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

#include <AzureIoTHub.h>
#include <AzureIoTUtility.h>
#include <AzureIoTProtocol_MQTT.h>

#include "myMqtt.h"

const char* ssid = "digitalisierung";
const char* pass = "cloudification";

const char* connectionString = "HostName=i3cmtesthub.azure-devices.net;DeviceId=gate1;SharedAccessKey=7mnKpOOcWrfXKMaIGwqoMAQ9wxYmrk2JUrZt1uHiJbM=";

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 5;     // the number of the pushbutton pin
const int buttonPin2 = 4;     // the number of the pushbutton pin
const int ledPin1 =  14;      // the number of the LED pin
const int ledPin2 =  12;      // the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

enum buttonPressingType
{
  pressed,
  released
};
buttonPressingType buttonPressing1 = released;
buttonPressingType buttonPressing2 = released;



void setup() {
  Serial.begin(9600);
  delay(10);

  // initialize the LED pins as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pins as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  
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

      if (strcmp(Properties[i].key, "led1")==0)
      {
        int value = atoi(Properties[i].value);
        if (value >= 0 && value <= 255)
        {
          analogWrite(ledPin1, value);
          Serial.print("Set Light 1 to ");
          Serial.println(value);
        }
      }
      if (strcmp(Properties[i].key, "led2") == 0)
      {
        int value = atoi(Properties[i].value);
        if (value >= 0 && value <= 255)
        {
          analogWrite(ledPin2, value);
          Serial.print("Set Light 2 to ");
          Serial.println(value);
        }
      }
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

    // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  if (buttonPressing1 == pressed && buttonState1 == LOW)
  {
    buttonPressing1 = released;
    Serial.println ("Button released");
    sendString("push1");
  }
  if (buttonPressing1 == released && buttonState1 == HIGH)
  {
    buttonPressing1 = pressed;
    Serial.println ("Button pressed");    
  }
  if (buttonPressing2 == pressed && buttonState2 == LOW)
  {
    buttonPressing2 = released;
    Serial.println ("Button released");
    sendString("push2");
  }
  if (buttonPressing2 == released && buttonState2 == HIGH)
  {
    buttonPressing2 = pressed;
    Serial.println ("Button pressed");    
  }

  do_mqtt();
  delay(200);
     
}


