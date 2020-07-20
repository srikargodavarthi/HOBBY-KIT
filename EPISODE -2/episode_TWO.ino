#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include"ssd1306Wire.h"
ssd1306Wire display(0x3c,D3,D4);
// Change here the ssid and password to your own.
const char *ssid = "hobby kit";
const char *pass = "";

ESP8266WebServer server(80);

String WEBPAGE="<html>\
  <head>\
    <title>hobby kit Demo</title>\
  </head>\
  <body>\
    <h1>welcom to hobby kit</h1>\
    <p>You can enter text here and it will output on the oled screen </p>\
    <form action='http://192.168.4.1/submit' method='POST'>\
      ENTER TEXT: <input type='text' name='input'><br>\
      <input type='submit' value='Submit'>\
    </form>\
  </body>\
</html>";


void pageone() {
  
  server.send(200, "text/html", WEBPAGE);
}

void pageTWO() {
  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "input");
       Serial.print(server.args());
      
    }
  }
  
  server.send(200, "text/html", WEBPAGE);
}


void setup() {
     Serial.begin(115220);
     Serial.println("");
     display.init();
  display.flipScreenVertically();
  
  display.setContrast(255);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
     Serial.print(WiFi.softAPIP());
     WiFi.softAP(ssid, pass);
     server.on("/",pageone);
     server.on("/submit", pageTWO);
     server.begin();

      
}

void loop() {
  server.handleClient();

}
