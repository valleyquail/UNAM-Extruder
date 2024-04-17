#ifndef PULTRUDER_MENUS_H
#define PULTRUDER_MENUS_H

#include <Arduino.h>
#include <menu.h>                  //menu macros and objects
#include <menuIO/PCF8574Out.h>     //arduino I2C LCD
#include <menuIO/chainStream.h>    // concatenate multiple input streams (this allows adding a button to the encoder)
#include <LiquidCrystal_PCF8574.h> //library for I2C LCD
#include <menuIO/keyIn.h>          //read keys from inputs
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>
#include "../../include/pin_definitions.h"

#endif