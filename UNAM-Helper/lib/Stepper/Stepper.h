//
// Created by nikesh on 4/17/24.
//

#ifndef UNAM_HELPER_STEPPER_H
#define UNAM_HELPER_STEPPER_H

#include "RP2040_PWM.h"

/**
 * This does not need to be a class but we ball
 */

class Stepper {

private:
    RP2040_PWM *pwm_driver;

    int dir;
    int step;


public:
    Stepper(int dir, int step);

    void setSpeed(float speed);

};

extern Stepper extruderMotor;

#endif //UNAM_HELPER_STEPPER_H
