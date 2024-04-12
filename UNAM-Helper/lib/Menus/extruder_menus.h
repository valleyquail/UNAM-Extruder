#ifndef EXTRUDER_MENUS_H
#define EXTRUDER_MENUS_H

#include <Arduino.h>
#include "menu.h"

class MenuNav
{
private:
    int NUM_COLS = 20;
    int NUM_ROWS = 4;

public:
    MenuNav();

    void initDisplay();
    void poll();
};

extern MenuNav menuNav;

#endif