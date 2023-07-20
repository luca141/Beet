#include "Arduino.h"
#include "Moisture32.h"

int low2, high2, pin2;


Moisture32::Moisture32(int pin, int low, int high)
{
    pinMode(pin, INPUT);
    low2 = low;
    high2 = high;
    pin2 = pin;
}

double Moisture32::getMoisture(int value)
{
    if (value < low2)
        value = low2;
    else if (value > high2)
        value = high2;

    double percentage = 100.0 - ((value - low2) * 100.0) / (high2 - low2);
    return percentage;
}

