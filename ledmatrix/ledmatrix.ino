/* Include the LedControl library */ 
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
  ledMatrix2.init();
  ledMatrix2.setIntensity(4); // range is 0-15
}
int counter =0;
void loop() 
{
    ledMatrix1.clear();
    ledMatrix1.setPixel(counter/8, counter%8);
    ledMatrix1.commit();
    
    ledMatrix2.clear();
    ledMatrix2.setPixel(counter%8, counter/8);
    ledMatrix2.commit();

    delay(200);
    counter++;
    if (counter >= 64) counter=0; 
}
