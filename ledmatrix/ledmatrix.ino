/* Include the LedControl library */ 
#include "LedControl.h"

/* Create a new LedControl variable.
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221
 * There will only be a single MAX7221 attached to the arduino 
 */  
LedControl lc1=LedControl(D7,D5,D8,1); 
LedControl lc2=LedControl(D7,D5,D4,1); 

void setup() {
    //wake up the MAX72XX from power-saving mode
    lc1.shutdown(0,false); 
    //set a medium brightness for the Leds
    lc1.setIntensity(0,8);
    lc1.clearDisplay(0); 

    //wake up the MAX72XX from power-saving mode
    lc2.shutdown(0,false); 
    //set a medium brightness for the Leds
    lc2.setIntensity(0,8);
    lc2.clearDisplay(0); 
}
int counter =0;
void loop() 
{
/* Set the status of a single Led.
 * Params :
 *   addr  address of the display
 *   row   the row of the Led (0..7)
 *   col   the column of the Led (0..7)
 *   state If true the led is switched on, if false it is switched off 
*/ 
    lc1.clearDisplay(0);
    lc1.setLed(0, counter/8, counter%8, true);

    lc2.clearDisplay(0);
    lc2.setLed(0, counter%8, counter/8, true);


    delay(100);
    counter++;
    if (counter >= 64) counter=0; 
}
