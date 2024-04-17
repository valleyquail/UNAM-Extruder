#include "skr_com.h"

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

void sendCommand(String command) {
    Serial1.println(command);
}


void parseString(String str, String *parsed) {
    int i = 0;
    int j = 0;
    while (i < str.length()) {
        if (str[i] == ' ') {
            i++;
            j++;
        } else {
            parsed[j] += str[i];
            i++;
        }
    }
}