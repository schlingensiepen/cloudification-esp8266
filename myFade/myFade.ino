/*
  Fade

  This example shows how to fade an LED on using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin.

*/

#define LED1 D5 // the PWM pin the LED is attached to
#define LED2 D6 // The other LED
           
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pins to be an output:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of LED1
  analogWrite(LED1, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  if (brightness >= 255) digitalWrite(LED2, HIGH);
  if (brightness <= 0) digitalWrite(LED2, LOW);
  
  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;    
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
