#include <Arduino.h>
#include "skr_com.h"
#include "../Menus/menu_system.h"
#include "Stepper.h"

bool initSKRConnection() {
    Serial1.begin(115200);
    long time = millis();
    while (!Serial1) {
        if (millis() - time > 5000) {
            Serial.println("Took too long to connect to the skr");
            return false;
        }
    }
    return true;
}

void sendCommand(const String &command) {
    Serial1.println(command);
}

bool sendHallEffect(const float &reading) {
    if (Serial1.availableForWrite()) {


        String temp = String(MOTOR_SPEED) + String(reading);

        Serial1.print(temp);
        return true;
    }
    return false;
}

void parseString(const String &str) {
    char flag = str.charAt(0);
    switch (flag) {
        case MOTOR_SPEED: {
            Serial.print("Received a motor speed; speed is now: ");
            int raw_steps = str.substring(1).toInt();
            Serial.println(raw_steps);
            extruderMotor.setSpeed(raw_steps);
            break;
        }
        case TEMP:
            Serial.println("Received a temperature update");
            MenuSystem::updateDisplay("wagga wagga");
            break;
        case FLOW_RATE:
            Serial.println("Received a flowrate update");
            MenuSystem::updateDisplay("wagga wagga");
            break;
        default:
            Serial.println("oopsie doopsie");
            break;
    }
}

void checkForUpdate() {
    if (!Serial1.available()) {
        return;
    }
    String received = Serial1.readString();
    received.trim();
    parseString(received);
}


