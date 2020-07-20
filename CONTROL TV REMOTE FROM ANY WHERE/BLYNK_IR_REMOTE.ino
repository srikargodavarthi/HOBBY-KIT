#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//IR library
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  //d2 in nodemcu
IRsend irsend(kIrLed);

char auth[] = "ISbbvKpXcRDQgqxj5inIfv2Ro3nnKkdj";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HOBBY KIT";
char pass[] = "123456789";

  BLYNK_WRITE(V1) { // VOLUME UP
  if (param.asInt() == 0) {
  //Serial.println("NEC");
  irsend.sendNEC(  0x80BF01FE ,32);
  }
  }

  BLYNK_WRITE(V2) { //VOLUME DOWN
  if (param.asInt() == 0) {
  //Serial.println("NEC");
  irsend.sendNEC(0x80BF817E,32);
  }
  }

  BLYNK_WRITE(V3) { // CH UP 
  if (param.asInt() == 0) {
  //Serial.println("NEC");
  irsend.sendNEC(0x80BFA15E,32);
  }
  }

 BLYNK_WRITE(V4) { // CH down
  if (param.asInt() == 0) {
  //Serial.println("NEC");
  irsend.sendNEC(0x80BF619E     
,32);
  }
  }
  

void setup()
{
  
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
