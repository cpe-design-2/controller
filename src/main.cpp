/*
File: main.cpp
Details:
    Entry-point to the micro-controller application.
*/

#include "controller.h"
#include "arduino.h"
//#include "Keyboard/src/Keyboard.h"
//#include "Mouse/src/Mouse.h"
#include "Joystick/Joystick.h"


// D-PAD CONTROL
const int UP_BUTTON = 5;          
const int DOWN_BUTTON = 4;          
const int LEFT_BUTTON = 3;          
const int RIGHT_BUTTON = 2;         

// TO DO: Determine which buttons will control these
// AB/XY CONTROL
const int A_BUTTON = 6;          
const int B_BUTTON = 7;          
const int X_BUTTON = 8;          
const int Y_BUTTON = 9;         

// TO DO: Determine which keyboard buttons will control these
// HOME/PAUSE BUTTONS
const int HOME_BUTTON = 10;         
const int PAUSE_BUTTON = 16;          

// JOYSTICK 1 CONTROL 
const int JS_1_BUTTON = 14;  // Push button
const int JS_1_X = A0;       // X-axis
const int JS_1_Y = A1;       // Y-axis

// JOYSTICK 2 CONTROL
const int JS_2_BUTTON = 15;  // Push button
const int JS_2_X = A2;       // X-axis
const int JS_2_Y = A3;       // Y-axis

// GENERAL VARIABLES
const int DELAY = 10;

Controller* c = nullptr; 

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 0,                 // Button Count, Hat Switch Count
  true, true, false,     // X, Y, and Z Axis
  true, true, false,     // Rx, Ry, and Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


void setup() {
    c = new Controller();
    Serial.begin(9600);
    
    /* Initialize pins */
    // D-PAD
    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);

    // AB/XY
    pinMode(A_BUTTON, INPUT_PULLUP);
    pinMode(B_BUTTON, INPUT_PULLUP);
    pinMode(X_BUTTON, INPUT_PULLUP);
    pinMode(Y_BUTTON, INPUT_PULLUP);

    // PAUSE and HOME
    pinMode(HOME_BUTTON, INPUT_PULLUP);
    pinMode(PAUSE_BUTTON, INPUT_PULLUP);

    // JOYSTICK 1 control
    pinMode(JS_1_BUTTON, INPUT_PULLUP);
    pinMode(JS_1_X, INPUT);
    pinMode(JS_1_Y, INPUT);

    // JOYSTICK 2 control
    pinMode(JS_2_BUTTON, INPUT_PULLUP); 
    pinMode(JS_2_X, INPUT);
    pinMode(JS_2_Y, INPUT);

    // Initialize the Joystick library
    Joystick.begin();
    Joystick.setXAxisRange(-1, 1);
    Joystick.setYAxisRange(-1, 1);
}

void loop() { 

  // Set the button states
  Joystick.setButton(0, digitalRead(UP_BUTTON));
  Joystick.setButton(1, digitalRead(DOWN_BUTTON));
  Joystick.setButton(2, digitalRead(LEFT_BUTTON));
  Joystick.setButton(3, digitalRead(RIGHT_BUTTON));

  Joystick.setButton(4, digitalRead(A_BUTTON));
  Joystick.setButton(5, digitalRead(B_BUTTON));
  Joystick.setButton(6, digitalRead(X_BUTTON));
  Joystick.setButton(7, digitalRead(Y_BUTTON));

  Joystick.setButton(8, digitalRead(HOME_BUTTON));
  Joystick.setButton(9, digitalRead(PAUSE_BUTTON));

  Joystick.setButton(10, !digitalRead(JS_1_BUTTON));
  Joystick.setButton(11, !digitalRead(JS_2_BUTTON));

  // Read the values from the joysticks
  int joystick_1_x = analogRead(JS_1_X);
  int joystick_1_y = analogRead(JS_1_Y);
  int joystick_2_x = analogRead(JS_2_X);
  int joystick_2_y = analogRead(JS_2_Y);

  // Convert the analog values
  int joystick_1_x_mapped = map(joystick_1_x, 0, 1023, -1, 1);
  int joystick_1_y_mapped = map(joystick_1_y, 0, 1023, -1, 1);
  int joystick_2_x_mapped = map(joystick_2_x, 0, 1023, -1, 1);
  int joystick_2_y_mapped = map(joystick_2_y, 0, 1023, -1, 1);


  // Set the values for the joystick object
  Joystick.setXAxis(joystick_1_x_mapped);
  Joystick.setYAxis(joystick_1_y_mapped);
  Joystick.setRxAxis(joystick_2_x_mapped);
  Joystick.setRyAxis(joystick_2_y_mapped);

  // Send the joystick values to the computer
  Joystick.sendState();

  // Wait for a short time before sending the next state
  delay(DELAY);
}

