#include <Arduino.h>
#include "../lib/pid_control/pid_controller.h"
#include "../lib/steppers/stepper_control.h"
#include "../lib/pico_uart/pico_uart.h"

PIDController pultruderPID = PIDController();
PIDController extruderPID = PIDController();
StepperController pultruderStepper = StepperController();
StepperController extruderStepper = StepperController();


void setup() {

}

void loop() {

}
