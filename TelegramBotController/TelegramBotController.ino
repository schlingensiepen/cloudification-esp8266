/**
    TelegramBotController
    Example show how to receive and send messages via Telegram's Bot API.
    It also demonstrates how to use a custom keyboard shown to the user
  
    Part of TelegramBotClient (https://github.com/schlingensiepen/TelegramBotClient)    
    Jörn Schlingensiepen <joern@schlingensiepen.com>

    Client's API:   https://schlingensiepen.github.io/TelegramBotClient/
    Telegram's API: https://core.telegram.org/bots/api
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <strings.h>

#include <TelegramBotClient.h>

// Instantiate Wifi connection credentials
const char* ssid     = "digitalisierung";
const char* password = "cloudification";

const int buzzPin=1;          // the number of the buzzer pin
const int buttonPin1 = 5;     // the number of the pushbutton pin
const int buttonPin2 = 4;     // the number of the pushbutton pin
const int ledPin1 =  14;      // the number of the LED pin
const int ledPin2 =  12;      // the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

int basePitch = 523;
unsigned long pollTimeOut = 2000;

// Instantiate Telegram Bot secure token
// This is provided by BotFather
const String botToken = "<< YOUR BOT TOKEN >>";

// Instantiate the ssl client used to communicate with Telegram's web API
WiFiClientSecure sslPollClient;

// Instantiate the client with secure token and client
TelegramBotClient client(
      botToken, 
      sslPollClient);

// Instantiate a keybord with 2 rows
TBCKeyBoard board(2);

enum buttonPressingType
{
  pressed,
  released
};

buttonPressingType buttonPressing1 = released;
buttonPressingType buttonPressing2 = released;

long lastChatId;

void processMessage(String message)
{
  Serial.print("Message arrived: ");
  Serial.println(message);
  message.toLowerCase();
  
  int led = -1;
  int level = -1;
  bool buzzer = false;
  int tonePitch = -1;


  char* pch = strdup(message.c_str());
  pch = strdup (message.c_str());  
  pch = strtok (pch," ");
  while (pch != NULL)
  {
    Serial.print("Token: [");
    Serial.print(pch);
    Serial.println("]");
    if (strcmp(pch, "led1") == 0) led = ledPin1;
    if (strcmp(pch, "led2") == 0) led = ledPin2;
    if (strcmp(pch, "on")   == 0) level = HIGH;
    if (strcmp(pch, "off")  == 0) level = LOW;
    if (strcmp(pch, "buzz") == 0) buzzer = true;
    if (strcmp(pch, "c5")   == 0) tonePitch = basePitch;
    if (strcmp(pch, "e5")   == 0) tonePitch = basePitch * 1.25;
    if (strcmp(pch, "g5")   == 0) tonePitch = basePitch * 1.5;
    if (strcmp(pch, "c6")   == 0) tonePitch = basePitch * 2;
    
    pch = strtok (NULL, " "); 
  }
  if (led >= 0 && level >= 0)
  {
    Serial.print("Turn LED");
    Serial.print(led);
    Serial.print(" to ");
    Serial.println(level);
    digitalWrite(led, level);    
  }

  if (buzzer && tonePitch > 0)
  {
    Serial.flush();
    Serial.end();
    tone(buzzPin, tonePitch);
    delay(1000);
    Serial.begin (115200);    
    Serial.flush();
  }  
}

// Function called on receiving a message
void onReceive (TelegramProcessError tbcErr, JwcProcessError jwcErr, Message* msg)
{      
    lastChatId = msg->ChatId;

    Serial.println("onReceive");
    Serial.print("tbcErr"); Serial.print((int)tbcErr); Serial.print(":"); Serial.println(toString(tbcErr));
    Serial.print("jwcErr"); Serial.print((int)jwcErr); Serial.print(":"); Serial.println(toString(jwcErr));
  
    Serial.print("UpdateId: "); Serial.println(msg->UpdateId);      
    Serial.print("MessageId: "); Serial.println(msg->MessageId);
    Serial.print("FromId: "); Serial.println(msg->FromId);
    Serial.print("FromIsBot: "); Serial.println(msg->FromIsBot);
    Serial.print("FromFirstName: "); Serial.println(msg->FromFirstName);
    Serial.print("FromLastName: "); Serial.println(msg->FromLastName);
    Serial.print("FromLanguageCode: "); Serial.println(msg->FromLanguageCode); 
    Serial.print("ChatId: "); Serial.println(msg->ChatId);
    Serial.print("ChatFirstName: "); Serial.println(msg->ChatFirstName);
    Serial.print("ChatLastName: "); Serial.println(msg->ChatLastName);
    Serial.print("ChatType: "); Serial.println(msg->ChatType);
    Serial.print("Text: "); Serial.println(msg->Text);
    Serial.print("Date: "); Serial.println(msg->Date);

    // Sending the text of received message back to the same chat
    // and add the custom keyboard to the message
    // chat is identified by an id stored in the ChatId attribute of msg    
    processMessage(msg->Text);    
}



// Function called if an error occures
void onError (TelegramProcessError tbcErr, JwcProcessError jwcErr)
{
  Serial.println("onError");
  Serial.print("tbcErr"); Serial.print((int)tbcErr); Serial.print(":"); Serial.println(toString(tbcErr));
  Serial.print("jwcErr"); Serial.print((int)jwcErr); Serial.print(":"); Serial.println(toString(jwcErr));
}

// Setup WiFi connection using credential defined at begin of file
void setupWiFi()
{
  Serial.println();
  Serial.printf("Try to connect to network %s ",ssid);
  Serial.println();
    
  WiFi.begin(ssid, password);
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

// Setup
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  setupWiFi();

  // initialize the LED pins as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pins as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  // Adding the 2 rows to the keyboard
  String row1[] = {"LED1 on", "LED2 on", "Buzz C5", "Buzz G5"};
  String row2[] = {"LED1 off", "LED2 off", "Buzz E5", "Buzz C6"};

  board
    .push(4, row1)
    .push(4, row2);
  
  // Sets the functions implemented above as so called callback functions,
  // thus the client will call this function on receiving data or on error.
  client.begin(      
      onReceive,
      onError);    
}


void sendMessage(char* message)
{
    Serial.print("Message ..: ");
    Serial.println(message);
    Serial.print("Chat id ..: ");        
    Serial.println(lastChatId);
    client.postMessage(lastChatId, message, board);
}


// Loop
void loop() {
  // To process receiving data this method has to be called each main loop()
  client.loop();
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

    if (buttonPressing1 == pressed && buttonState1 == LOW)
    { 
      buttonPressing1 = released;
      sendMessage("Button 1 released");
    }
    if (buttonPressing1 == released && buttonState1 == HIGH)
    {
      buttonPressing1 = pressed;
      sendMessage("Button 1 pressed");    
    }
    if (buttonPressing2 == pressed && buttonState2 == LOW)
    {
      buttonPressing2 = released;
      sendMessage("Button 2 released");
    }
    if (buttonPressing2 == released && buttonState2 == HIGH)
    {
      buttonPressing2 = pressed;
      sendMessage("Button 2 pressed");    
    }
}
