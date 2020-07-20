#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>



// Change here the ssid and password to your own.
const char *ssid = "hobby kit";
const char *pass = "";

ESP8266WebServer server(80);

String text="welcome to hobby kit";

void pageone() {
  
  server.send(200, "text/plain", text);
}


void setup() {
     Serial.begin(115220);
     Serial.println("");
     Serial.print(WiFi.softAPIP());
     WiFi.softAP(ssid, password);
     server.on("/",pageone);
     server.begin();

      
}

void loop() {
  server.Client();

}
