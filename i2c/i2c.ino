#include "Wire.h"

int startAddr = 0x03;
int endAddr = 0x7F;

int currentAddr = startAddr;

char buf[256];
 
void setup() {
    Wire.begin();
    Serial.begin(9600);
    sprintf(buf, "Scanning address range 0x%02X - 0x%02X\n\n", startAddr, endAddr);
    Serial.println(buf);
}

void loop() 
{ 
  if (currentAddr > endAddr) return;

  if (currentAddr % 16 == 0) 
  {
    Serial.println();
    sprintf(buf, "%02X: ", currentAddr);
    Serial.print(buf);
  }
   
  Wire.beginTransmission(currentAddr);
  byte error = Wire.endTransmission();
  if (error) 
  {
    Serial.print("..");
  } 
  else 
  {
    sprintf(buf, "%02X", currentAddr);
    Serial.print(buf);
  }
  currentAddr++;
}

