#include "Arduino.h"
#include "extruder_menus.h"
#include "../../include/pin_definitions.h"
#include "Wire.h"

// Fields/values that control the menu navigation and display
//_________________________________________________________________________________________________________

int test;
int temp;

//_________________________________________________________________________________________________________

// Actions
//_________________________________________________________________________________
result showEvent(eventMask e)
{
    Serial.print("event: ");
    Serial.println(e);
    return proceed;
}

// Menus
//_________________________________________________________________________________

MENU(extruderDisplay, "Extruder Display", doNothing, noEvent, wrapStyle,
     OP("Extrude", doNothing, enterEvent),
     OP("Retract", doNothing, enterEvent),
     OP("Change Filament", doNothing, enterEvent),
     OP("Settings", doNothing, enterEvent),
     EXIT("<Back"));