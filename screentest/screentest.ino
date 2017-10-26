#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

int counter = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Digitalisierung");
  display.println("Cloudification");
  display.display();

}

void loop() {
  // draw a white circle, 6 pixel radius  
  display.fillCircle(((counter %4) +0.5) * display.width()/4, 3* display.height()/4, 6, BLACK);
  counter++;
  display.fillCircle(((counter %4) +0.5) * display.width()/4, 3* display.height()/4, 6, WHITE);
  display.display();
  delay(500);
}

