#include <ESP8266WiFi.h>

const char* ssid = "digitalisierung";
const char* pass = "cloudification";

const char* host = "api.schlingensiepen.com";
const int port = 80;

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
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) 
  {
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("Strength ...: ");
    Serial.println(WiFi.RSSI());
  }
  else
  {
    Serial.println("Connection lost");
    delay(10000);
    return;        
  }

  Serial.printf("Try to connect to %s at port %d", host, port);
  Serial.println();
  
  WiFiClient client;
  if (client.connect(host, port))
  {
    Serial.println("Connection to host successful.");
  } 
  else
  {
    Serial.println("Connection to host failed.");
    delay(10000);
    return;        
  }
  
  delay(3000);
}
