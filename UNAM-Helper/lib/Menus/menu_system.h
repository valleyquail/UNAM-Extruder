#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "extruder_menus.h"
#include "pultruder_menus.h"

enum FILAMENT_TYPES {
    PLA,
    PETG,
    ABS,
    HIPS,
    OTHER
};

/**
 * @brief Wrapper class for the menu items since it gets messy very quickly
 * This doesn't really need to exist, but it makes it a lot nicer for
 * programming since it wraps the macros and objects in a class
 *
 */
class MenuSystem {
private:
    void setFilamentType();

public:
    MenuSystem();

    FILAMENT_TYPES getFilamentType();

    static void initDisplay();

    static void poll();

    static void updateDisplay(String text);
};


#endif