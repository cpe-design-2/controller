/*
File: main.cpp
Details:
    Entry-point to the micro-controller application.
*/

#include "arduino.h"

#define GAMEPAD_EN 0

#ifdef GAMEPAD_EN
  #include "Joystick/Joystick.h"
#else
  #include "Keyboard/src/Keyboard.h"
  #include "Mouse/src/Mouse.h"
#endif

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
const int JS_1_X = A1;       // X-axis
const int JS_1_Y = A0;       // Y-axis

#ifdef GAMEPAD_EN
  // JOYSTICK 2 CONTROL (UNMAPPED WHEN NOT USING GAMEPAD)
  const int JS_2_BUTTON = 15;  // Push button
  const int JS_2_X = A2;       // X-axis
  const int JS_2_Y = A3;       // Y-axis
#endif        

         
// GENERAL VARIABLES
#ifdef GAMEPAD_EN
  const int DELAY = 10;
#else
  // GENERAL VARIABLES
  const int DELAY = 190;
#endif


#ifdef GAMEPAD_EN

#else
  const int RANGE = 12;             // output range of X or Y movement
  const int THRESHOLD = RANGE / 4;  // resting threshold
  const int CENTER = RANGE / 2;     // resting position value

  // Function to read X and Y axis for mouse control
  int readAxis(int axis){

    int read = analogRead(axis); //read the current axis
    read = map(read, 0, 1023, 0, RANGE);
    
    int to_return = read - CENTER;

    if(abs(to_return) < THRESHOLD){ //don't move mouse if mouse read is too small, prevents joycon drift
      to_return = 0;
    }
    
    return to_return;
  }
#endif

#ifdef GAMEPAD_EN
  Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
    12, 0,                 // Button Count, Hat Switch Count
    true, true, true,      // X and Y, but no Z Axis
    true, true, true,      // Rx, Ry, or Rz
    false, false,          // No rudder or throttle
    false, false, false);  // No accelerator, brake, or steering
#else
 
#endif

void setup() {
    Serial.begin(9600);
    
    #ifdef GAMEPAD_EN
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
    #else
      //Initialize pins
      pinMode(UP_BUTTON, INPUT);
      pinMode(DOWN_BUTTON, INPUT);
      pinMode(LEFT_BUTTON, INPUT);
      pinMode(RIGHT_BUTTON, INPUT);

      Keyboard.begin();
      Mouse.begin();
    #endif

}

void loop() { 
  #ifdef GAMEPAD_EN
    delay(DELAY);
  #else
    // Mouse Control:
    int x_move = readAxis(JS_1_X);
    int y_move = readAxis(JS_1_Y);

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

    //A1 / spacebar control
    if(digitalRead(A_BUTTON) == HIGH){
      Keyboard.write((char) 32);
      delay(DELAY);
    }
  #endif
}

