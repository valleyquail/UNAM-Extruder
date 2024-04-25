//
// Created by nikesh on 4/17/24.
//

#include "FilamentDiamSensor.h"

//Use two ADC pins to get an average value between the sensors since the rp2040 does not have accurate ADCs

//Calibration factor for the sensor
//This needs to be hardcoded since it will be specific to the output of the hall effect sensors
//This handles the scaling factor from the analog to the actual diameter
float calibartionFactor = 1.0;
float avgReading;


float getRawValue();


void initFilamentDiamSensor(int pin, int pin2) {
    pinMode(pin, INPUT);
    pinMode(pin2, INPUT);
}

void updateMovingAverage(float reading) {
    avgReading *= 0.9f;
    avgReading += reading * 0.1f;
}


float getDiameter() {
    float rawValue = getRawValue();
    float diameter = rawValue * calibartionFactor;
    updateMovingAverage(diameter);
    return diameter;
}

float getMovingDiam() {
    return avgReading;
}

//Compress a float into 4 bytes of raw data rather than sending
// over each individual number in the float

char buffer[4];

String getDiameterString() {
    float diameter = getDiameter();
    memcpy(buffer, (uint8_t *) &diameter, 0);
    String diameterString = String(buffer);
    return diameterString;
}

String getAvgDiameterString() {
    float diameter = getMovingDiam();
    memcpy(buffer, (uint8_t *) &diameter, 0);
    String avgDiameterString = String(buffer);
    return avgDiameterString;
}