#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

// D5 is RX of ESP8266, connect to TX of DFPlayer
// D6 is TX of ESP8266, connect to RX of DFPlayer module
SoftwareSerial dfPlaySerial(D5, D8);

#include "DFPlay.h"
DFPlay dfPlay;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ISbbvKpXcRDQgqxj5inIfv2Ro3nnKkdj";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ASUS";
char pass[] = "12345679";

#define PLAY_MODE_OFF         0
#define PLAY_MODE_TRACK       1
#define PLAY_MODE_ALL         2
int playmode = PLAY_MODE_OFF;

#define DFPLAY_MEDIA_USB 1
#define DFPLAY_MEDIA_SD  2

#define VPIN_PLAYTRACK   V4
#define VPIN_MUSICPLAYER V5
#define VPIN_VOLUME      V6
#define VPIN_EQUALIZER   V7

int currentTrackCount = -1;

BLYNK_CONNECTED() {
  // Synchronize volume & equalizer of DFPlayer with Blynk widgets
  Blynk.syncVirtual(VPIN_VOLUME);
  Blynk.syncVirtual(VPIN_EQUALIZER);

  // Update music player widget (play/stop button and label) based on state DFPlayer
  if (currentTrackCount >= 0)
  {
    String trackcountString(currentTrackCount + 1); // Start with 1 instead of 0 in user interface
    Blynk.virtualWrite(VPIN_MUSICPLAYER, "play");
    Blynk.setProperty(VPIN_MUSICPLAYER, "label", trackcountString);
  }
  else
  {
    Blynk.virtualWrite(VPIN_MUSICPLAYER, "stop");
    Blynk.setProperty(VPIN_MUSICPLAYER, "label", " ");
  }
}

BLYNK_WRITE(VPIN_PLAYTRACK)
{
  int tracknr = param.asInt();
#ifdef BLYNK_PRINT
  BLYNK_PRINT.print("BLYNK_WRITE(VPIN_PLAYTRACK): ");
  BLYNK_PRINT.println(tracknr);
#endif

  if (tracknr > 0)
  {
    String trackcountString(tracknr);
    dfPlay.play(DFPLAY_MEDIA_SD, 0, tracknr); // Plays tracknr in root folder on SD-card
    playmode = PLAY_MODE_TRACK;
    currentTrackCount = -1;
    Blynk.setProperty(VPIN_MUSICPLAYER, "label", trackcountString);
    Blynk.virtualWrite(VPIN_MUSICPLAYER, "play");
  }
}


BLYNK_WRITE(VPIN_MUSICPLAYER)
{
  String action = param.asStr();
#ifdef BLYNK_PRINT
  BLYNK_PRINT.print("BLYNK_WRITE(VPIN_MUSICPLAYER): ");
  BLYNK_PRINT.println(action);
#endif

  if (action == "play") {
    dfPlay.play(DFPLAY_MEDIA_SD); // Plays all tracks in root folder of SD-card
    playmode = PLAY_MODE_ALL;
  }
  if (action == "stop") {
    dfPlay.stop();
  }
  if (action == "next") {
    dfPlay.skip();
  }
  if (action == "prev") {
    dfPlay.back();
  }
}

BLYNK_WRITE(VPIN_VOLUME)
{
  int paramVol = param.asInt();
  uint8_t volume = constrain(paramVol, 0, 30);
#ifdef BLYNK_PRINT
  BLYNK_PRINT.print("BLYNK_WRITE(VPIN_VOLUME): ");
  BLYNK_PRINT.println(paramVol);
#endif

  dfPlay.setVolume(volume);
}

BLYNK_WRITE(VPIN_EQUALIZER)
{
  int paramEq = param.asInt();
  uint8_t eq = constrain(paramEq, 1, 6) - 1; // Blynk starts with 1, setEqualizer starts with 0

#ifdef BLYNK_PRINT
  BLYNK_PRINT.print("BLYNK_WRITE(VPIN_EQUALIZER): ");
  BLYNK_PRINT.println(paramEq);
#endif

  dfPlay.setEqualizer(eq);
}

void updatePlayerState()
{
  int trackcount;

  if (dfPlay.isPlaying())
  {
    trackcount = (int)dfPlay.getTrackCount();
  }
  else
  {
    trackcount = -1;
    playmode = PLAY_MODE_OFF;
  }

  if (trackcount != currentTrackCount)
  {
    switch (playmode)
    {
      case PLAY_MODE_OFF:
        Blynk.setProperty(VPIN_MUSICPLAYER, "label", " ");
        Blynk.virtualWrite(VPIN_MUSICPLAYER, "stop");
        break;


      case PLAY_MODE_ALL:
        String trackcountString(trackcount + 1); // Start with 1 instead of 0 in user interface
        Blynk.setProperty(VPIN_MUSICPLAYER, "label", trackcountString);
        Blynk.virtualWrite(VPIN_MUSICPLAYER, "play");
        break;
    }

    currentTrackCount = trackcount;
  }
}

void setup()
{
  // Debug console
#ifdef BLYNK_PRINT
  BLYNK_PRINT.begin(115200);
  BLYNK_PRINT.println("Waiting for connections...");
#endif

  dfPlaySerial.begin(9600);
  dfPlay.begin(dfPlaySerial);          // Prepares DFPlay for execution

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}


void loop()
{
  Blynk.run();
  dfPlay.manageDevice(); // Sends requests to DFPlayer & processes responses.
  updatePlayerState();
}
