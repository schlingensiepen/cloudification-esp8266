#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "digitalisierung";
const char* pass = "cloudification";

const char* mqtt_server = "m23.cloudmqtt.com";
const int   mqtt_port = 16912;
const char* mqtt_user = "";
const char* mqtt_password = "";

const int buzzPin=1;          // the number of the buzzer pin
const int buttonPin1 = 5;     // the number of the pushbutton pin
const int buttonPin2 = 4;     // the number of the pushbutton pin
const int ledPin1 =  14;      // the number of the LED pin
const int ledPin2 =  12;      // the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

char* button1topic = "sensor/button1";
char* button2topic = "sensor/button2";
char* led1topic = "actor/led1";
char* led2topic = "actor/led2";
char* buzzertopic = "actor/buzzer";

enum buttonPressingType
{
  pressed,
  released
};
buttonPressingType buttonPressing1 = released;
buttonPressingType buttonPressing2 = released;


WiFiClient espClient;
PubSubClient client(espClient);

unsigned long endBuzzerTime = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  payload[length] = 0;

  String s_topic   = String(topic);
  s_topic.trim();
  s_topic.toLowerCase();
    
  String s_payload = String((char *)payload);
  s_payload.trim();
  s_payload.toLowerCase();

  Serial.print(s_payload);
  Serial.println();

  int led = -1;
  if (s_topic.equals(led1topic)) led = ledPin1;
  if (s_topic.equals(led2topic)) led = ledPin2;

  int level = -1;
  if (s_payload.equals("on")) level = HIGH;
  if (s_payload.equals("off")) level = LOW;

  if (led >= 0 && level >= 0)
  {
    digitalWrite(led, level);    
    return;
  }

  if (!s_topic.equals(buzzertopic)) return;


  long tonePitch = s_payload.substring(0, s_payload.indexOf(",")).toInt();
  long duration = s_payload.substring(s_payload.lastIndexOf(",")+1).toInt();

  Serial.println("Buzzer");
  Serial.print ("Tone pitch ..: ");
  Serial.println(tonePitch);
  Serial.print ("Duration ....: ");
  Serial.println(duration);
  Serial.flush();
  
  endBuzzerTime = millis() + duration;
  tone(buzzPin, tonePitch);
}


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
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      subscribe(led1topic);
      subscribe(led2topic);
      subscribe(buzzertopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void subscribe(char* topic)
{
  Serial.print ("Subscripe to: ");
  Serial.println(topic);

  client.subscribe(topic);
}

void publish(char* topic, char* message, char* data)
{
  Serial.println (message);
  Serial.print (topic);
  Serial.print (" : ");
  Serial.print (data);
  
  if (client.publish(topic, data)) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }  
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  if (buttonPressing1 == pressed && buttonState1 == LOW)
  {
    buttonPressing1 = released;
    publish(button1topic, "Button 1 released", "released");
  }
  if (buttonPressing1 == released && buttonState1 == HIGH)
  {
    buttonPressing1 = pressed;
    publish (button1topic, "Button 1 pressed", "pressed");    
  }
  if (buttonPressing2 == pressed && buttonState2 == LOW)
  {
    buttonPressing2 = released;
    publish(button2topic, "Button 2 released", "released");
  }
  if (buttonPressing2 == released && buttonState2 == HIGH)
  {
    buttonPressing2 = pressed;
    publish (button2topic, "Button 2 pressed", "pressed");    
  }
  if (endBuzzerTime != 0 && millis() > endBuzzerTime)
  {
    endBuzzerTime = 0;   
    noTone(buzzPin);     
    Serial.begin(9600);
    delay(10);
    Serial.flush();
    Serial.println();
    Serial.println("Silence");
  }
}


