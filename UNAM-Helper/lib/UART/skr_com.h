#include <Arduino.h>

enum MESSAGE_FLAGS {
    HALL_EFFECT = 'H',
    MOTOR_SPEED = 'M',
    TEMP = 'T',
    FLOW_RATE = 'F',
};


struct DeviceData {
    float temperature;
    float flowRate;
    float motorSpeed;
    float hallEffect;
};

bool initSKRConnection();

void sendCommand(const String &command);

bool sendHallEffect(const float &reading);

void checkForUpdate();
