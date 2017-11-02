#include <ESP8266WiFi.h>

const char* ssid = "digitalisierung";
const char* pass = "cloudification";

const char* host = "api.schlingensiepen.com";
const int port = 80;

const char* scheme = "http";
const char* path = "/iot/getDateTime/";
const int timeout = 10000;

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

  char* url = new char[255];
  sprintf(url, "%s://%s%s", scheme, host, path);

  Serial.printf("Try to retrieve %s via %s", url, scheme);
  Serial.println();

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  int start = millis();
  while (!client.available())
  {
    if (millis() - start > timeout)
    {
      Serial.println ("Timeout ...");
      client.stop();
      Serial.println ("Client stopped.");
      delay (10000);
      return;            
    }        
  }
  Serial.println("Got response from server:");
  while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.println(line);
  }  
  delay(3000);
}
