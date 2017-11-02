#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "digitalisierung";
const char* pass = "cloudification";

const char* host = "api.schlingensiepen.com";
const int port = 80;

const char* scheme = "http";
const char* path = "/iot/getDateTime/";
const int timeout = 10000;

String prefix = "http://api.schlingensiepen.com/iot/";
String commands[] = {
  "getDate", "getDateTime", "getHost", "getIP", "getTime", "getUser", 
  "ping", "generateBullshit", "generateRandomNumber", };
int commandCounter = 0;
  
HTTPClient http;

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

  String url = prefix + commands[commandCounter] + "/";

  Serial.println("Try to retrieve " + url);

  http.begin(url);
  int err = http.GET();
  if (err == 200)
  {
    String content = http.getString();
    Serial.println(content);
  }
  else
  {
    Serial.printf("Got an error, error code:%d", err);
    delay(10000);
  }
  Serial.println("Closing connection");
  http.end();
  
  commandCounter++;
  if (commandCounter >= sizeof(commands)/sizeof(commands[0])) commandCounter = 0;

  delay(3000);
}
