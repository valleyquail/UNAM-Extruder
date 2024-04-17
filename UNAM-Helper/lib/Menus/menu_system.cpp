

#include <Arduino.h>
#include "menu_system.h"
#include "../../include/pin_definitions.h"
#include <LiquidCrystal_PCF8574.h> //library for I2C LCD
#include <menu.h>         //menu macros and objects
#include <menuIO/keyIn.h> //read keys from inputs
#include "Wire.h"

// Initializers for the common menu system
//_________________________________________________________________________________

LiquidCrystal_PCF8574 lcd(LCD_ADDRESS); // set the LCD address to 0x27 for a 20 chars and 4 line display

using namespace Menu;

// Control system for the menus when using limit switches for guidance
//  this will be changed to encoder input
//  TODO: get the encoder working when it arrives

keyMap joystickBtn_map[] = {
    {
        UP_PIN,
        defaultNavCodes[upCmd].ch,
    },
    {
        DOWN_PIN,
        defaultNavCodes[downCmd].ch,
    },
    {
        LEFT_PIN,
        defaultNavCodes[leftCmd].ch,
    },
    {
        RIGHT_PIN,
        defaultNavCodes[rightCmd].ch,
    },
    {
        SELECT_PIN,
        defaultNavCodes[enterCmd].ch,
    },

};
keyIn<5> joystickBtns(joystickBtn_map);

serialIn serial(Serial);
menuIn *inputsList[] = {&joystickBtns, &serial};
chainStream<2> in(inputsList); // 3 is the number of inputs

MENU_OUTPUTS(out, MAX_DEPTH, LCD_OUT(lcd, {0, 0, 20, 4}), SERIAL_OUT(Serial));

FILAMENT_TYPES filament_type = PLA;

CHOOSE(filament_type, chooseMenu, "Choose Filament Type", doNothing, noEvent, wrapStyle,
       VALUE("PLA", PLA, doNothing, noEvent),
       VALUE("PETG", PETG, doNothing, noEvent),
       VALUE("ABS", ABS, doNothing, noEvent),
       VALUE("HIPS", HIPS, doNothing, noEvent),
       VALUE("Other", OTHER, doNothing, noEvent));

MENU(extrudeMenu, "Extruder", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(chooseMenu));

MENU(pultrudeMenu, "Pultruder", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(chooseMenu));

MENU(mainMenu, "Select Device", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(extrudeMenu),
     SUBMENU(pultrudeMenu));

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out);

// Menus
//_________________________________________________________________________________

MenuSystem::MenuSystem()
{
}

void MenuSystem::initDisplay()
{
    joystickBtns.begin();
    Wire.setSDA(SDA_PIN);
    Wire.setSCL(SCL_PIN);
    Wire.begin();
    Wire.beginTransmission(LCD_ADDRESS);
    int error = Wire.endTransmission();
    if (error == 0)
        Serial.println("I2C LCD found");
    else
        Serial.println("I2C LCD not found");
    lcd.begin(20, 4); // initialize the lcd
}

// Get the selected filament type from the menu
FILAMENT_TYPES MenuSystem::getFilamentType()
{
    return filament_type;
}

void MenuSystem::poll()
{
    nav.poll();
}

