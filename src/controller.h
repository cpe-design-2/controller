#pragma once
#include <stdint.h>

#define IDENTIFICATION_NUMBER 0x03

class Controller {
    private:
        uint8_t id;

    public:
        Controller();

        uint8_t GetId();
};