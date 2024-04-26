//
// Created by nikesh on 4/17/24.
//

#ifndef UNAM_HELPER_FILAMENTDIAMSENSOR_H
#define UNAM_HELPER_FILAMENTDIAMSENSOR_H


#include <Arduino.h>



//Use two ADC pins to get an average value between the sensors since the rp2040 does not have accurate ADCs

//Calibration factor for the sensor
//This needs to be hardcoded since it will be specific to the output of the hall effect sensors
//This handles the scaling factor from the analog to the actual diameter


void initFilamentDiamSensor(int pin, int pin2);

float movingAverage(float *array, int n);

float getDiameter();

void calibrate();


#endif //UNAM_HELPER_FILAMENTDIAMSENSOR_H
