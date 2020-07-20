
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SPI.h> 
#include <Wire.h>  
#include "SSD1306Wire.h" 
#include "SSD1306Spi.h" 
 

SSD1306Wire  display(0x3c, D3, D4); 

// Change here the ssid and password to your own.
const char *ssid = "hobby kit";
const char *password = "";




// Your webpage to show in string form.
String webPage = "<html>\
  <head>\
    <title>hobby kit Demo</title>\
  </head>\
  <body>\
    <h1>welcom to hobby kit</h1>\
    <p>You can enter text here and it will output on the oled screen </p>\
    <form action='http://192.168.4.1/submit' method='POST'>\
      Input: <input type='text' name='input'><br>\
      <input type='submit' value='Submit'>\
    </form>\
  </body>\
</html>";
ESP8266WebServer server(80); // webserver on port 80


// Send the webpage when going to ESP8266s ip address
void handleRoot() {
  server.send(200, "text/html", webPage);
}

// Handle the submit Button
void handleSubmit(){
  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "input") {
         // If the argumentName is input print out result on OLED Screen.
         display.clear();
         
         display.drawString(0,0, "IP address: " + WiFi.softAPIP().toString());
         display.drawString(0,11, "welcome to hobbykit " );
         display.drawString(0,20, "output: " + server.arg(i));
         display.display();
      }
    }
  }
  // Send the webpage again so users can enter text again.
  server.send(200, "text/html", webPage);
}

void setup() {
  // Init and flip the OLED display
  display.init();
  display.flipScreenVertically();
  // Set contrast and font
  display.setContrast(255);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // Startup Wifi Access Point
  WiFi.softAP(ssid, password);
  delay(500);

  // Display some info on the OLED
  display.clear();
  display.drawString(0,0, "IP address: " + WiFi.softAPIP().toString()); // The Ip of the ESPitself so you know where to go when connected.
   display.drawString(0,11, "subscribe hobby kit" );
  display.display();

  // Start WebSockets on '/' and '/submit' for the form submit.
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.begin();
}

// handle websocket requests forever.
void loop() {
  server.handleClient();
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
