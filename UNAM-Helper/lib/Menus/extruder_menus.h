
#ifndef EXTRUDER_MENUS_H
#define EXTRUDER_MENUS_H

#include <Arduino.h>
#include <menu.h>                  //menu macros and objects
#include <menuIO/PCF8574Out.h>     //arduino I2C LCD
#include <menuIO/chainStream.h>    // concatenate multiple input streams (this allows adding a button to the encoder)
#include <menuIO/keyIn.h>          //read keys from inputs
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>

#define MAX_DEPTH 5
#define SOFT_DEBOUNCE_MS 100

extern Menu::menu extruderDisplay;
extern Menu::menu extruderSettings;
extern Menu::menu extruderCalibration;
extern Menu::menu extruderFilament;

#endif