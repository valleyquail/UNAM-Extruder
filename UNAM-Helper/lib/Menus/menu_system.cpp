

#include <Arduino.h>
#include "menu_system.h"
#include "../../include/pin_definitions.h"
#include <LiquidCrystal_PCF8574.h> //library for I2C LCD
#include <menu.h>                  //menu macros and objects
#include <menuIO/keyIn.h>          //read keys from inputs
#include "RPi_Pico_TimerInterrupt.h"
#include "../ClickEncoder/ClickEncoder.h"
#include <menuIO/clickEncoderIn.h>
#include "Wire.h"

// Initializers for the common menu system
//_________________________________________________________________________________

LiquidCrystal_PCF8574 lcd(LCD_ADDRESS); // set the LCD address to 0x27 for a 20 chars and 4 line display

using namespace Menu;

#define POLL_PERIOD 1000
RPI_PICO_Timer ITimer0(0);


ClickEncoder clickEncoder(ENCODER_A_PIN, ENCODER_B_PIN, SELECT_BUTTON_PIN, 4);
ClickEncoderStream encStream(clickEncoder, 1);

MENU_INPUTS(in, &encStream);

bool TimerISR(struct repeating_timer *t) {
    (void) t;

    clickEncoder.service();
    return true;
}


MENU_OUTPUTS(out, MAX_DEPTH, LCD_OUT(lcd, {0, 0, 20, 4}), SERIAL_OUT(Serial));

FILAMENT_TYPES filament_type = PLA;


CHOOSE(filament_type, chooseMenu, "Plastic Type:", doNothing, enterEvent, wrapStyle,
       VALUE("PLA", PLA, doNothing, noEvent),
       VALUE("PETG", PETG, doNothing, noEvent),
       VALUE("ABS", ABS, doNothing, noEvent),
       VALUE("HIPS", HIPS, doNothing, noEvent),
       VALUE("Other", OTHER, doNothing, noEvent));


MENU(statsMenu, "Stats", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(chooseMenu));

MENU(extrudeMenu, "Extruder", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(chooseMenu));

MENU(pultrudeMenu, "Pultruder", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(chooseMenu));

MENU(mainMenu, "Select Device", doNothing, anyEvent, wrapStyle,
     SUBMENU(extrudeMenu),
     SUBMENU(pultrudeMenu));

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out);

// Menus
//_________________________________________________________________________________

MenuSystem::MenuSystem() = default;

void MenuSystem::initDisplay() {
    pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
    ITimer0.attachInterruptInterval(POLL_PERIOD, TimerISR);
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
    lcd.setBacklight(200);
}

// Get the selected filament type from the menu
FILAMENT_TYPES MenuSystem::getFilamentType() {
    return filament_type;
}

void MenuSystem::poll() {

    nav.poll();
}

void MenuSystem::updateDisplay(String text) {
}
