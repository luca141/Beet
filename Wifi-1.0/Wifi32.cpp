
#include "Arduino.h"
#include "WiFi32.h"
#include <WiFi.h>
#inlcude <string>



Wifi32::Wifi32(char ssid[], char password[])
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecring ro WiFi ..");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

string Wifi32::getMac()
{
    return WiFi.macAddress();
}