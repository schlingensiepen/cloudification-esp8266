/*
  myButton
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 5;     // the number of the pushbutton pin
const int buttonPin2 = 4;     // the number of the pushbutton pin
const int ledPin1 =  14;      // the number of the LED pin
const int ledPin2 =  12;      // the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
enum ledAutomatStateType
{
  pressedToOn,
  pressedToOff,
  lightOn,
  lightOff
};
ledAutomatStateType ledAutomatState = lightOff;

void setup() {
  // initialize the LED pins as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pins as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    // turn LED on:
    digitalWrite(ledPin1, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin1, LOW);
  }
  switch(ledAutomatState)
  {
    case pressedToOn:
          // Button was pressed, while LED was off
          if (buttonState2 == LOW)
          {
            // Button was pressed and is now released
            // turn LED on:
            digitalWrite(ledPin2, HIGH);
            // new state LED is on
            ledAutomatState = lightOn;
          }
          break;
    case pressedToOff:
          // Button was pressed, while LED was on
          if (buttonState2 == LOW)
          {
            // Button was pressed and is now released
            // turn LED on:
            digitalWrite(ledPin2, LOW);
            // new state LED is on
            ledAutomatState = lightOff;
          }    
          break;
    case lightOn:
          // Light is on
          if (buttonState2 == HIGH)
          {
            // button is pressed while light is on
            // going to turn off on button release
            ledAutomatState = pressedToOff;
          }
          break;
    case lightOff:
          // Light is off
          if (buttonState2 == HIGH)
          {
            // button is pressed while light is off
            // going to turn on on button release
            ledAutomatState = pressedToOn;
          }
          break;
  }  
}
