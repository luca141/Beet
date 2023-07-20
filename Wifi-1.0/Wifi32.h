
#ifndef Wifi32_h
#define Wifi32_h

#include "Arduino.h"
#include <string>

class Wifi32
{
    public:
        Wifi32(char ssid[], char password[]);
        string getMac();

};

#endif