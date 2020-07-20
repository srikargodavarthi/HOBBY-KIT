


// HELLO..,; WELCOM TO MY CODE ..,/;'

// SUBSCRIBE TO MY CHANNEL =HOBBY KIT //
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trigPin 4
#define echoPin 5

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "5J7uOTj7ToKA5a4GEk8kP5B5Sy_3klbK";// AUTH TOKEN FROM BLYNK APP

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HOBBY KIT ";// WIFI NAME 
char pass[] = "12346789";// WIFI PASSWORD 
WidgetLCD lcd(V1);
int counter = 0;
int currentState1 = 0;
int previousState1 = 0;
int currentState2 = 0;
int previousState2 = 0;
int inside = 0;
int outside = 0;


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  
lcd.print(0, 0,"IN: ");

lcd.print(8, 0,"OUT: ");

lcd.print(0, 1,"Total Inside: ");
long duration, distance;
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance <= 9){
currentState1 = 1;
}
else {
currentState1 = 0;
}
delay(100);
if(currentState1 != previousState1){
if(currentState1 == 1){
counter = counter + 1;}

lcd.print(14, 1,counter);
inside = inside +1;}

lcd.print(4, 0,inside);
if (distance > 9 && distance <= 18){
currentState2 = 1;
}
else {
currentState2 = 0;
}
delay(100);
if(currentState2 != previousState2){
if(currentState2 == 1){
counter = counter - 1;}

lcd.print(14, 1,counter);
outside = outside +1;}

lcd.print(13, 0,outside);
lcd.print(14, 1,counter);
if (counter > 9 || counter < 0){
lcd.print(14, 1,counter);
delay(100);
lcd.clear();
 }

if (counter > 9 || counter < 0){
lcd.print(14, 1,counter);
delay(100);
lcd.clear();
}
  Blynk.run();
}
