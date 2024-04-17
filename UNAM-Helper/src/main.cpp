#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu_system.h"
#include "../include/pin_definitions.h"

MenuSystem menuSys = MenuSystem();

void setup()
{
    Serial.begin(115200);
    for (int i = 0; i < 2000; i += 100)
    {
        delayMicroseconds(100000);
        Serial.print("starting in: ");
        Serial.println(i);
    }

    menuSys.initDisplay();

    Serial.println("initialized");
}

void loop()
{
    menuSys.poll();
}
