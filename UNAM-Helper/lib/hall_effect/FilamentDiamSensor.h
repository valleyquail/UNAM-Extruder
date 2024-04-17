//
// Created by nikesh on 4/17/24.
//

#ifndef UNAM_HELPER_FILAMENTDIAMSENSOR_H
#define UNAM_HELPER_FILAMENTDIAMSENSOR_H


#include <Arduino.h>


class FilamentDiamSensor {


private:
    //Use two ADC pins to get an average value between the sensors since the rp2040 does not have accurate ADCs
    int adc1;
    int adc2;

    //Calibration factor for the sensor
    //This needs to be hardcoded since it will be specific to the output of the hall effect sensors
    //This handles the scaling factor from the analog to the actual diameter
    float calibartionFactor = 1.0;
    float getRawValue();
    float movingAverage(float *array, int n);
    float filamentWindingSpeed = 0.0;
public:
    FilamentDiamSensor(int pin, int pin2);
    void setFilamentWindingSpeed(float speed);
    float getDiameter();
    String getDiameterString();
};


#endif //UNAM_HELPER_FILAMENTDIAMSENSOR_H
