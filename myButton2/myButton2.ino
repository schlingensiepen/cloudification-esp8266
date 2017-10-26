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
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState2 == HIGH) {
    // turn LED on:
    digitalWrite(ledPin2, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin2, LOW);
  }

}
