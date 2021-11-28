#include "Arduino.h"
#include "Led.h"

Led::Led(int digitalPin) {
    _digitalPin = digitalPin; 
    pinMode(digitalPin, OUTPUT); 
    digitalWrite(digitalPin, LOW); 
}

void Led::setStatus(boolean status) {
    digitalWrite(_digitalPin, status); 
}