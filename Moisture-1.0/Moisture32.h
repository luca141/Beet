#ifndef Moisture32_h
#define Moisture32_h

#include "Arduino.h"

class Moisture32
{
    public:
        Moisture32(int pin, int high, int low);
        double getMoisture(int value);
    
    private:

};


#endif