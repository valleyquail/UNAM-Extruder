#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu_system.h"
#include "../include/pin_definitions.h"
#include "../lib/UART/skr_com.h"
#include "../lib/Stepper/Stepper.h"
#include "../lib/hall_effect/FilamentDiamSensor.h"


void setup() {
    Serial.begin(115200);
    for (int i = 0; i < 2000; i += 100) {
        delayMicroseconds(100000);
        Serial.print("starting in: ");
        Serial.println(i);
    }

    MenuSystem::initDisplay();
    // extruderMotor.setSpeed(100);
    Serial.println("initialized");
}

void loop() {
    MenuSystem::poll();
    checkForUpdate();

}
