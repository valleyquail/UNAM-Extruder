#include "Arduino.h"
#include "extruder_menus.h"
#include "../../include/pin_definitions.h"
#include "Wire.h"

#include <menu.h>                  //menu macros and objects
#include <menuIO/PCF8574Out.h>     //arduino I2C LCD
#include <menuIO/chainStream.h>    // concatenate multiple input streams (this allows adding a button to the encoder)
#include <LiquidCrystal_PCF8574.h> //library for I2C LCD
#include <menuIO/keyIn.h>          //read keys from inputs
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>

#define MAX_DEPTH 2

LiquidCrystal_PCF8574 lcd(LCD_ADDRESS); // set the LCD address to 0x27 for a 20 chars and 4 line display
using namespace Menu;

result showEvent(eventMask e)
{
    Serial.print("event: ");
    Serial.println(e);
    return proceed;
}

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

void testAction(eventMask e, navNode &nav, prompt &item, menuIn &in)
{
    Serial.println("Test Action");
}
serialIn serial(Serial);
menuIn *inputsList[] = {&joystickBtns, &serial};
chainStream<2> in(inputsList); // 3 is the number of inputs

MENU_OUTPUTS(out, MAX_DEPTH, LCD_OUT(lcd, {0, 0, 20, 4}), SERIAL_OUT(Serial));

int test = 5;

MENU(subMenu, "Sub-Menu", doNothing, anyEvent, wrapStyle,
     OP("Sub1", showEvent, enterEvent),
     OP("Sub2", showEvent, enterEvent),
     OP("Sub3", showEvent, enterEvent),
     EXIT("<Back"));

MENU(mainMenu, "Main menu", doNothing, anyEvent, wrapStyle, OP("Print", testAction, enterEvent),
     OP("Actions test", testAction, enterEvent),
     SUBMENU(subMenu),
     FIELD(test, "Test", "%", 0, 100, 10, 1, doNothing, noEvent, wrapStyle));

NAVROOT(nav, mainMenu, 2, in, out);

MenuNav::MenuNav()
{
}

void MenuNav::initDisplay()
{
    joystickBtns.begin();
    Wire.setSDA(SDA_PIN);
    Wire.setSCL(SCL_PIN);
    Wire.begin();
    Wire.beginTransmission(LCD_ADDRESS);
    int error = Wire.endTransmission();
    if (error == 0)
    {
        Serial.println("I2C LCD found");
    }
    else
    {
        Serial.println("I2C LCD not found");
    }
    lcd.begin(20, 4); // initialize the lcd
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.setCursor(0, 0);
    // lcd.print("Extruder Menu");
    // lcd.setCursor(0, 1);
    // lcd.print("Version 1.0");
}

void MenuNav::poll()
{
    nav.poll();
}