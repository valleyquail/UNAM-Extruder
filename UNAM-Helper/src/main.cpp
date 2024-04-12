#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include "extruder_menus.h"
#include "../include/pin_definitions.h"
#include "actions.h"

MenuNav menuNav = MenuNav();

void setup()
{
    Serial.begin(115200);
    for (int i = 0; i < 2000; i += 100)
    {
        delayMicroseconds(100000);
        Serial.print("starting in: ");
        Serial.println(i);
    }

    menuNav.initDisplay();

    initPins();
    Serial.println("initialized");
}

void loop()
{
    menuNav.poll();
}
