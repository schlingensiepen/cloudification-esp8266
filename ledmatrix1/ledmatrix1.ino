#include <SPI.h>
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 1
#define CS_PIN1 D8
#define CS_PIN2 D4
LedMatrix ledMatrix1 = LedMatrix(NUMBER_OF_DEVICES, CS_PIN1);
LedMatrix ledMatrix2 = LedMatrix(NUMBER_OF_DEVICES, CS_PIN2);

void setup() {
  Serial.begin(9600); // For debugging output
  ledMatrix1.init();
  ledMatrix1.setIntensity(4); // range is 0-15
  ledMatrix1.setText("Digitalisierung");
  ledMatrix2.init();
  ledMatrix2.setIntensity(4); // range is 0-15
  ledMatrix2.setText("Cloudification");
}

void loop() {
  ledMatrix1.clear();
  ledMatrix1.scrollTextLeft();
  ledMatrix1.drawText();
  ledMatrix1.commit(); // commit transfers the byte buffer to the displays
  ledMatrix2.clear();
  ledMatrix2.scrollTextLeft();
  ledMatrix2.drawText();
  ledMatrix2.commit(); // commit transfers the byte buffer to the displays
  delay(200);
}
