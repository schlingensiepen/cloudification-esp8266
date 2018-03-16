/*
  Blink1
  Lets the lamps on D5 and D6 flash alternately

  Sample by Jörn Schlingensiepen
*/

#define LED1 D5
#define LED2 D6

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins LED1 and LED2 as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);  // turn the LED1 on by making the voltage HIGH
  digitalWrite(LED2, LOW );  // turn the LED2 off by making the voltage LOW
  delay(1000);               // wait for a second
  digitalWrite(LED1, LOW);   // turn the LED1 off by making the voltage LOW
  digitalWrite(LED2, HIGH);  // turn the LED2 on by making the voltage HIGH
  delay(1000);               // wait for a second
}
