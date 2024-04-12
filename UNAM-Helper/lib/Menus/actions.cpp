#include "actions.h"
#include "../../include/pin_definitions.h"

void initPins()
{
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);
    pinMode(LEFT_PIN, INPUT);
    pinMode(RIGHT_PIN, INPUT);
    pinMode(SELECT_PIN, INPUT);
}

void printPins()
{
    if (digitalRead(UP_PIN) == HIGH)
    {
        Serial.println("UP_PIN is HIGH");
    }
    if (digitalRead(DOWN_PIN) == HIGH)
    {
        Serial.println("DOWN_PIN is HIGH");
    }
    if (digitalRead(LEFT_PIN) == HIGH)
    {
        Serial.println("LEFT_PIN is HIGH");
    }
    if (digitalRead(RIGHT_PIN) == HIGH)
    {
        Serial.println("RIGHT_PIN is HIGH");
    }
    if (digitalRead(SELECT_PIN) == HIGH)
    {
        Serial.println("SELECT_PIN is HIGH");
    }
}