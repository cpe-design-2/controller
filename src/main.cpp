/*
File: main.cpp
Details:
    Entry-point to the micro-controller application.
*/

#include "arduino.h"
#include "Keyboard/src/Keyboard.h"
#include "Mouse/src/Mouse.h"
#include "Joystick/Joystick.h"

bool KEYBOARD = true;

// D-PAD/KEYBOARD CONTROL
const int UP_BUTTON    = 5;   // W (up)         
const int DOWN_BUTTON  = 4;   // S (down)       
const int LEFT_BUTTON  = 3;   // A (left)
const int RIGHT_BUTTON = 2;   // D (right)  

// BUTTON/INTERACTION CONTROL
const int A_BUTTON = 6;          
const int B_BUTTON = 7;          
const int X_BUTTON = 8;          
const int Y_BUTTON = 9; 

// HOME/PAUSE BUTTONS
const int HOME_BUTTON  = 10;         
const int PAUSE_BUTTON = 16; 

// JOYSTICK 1/MOUSE CONTROL 
const int JS_1_BUTTON = 14;  // Push button
const int JS_1_X = A0;       // X-axis
const int JS_1_Y = A1;       // Y-axis

// JOYSTICK 2 CONTROL
const int JS_2_BUTTON = 15;  // Push button
const int JS_2_X = A2;       // X-axis
const int JS_2_Y = A3;       // Y-axis       

         
// GENERAL VARIABLES
const int DELAY = 10;
const int RANGE = 12;             // output range of X or Y movement
const int THRESHOLD = RANGE / 4;  // resting threshold
const int CENTER = RANGE / 2;     // resting position value
const int MULTIPLIER = 6;         // scalar to move mouse quicker

// Function to read X and Y axis for mouse control
int readAxis(int axis){

  int read = analogRead(axis); //read the current axis
  read = map(read, 0, 1023, 0, RANGE);
  
  int to_return = (read - CENTER) * MULTIPLIER;

  if(abs(to_return) < THRESHOLD){ //don't move mouse if mouse read is too small, prevents joycon drift
    to_return = 0;
  }
  
  return to_return;
}

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 0,                 // Button Count, Hat Switch Count
  true, true, true,      // X and Y, but no Z Axis
  true, true, true,      // Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  Serial.begin(9600);
  // if in JOYSTICK mode
  if (!KEYBOARD) { 
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
  } else {
    //Initialize pins
    pinMode(UP_BUTTON, INPUT);
    pinMode(DOWN_BUTTON, INPUT);
    pinMode(LEFT_BUTTON, INPUT);
    pinMode(RIGHT_BUTTON, INPUT);

    pinMode(A_BUTTON, INPUT); 
    pinMode(B_BUTTON, INPUT);
    pinMode(X_BUTTON, INPUT);
    pinMode(Y_BUTTON, INPUT);         

    pinMode(HOME_BUTTON, INPUT);
    pinMode(PAUSE_BUTTON, INPUT);

    pinMode(JS_1_BUTTON, INPUT_PULLUP);
    pinMode(JS_2_BUTTON, INPUT); 

    Keyboard.begin();
    Mouse.begin();
  }
}

void loop() { 
  if (!KEYBOARD) {
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
  // KEYBOARD CONFIGURATION
  } else {
    // Mouse Control:
    int x_move = readAxis(JS_1_X);
    int y_move = readAxis(JS_1_Y);

    Mouse.move(x_move, y_move, 0);  

    Serial.print(digitalRead(JS_1_BUTTON));
    
    if (digitalRead(JS_1_BUTTON) == HIGH && Mouse.isPressed(MOUSE_LEFT) == true) {
        Mouse.release(MOUSE_LEFT);
    } else if (digitalRead(JS_1_BUTTON) != HIGH && Mouse.isPressed(MOUSE_LEFT) == false) {
        Mouse.press(MOUSE_LEFT);
    }
    
    // WASD Control:
    if(digitalRead(UP_BUTTON) == HIGH){
      Keyboard.press('w');
      delay(DELAY);
    } else Keyboard.release('w');

    if(digitalRead(DOWN_BUTTON) == HIGH){
      Keyboard.press('s');
      delay(DELAY);
    } else Keyboard.release('s');

    if(digitalRead(LEFT_BUTTON) == HIGH){
      Keyboard.press('a');
      delay(DELAY);
    } else Keyboard.release('a');
    
    if(digitalRead(RIGHT_BUTTON) == HIGH){
      Keyboard.press('d');
      delay(DELAY);
    } else Keyboard.release('d');

    //spacebar control
    if(digitalRead(A_BUTTON) == HIGH){
      Keyboard.write((char) 32);
      delay(DELAY);
    }
    
    if(digitalRead(B_BUTTON) == HIGH){
      Keyboard.press('b');
      delay(DELAY);
    }

    if(digitalRead(X_BUTTON) == HIGH){
      Keyboard.press('x');
      delay(DELAY);
    }

    if(digitalRead(Y_BUTTON) == HIGH){
      Keyboard.press('Y');
      delay(DELAY);
    }

    if(digitalRead(HOME_BUTTON) == HIGH){
      Keyboard.press('h');
      delay(DELAY);
    }

    if(digitalRead(PAUSE_BUTTON) == HIGH){
      Keyboard.press('P');
      delay(DELAY);
    }

  }
}

