

#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>

// D5 is RX of ESP8266, connect to TX of DFPlayer
// D6 is TX of ESP8266, connect to RX of DFPlayer module
SoftwareSerial dfPlaySerial(D4,D5);
#include "DFPlay.h"
DFPlay dfPlay;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hobbykit";
char pass[] = "123456";

#define PLAY_MODE_OFF         0
#define PLAY_MODE_TRACK       1
#define PLAY_MODE_ALL         2
int playmode = PLAY_MODE_OFF;

#define DFPLAY_MEDIA_USB 1
#define DFPLAY_MEDIA_SD  2

#define SENSORPIN D1
int currentTrackCount = -1;


void setup()
{
  // Debug console
  pinMode(SENSORPIN, INPUT);


  dfPlaySerial.begin(9600);
  dfPlay.begin(dfPlaySerial);          // Prepares DFPlay for execution

  WiFi.begin(ssid,pass);
 dfPlay.setVolume(30);

}
void loop()
{
 
    
 int detect = digitalRead(SENSORPIN);// read obstacle status and store it into "detect"
  if(detect == LOW){
    
 dfPlay.play(DFPLAY_MEDIA_SD, 0,detect); // Plays tracknr in root folder on SD-card
    playmode = PLAY_MODE_TRACK;
  
}
  
  dfPlay.manageDevice(); // Sends requests to DFPlayer & processes responses.
  
}
