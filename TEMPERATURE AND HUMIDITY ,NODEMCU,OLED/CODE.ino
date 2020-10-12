#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SSD1306.h"
#include <DHT.h>


char ssid[] = "ASUS";
char pass[] = "9515968191";


#define DHTPIN 4     
#define DHTTYPE DHT11   

SSD1306  display(0x3C, D3, D4);   // D3 -> SDA,D4 -> SCL
DHT dht(DHTPIN, DHTTYPE);



void setup(){
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  dht.begin(); // initialize dht
  WiFi.begin(ssid, pass);

}

void displayWeather(){ //Creating a function to read and display temperature and humidity on OLED display
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)){
    display.clear(); // clearing the display
    display.drawString(5,0, "DHT Failed!");
    return;
  }
   
  display.clear();
  display.drawString(30, 0, "Weather");
  display.drawString(0, 20, "Humidity: " + String(h) + "%\t"); 
  display.drawString(0, 40, "Temp: " + String(t) + "°C"); 
  
  //display.drawString(0, 40, "Temp: " + String(f) + "°F"); 

}
void loop(){

  displayWeather(); //Calling back the displayWeather function
  display.display();

}
