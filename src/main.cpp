/*
File: main.cpp
Details:
    Entry-point to the micro-controller application.
*/

#include "controller.h"
#include "arduino.h"

// @note: example code to test using the C++ header/source files
Controller* c = nullptr; 

void setup() {
    c = new Controller();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    uint32_t delta = 1000;
    if (c->GetId() == 0x03) {
        delta = 100;
    }

    digitalWrite(LED_BUILTIN, HIGH);
    delay(delta);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delta);
}