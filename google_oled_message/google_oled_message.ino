
#include <ESP8266WiFi.h>

#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>
#include <Wire.h>  
#include "SSD1306Wire.h" 
#include "SSD1306Spi.h" 
#include "AdafruitIO_WiFi.h"



#define IO_USERNAME    "glnsrikar"
#define IO_KEY         "5de6fd7a34994effb2d8fc867f41e9d3"
char ssid[] = "hobby kit"; 
char pass[] = "123456789"; 

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid,  pass);


 

SSD1306Wire  display(0x3c, D3, D4); 


AdafruitIO_Feed *command = io.feed("voice-commands"); // Set up the 'command' feed


void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  
  display.init();
  display.flipScreenVertically();
  display.setContrast(255);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  io.connect();
  command->onMessage(handleMessage);  
}

// MAIN CODE
void loop()
{
  io.run();
}

// this part of the code runs whenever there's a new message on Adafruit.io feed
void handleMessage(AdafruitIO_Data *data) {
  
  String commandStr = data->toString(); // store the incoming commands in a string
  
  // received message
  Serial.print("received <- ");
  Serial.println(commandStr);
  
  display.clear();
    display.drawString(0,0,commandStr);
    display.display();
} 
