/*
File: main.cpp
Details:
    Entry-point to the micro-controller application.
*/

#include "controller.h"
#include "arduino.h"
#include "Keyboard/src/Keyboard.h"
#include "Mouse/src/Mouse.h"
#include "Joystick/Joystick.h"


// WASD CONTROL
const int W_Button = 5;          //W
const int S_Button = 4;          //S
const int A_Button = 3;          //A
const int D_Button = 2;          //D

// TO DO: Determine which buttons will control these
// AB/XY CONTROL
const int A1_Button = 6;          //
const int B_Button = 7;          //
const int X_Button = 8;          //
const int Y_Button = 9;          //

// TO DO: Determine which keyboard buttons will control these
// HOME/PAUSE BUTTONS
const int Home_Button = 10;          //
const int Pause_Button = 16;          //

// JOYSTICK 1 CONTROL (MOUSE)
const int JS_1_Button = 14;  // Push button
const int JS_1_X = A0;       // X-axis
const int JS_1_Y = A1;       // Y-axis

const int Range = 12;             // output range of X or Y movement
const int Delay = 5;              // response delay of the mouse, in ms
const int Threshold = Range / 4;  // resting threshold
const int Center = Range / 2;     // resting position value

// JOYSTICK 2 CONTROL
const int JS_2_Button = 15;  // Push button
const int JS_2_X = A2;       // X-axis
const int JS_2_Y = A3;       // Y-axis

// GENERAL VARIABLES
const int DELAY = 190;

Controller* c = nullptr; 

// Function to read X and Y axis for mouse control
int readAxis(int axis){

  int read = analogRead(axis); //read the current axis
  read = map(read, 0, 1023, 0, Range);
  
  int to_return = read - Center;

  if(abs(to_return) < Threshold){ //don't move mouse if mouse read is too small, prevents joycon drift
    to_return = 0;
  }
  
  return to_return;
}

void setup() {
    c = new Controller();
    Serial.begin(9600);
    
    //Initialize pins
    pinMode(W_Button, INPUT);
    pinMode(S_Button, INPUT);
    pinMode(A_Button, INPUT);
    pinMode(D_Button, INPUT);

    Keyboard.begin();
    Mouse.begin();
}

void loop() {
    // Mouse Control:
    int x_move = readAxis(A1);
    int y_move = readAxis(A0);

    Mouse.move(-x_move, y_move, 0);  

    
    if (digitalRead(JS_1_Button) != HIGH) {
    // if the mouse is not pressed, press it:
      if (!Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.press(MOUSE_LEFT);
        delay(DELAY);
      }
    }
    // else the mouse button is not pressed:
    else {
      // if the mouse is pressed, release it:
      if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT);
        delay(DELAY);
      }
    }
    
    
    // WASD Control:
    if(digitalRead(W_Button) == HIGH){
      Keyboard.press('w');
      delay(DELAY);
    } else Keyboard.release('w');

    if(digitalRead(S_Button) == HIGH){
      Keyboard.press('s');
      delay(DELAY);
    } else Keyboard.release('s');

    if(digitalRead(A_Button) == HIGH){
      Keyboard.press('a');
      delay(DELAY);
    } else Keyboard.release('a');
   
   if(digitalRead(D_Button) == HIGH){
      Keyboard.press('d');
      delay(DELAY);
   } else Keyboard.release('d');

   //A1 / spacebar control
   if(digitalRead(A1_Button) == HIGH){
      Keyboard.write((char) 32);
      delay(DELAY);
    }
}

