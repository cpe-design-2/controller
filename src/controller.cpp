#include "controller.h"

Controller::Controller() {
    this->id = IDENTIFICATION_NUMBER;
}

uint8_t Controller::GetId() {
    return this->id;
}