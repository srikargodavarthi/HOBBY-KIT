#include <ESP8266WiFi.h>
#include <Wire.h>  
#include "SSD1306Wire.h" 
 
 

SSD1306Wire  display(0x3c, D3, D4);  //D3=SDa  D4=SCK  

 
void setup() {
  delay(1000);
 
  Serial.begin(115200);  
  Serial.println("");
  
  Serial.println("Initializing OLED Display");
 display.init();
 

  display.setFont(ArialMT_Plain_10);
}
 

void loop() {
   display.clear(); 
   display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0,"subscribe hobbykit");
  display.display();
  
}

 
