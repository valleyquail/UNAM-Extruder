#include <Arduino.h>


bool initSKRConnection();

void sendCommand(String command);

void parseString(String str, String *parsed);
