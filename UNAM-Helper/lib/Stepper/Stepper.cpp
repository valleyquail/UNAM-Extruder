//
// Created by nikesh on 4/17/24.
//

#include "Arduino.h"
#include "Stepper.h"
#include "../../include/pin_definitions.h"

#define MAX_STEP_RATE 20000
#define MICROSTEPPING 1
#define DUTY_CYLCE 25

Stepper extruderMotor = Stepper(STEPPER_DIR, STEPPER_PULSE);

Stepper::Stepper(int dir, int step) {
    this->dir = dir;
    this->step = step;
    // Initialize a stepper driver pwm output for sending steps in a non-blocking way
    // Max step rate is 20kHz because the duty cycle is 25% high
    this->pwm_driver = new RP2040_PWM(step, 0, DUTY_CYLCE);
    pinMode(dir, OUTPUT);
    pinMode(step, OUTPUT);
}

void Stepper::setSpeed(float rad_per_sec) {
    // Convert the rad per sec to steps per second
    float steps_per_sec = floor(rad_per_sec * 200.0 * MICROSTEPPING / PI);
    if (steps_per_sec > MAX_STEP_RATE) {
        steps_per_sec = MAX_STEP_RATE;
        Serial.println("Speed is too high, setting to max");
    }
    Serial.print("Setting speed to: ");
    Serial.println(steps_per_sec);
    if (steps_per_sec < 0) {
        digitalWrite(this->dir, HIGH);
    } else {
        digitalWrite(this->dir, LOW);
    }
    pwm_driver->setPWM(step, steps_per_sec, DUTY_CYLCE);
};

