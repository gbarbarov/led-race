/*  
LED RACE
 An minimalist car race with a Led strip  

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

float speed1=0;
float speed2=1.25;
float dist1=0;
float dist2=0;

byte loop1=0;
byte loop2=0;

byte loop_max=5;

int NPIXELS=300;
float ACEL=0.2;
float FRICTION=0.01;
float kf=1.5;

byte flag_sw1=0;
byte flag_sw2=0;
 

Adafruit_NeoPixel track = Adafruit_NeoPixel(NPIXELS, PIN_LED, NEO_GRB + NEO_KHZ800);

int tdelay = 5; 

void setup() {
  track.begin(); 
  pinMode(PIN_P1,INPUT_PULLUP); 
  pinMode(PIN_P2,INPUT_PULLUP); 
}

void draw_p1(void){for(int i=0;i<=loop1;i++){track.setPixelColor(((word)dist1 % NPIXELS)+i, track.Color(0,255,0));};                    
                   //track.setPixelColor(((word)dist1 % NUMPIXELS)+1, track.Color(random(255),random(255),random(155)));   
  }

void draw_p2(void){for(int i=0;i<=loop2;i++){track.setPixelColor(((word)dist2 % NPIXELS)+i, track.Color(255,0,0));};            
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
    if (dist1>NPIXELS*loop1) {loop1++;};
    if (dist2>NPIXELS*loop2) {loop2++;};

    if (loop1>loop_max) {for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(0,255,0));}; track.show();
                                                      delay(5000);loop1=0;loop2=0;dist1=0;dist2=0;speed1=0;
                                                     }
    if (loop2>loop_max) {for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(255,0,0));}; track.show();
                                                      delay(5000);loop1=0;loop2=0;dist1=0;dist2=0;speed2=0;
                                                     }
    
    
    draw_p1();
    draw_p2();
    track.show(); 
    delay(tdelay); 
}
