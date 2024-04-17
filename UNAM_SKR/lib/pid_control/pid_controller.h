//
// Created by nikesh on 4/17/24.
//

#ifndef UNAM_SKR_EXTRUDER_PID_H
#define UNAM_SKR_EXTRUDER_PID_H

#include "../../include/pin_definitions.h"

class PIDController{

private:
    void loadFromEEPROM();
    void saveToEEPROM();
    float kp;
    float ki;
    float kd;

    float setpoint;


public:
    PIDController();
    /**
     * @brief Initialize the PID controller
     * @param isPultruder if true, loads the pulltruder PID values, else loads the extruder PID values
     */
    void init(bool isPultruder);
    void setSetpoint(float setpoint);
    void runCalibration();

};


#endif //UNAM_SKR_EXTRUDER_PID_H
