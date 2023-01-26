/*
File: main.cpp
Details:
    Entry-point to the micro-controller application.
*/

#include "controller.h"
#include "arduino.h"
#include "Keyboard/src/Keyboard.h"


const int UpButton = 5; 
const int DownButton = 4;
const int LeftButton = 3;
const int RightButton = 2;

Controller* c = nullptr; 

void setup() {
    c = new Controller();
    Serial.begin(9600);

    //Initialize pins
    pinMode(UpButton, INPUT);
    pinMode(DownButton, INPUT);
    pinMode(LeftButton, INPUT);
    pinMode(RightButton, INPUT);
    Keyboard.begin();
}

void loop() {

    if(digitalRead(UpButton) == HIGH){
        Keyboard.press('w');
        Keyboard.release('w');
        //delay(300);
    }
   if(digitalRead(DownButton) == HIGH){
        Keyboard.press('s');
        Keyboard.release('s');
	      //delay(300);
   }
   if(digitalRead(LeftButton) == HIGH){
        Keyboard.press('a');
        Keyboard.release('a');
	      //delay(300);
   }
   if(digitalRead(RightButton) == HIGH){
        Keyboard.press('d');
        Keyboard.release('d');
	      //delay(300);
   }
}