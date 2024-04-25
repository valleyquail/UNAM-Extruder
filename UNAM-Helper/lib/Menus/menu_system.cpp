

#include <Arduino.h>
#include "menu_system.h"
#include "../../include/pin_definitions.h"
#include <LiquidCrystal_PCF8574.h> //library for I2C LCD
#include <menu.h>                  //menu macros and objects
#include <menuIO/keyIn.h>          //read keys from inputs

// some example libraries to handle the rotation and clicky part
// of the encoder. These will generate our events.
#include <qdec.h>      //https://github.com/SimpleHacks/QDEC
#include <AceButton.h> // https://github.com/bxparks/AceButton
#include <menuIO/rotaryEventIn.h>
#include "Wire.h"

// Initializers for the common menu system
//_________________________________________________________________________________

LiquidCrystal_PCF8574 lcd(LCD_ADDRESS); // set the LCD address to 0x27 for a 20 chars and 4 line display

using namespace Menu;
using namespace ::ace_button;
using namespace ::SimpleHacks;
QDecoder qdec(ENCODER_A_PIN, ENCODER_B_PIN, true); // rotary part
AceButton button(SELECT_BUTTON_PIN);               // button part

RotaryEventIn reIn(
        RotaryEventIn::EventType::BUTTON_CLICKED |        // select
        RotaryEventIn::EventType::BUTTON_DOUBLE_CLICKED | // back
        RotaryEventIn::EventType::BUTTON_LONG_PRESSED |   // also back
        RotaryEventIn::EventType::ROTARY_CCW |            // up
        RotaryEventIn::EventType::ROTARY_CW               // down
);

// This is the ISR (interrupt service routine) for rotary events
// We will convert/relay events to the RotaryEventIn object
// Callback config in setup()
void IsrForQDEC(void) {
    QDECODER_EVENT event = qdec.update();
    if (event & QDECODER_EVENT_CW) {
        reIn.registerEvent(RotaryEventIn::EventType::ROTARY_CW);
    } else if (event & QDECODER_EVENT_CCW) {
        reIn.registerEvent(RotaryEventIn::EventType::ROTARY_CCW);
    }
    Serial.println("ISR");
}

// This is the handler/callback for button events
// We will convert/relay events to the RotaryEventIn object
// Callback config in setup()
void handleButtonEvent(AceButton * /* button */, uint8_t eventType, uint8_t buttonState) {

    switch (eventType) {
        case AceButton::kEventClicked:
            reIn.registerEvent(RotaryEventIn::EventType::BUTTON_CLICKED);
            break;
        case AceButton::kEventDoubleClicked:
            reIn.registerEvent(RotaryEventIn::EventType::BUTTON_DOUBLE_CLICKED);
            break;
        case AceButton::kEventLongPressed:
            reIn.registerEvent(RotaryEventIn::EventType::BUTTON_LONG_PRESSED);
            break;
    }
}

serialIn serial(Serial);
menuIn *inputsList[] = {&reIn, &serial};
chainStream<2> in(inputsList); // 3 is the number of inputs

MENU_OUTPUTS(out, MAX_DEPTH, LCD_OUT(lcd, {0, 0, 20, 4}), SERIAL_OUT(Serial));

FILAMENT_TYPES filament_type = PLA;


CHOOSE(filament_type, chooseMenu, "Choose Filament Type", doNothing, noEvent, wrapStyle,
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

MENU(mainMenu, "Select Device", doNothing, anyEvent, wrapStyle, OP("Print", doNothing, enterEvent),
     SUBMENU(extrudeMenu),
     SUBMENU(pultrudeMenu));

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out);

// Menus
//_________________________________________________________________________________

MenuSystem::MenuSystem() = default;

void MenuSystem::initDisplay() {
    qdec.begin();
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), IsrForQDEC, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B_PIN), IsrForQDEC, CHANGE);

    // setup rotary button
    pinMode(SELECT_BUTTON_PIN, INPUT);
    ButtonConfig *buttonConfig = button.getButtonConfig();
    buttonConfig->setEventHandler(handleButtonEvent);
    buttonConfig->setFeature(ButtonConfig::kFeatureClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
    buttonConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);

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
    button.check(); // acebutton check, rotary is on ISR
    nav.poll();
}

void MenuSystem::updateDisplay(String text) {
}
