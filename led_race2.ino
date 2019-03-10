/*  
 
LED RACE
 An minimalist cars race for LED strip  

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 by gbarbarov@singulardevices.com  for Arduino day Seville 2019 

*/

                                                            
#include <Adafruit_NeoPixel.h>
#define PIN_LED        A0
#define PIN_P1         7
#define PIN_P2         6
#define PIN_AUDIO      3

#define COLOR1    track.Color(255,0,0)
#define COLOR2    track.Color(0,255,0)

int win_music[] = {
  2637, 2637, 0, 2637, 
  0, 2093, 2637, 0,
  3136    
};
      

int TBEEP=4; 

float speed1=0;
float speed2=0;
float dist1=0;
float dist2=0;

byte loop1=0;
byte loop2=0;

byte leader=0;
byte loop_max=5;

int NPIXELS=300;
float ACEL=0.2;
float FRICTION=0.01;
float kf=1.5;

byte flag_sw1=0;
byte flag_sw2=0;
byte draworder=0;
 
unsigned long timestamp=0;

Adafruit_NeoPixel track = Adafruit_NeoPixel(NPIXELS, PIN_LED, NEO_GRB + NEO_KHZ800);

int tdelay = 5; 

void setup() {
  track.begin(); 
  pinMode(PIN_P1,INPUT_PULLUP); 
  pinMode(PIN_P2,INPUT_PULLUP);  
  start_race();
}

void start_race(){for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(0,0,0));};
                  track.show();
                  delay(2000);
                  track.setPixelColor(12, track.Color(0,255,0));
                  track.setPixelColor(11, track.Color(0,255,0));
                  track.show();
                  tone(PIN_AUDIO,400);
                  delay(2000);
                  noTone(PIN_AUDIO);                  
                  track.setPixelColor(12, track.Color(0,0,0));
                  track.setPixelColor(11, track.Color(0,0,0));
                  track.setPixelColor(10, track.Color(255,255,0));
                  track.setPixelColor(9, track.Color(255,255,0));
                  track.show();
                  tone(PIN_AUDIO,600);
                  delay(2000);
                  noTone(PIN_AUDIO);                  
                  track.setPixelColor(9, track.Color(0,0,0));
                  track.setPixelColor(10, track.Color(0,0,0));
                  track.setPixelColor(8, track.Color(255,0,0));
                  track.setPixelColor(7, track.Color(255,0,0));
                  track.show();
                  tone(PIN_AUDIO,1200);
                  delay(2000);
                  noTone(PIN_AUDIO);                               
                  timestamp=0;              
                 };

void winner_fx() {/*for(int i=0;i<6;i++){tone(PIN_AUDIO,400+i*100);
                                    delay(300-i*20);
                                   }
               noTone(PIN_AUDIO);  
               for(int i=0;i<=loop1;i++) {track.setPixelColor(i, track.Color(0,0,0));};
               track.show(); 
               delay(4000);    
                */
               int msize = sizeof(win_music) / sizeof(int);
               for (int note = 0; note < msize; note++) {
               tone(PIN_AUDIO, win_music[note],200);
               delay(230);
               noTone(PIN_AUDIO);

}

                                               
              };

void burning1(){
//to do
 }

void burning2(){
//to do
 }

void track_rain_fx(){
//to do
 }

void track_oil_fx(){
//to do
 }

void draw_safety_car(){
//to do
 }

void draw_car1(void){for(int i=0;i<=loop1;i++){track.setPixelColor(((word)dist1 % NPIXELS)+i, track.Color(0,255-i*50,0));};   //i not see FX dimmer light ? Why ???                 
  }

void draw_car2(void){for(int i=0;i<=loop2;i++){track.setPixelColor(((word)dist2 % NPIXELS)+i, track.Color(255-i*50,0,0));};            
 }
  
void loop() {
    for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(0,0,0));};
    if ( (flag_sw1==1) && (digitalRead(PIN_P1)==0) ) {flag_sw1=0;speed1+=ACEL;};
    if ( (flag_sw1==0) && (digitalRead(PIN_P1)==1) ) {flag_sw1=1;};
    
    speed1-=FRICTION*speed1*kf; 
    if (speed1<0) {speed1=0;};

    if ( (flag_sw2==1) && (digitalRead(PIN_P2)==0) ) {flag_sw2=0;speed2+=ACEL;};
    if ( (flag_sw2==0) && (digitalRead(PIN_P2)==1) ) {flag_sw2=1;};
    
    speed2-=FRICTION*speed2*kf; 
    if (speed2<0) {speed2=0;};
    
    dist1=dist1+speed1;
    dist2=dist2+speed2;

    if (dist1>dist2) {leader=1;} 
    if (dist2>dist1) {leader=2;};
      
    if (dist1>NPIXELS*loop1) {loop1++;tone(PIN_AUDIO,600);TBEEP=2;};
    if (dist2>NPIXELS*loop2) {loop2++;tone(PIN_AUDIO,700);TBEEP=2;};

    if (loop1>loop_max) {for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(0,255,0));}; track.show();
                                                    winner_fx();loop1=0;loop2=0;dist1=0;dist2=0;speed1=0;speed2=0;timestamp=0;
                                                    start_race();
                                                   }
    if (loop2>loop_max) {for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(255,0,0));}; track.show();
                                                    winner_fx();loop1=0;loop2=0;dist1=0;dist2=0;speed1=0;speed2=0;timestamp=0;
                                                    start_race();
                                                   }
    if ((millis() & 512)==(512*draworder)) {if (draworder==0) {draworder=1;}
                          else {draworder=0;}   
                         }; 

    if (draworder==0) {draw_car1();draw_car2();}
        else {draw_car2();draw_car1();}   
                 
    track.show(); 
    delay(tdelay);
    
    if (TBEEP>0) {TBEEP-=1; 
                  if (TBEEP==0) {noTone(PIN_AUDIO);}; // lib conflict !!!! interruption off by neopixel
                 };   
}
