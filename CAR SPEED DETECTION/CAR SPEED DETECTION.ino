#define BLYNK_PRINT Serial


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define ir_s1 D1
#define ir_s2  D2

 char auth[] = "G0D-6tbWyPPtIMoF2nVKvRU-57B0eGIy";  //auth token by blynk app

char ssid[] = "HOBBY KIT";        //ssid ie wifi name            
char pass[] = "123456789";    //password "":



int timer1;
int timer2;

float Time;

int flag1 = 0;
int flag2 = 0;

float distance = 5.0;
float speed;




WidgetLCD lcd(V1);

void setup(){
  

 Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
 
  
  
lcd.print(0, 0,"");
  lcd.clear();
  
lcd.print(0, 0,"welcom to ");
  
lcd.print(1, 1,"ROBOTIC IDEAS");
  delay(2000);
  lcd.clear();
}

void loop() {
 
  
if(digitalRead (ir_s1) == LOW && flag1==0){timer1 = millis(); flag1=1;}

if(digitalRead (ir_s2) == LOW && flag2==0){timer2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){
     if(timer1 > timer2){Time = timer1 - timer2;}
else if(timer2 > timer1){Time = timer2 - timer1;}
 Time=Time/1000;//convert millisecond to second
 speed=(distance/Time);//v=d/t
 speed=speed*3600;//multiply by seconds per hr
 speed=speed/1000;//division by meters per Km
}

if(speed==0){ 

if(flag1==0 && flag2==0){
lcd.print(0, 1,"not detected");}
                    else{
lcd.print(0, 1,"serching...");} 
}
else{
    lcd.clear(); 
    
lcd.print(0, 0,"speed:");
    lcd.print(7, 0,speed);
    lcd.print(12, 0,"Km/Hr  ");
    
  if(speed > 50){lcd.print(0, 1,"over speed"); }
            else{lcd.print(0, 1,"  Normal Speed   "); }    
    delay(3000);
    
    speed = 0;
    flag1 = 0;
    flag2 = 0;

}
Blynk.run();
}
