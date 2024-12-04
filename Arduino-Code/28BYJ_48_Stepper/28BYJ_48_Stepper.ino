#include <Stepper.h>

Stepper myStepper(32, 10, 12, 11, 13);
int steps = 2038; //steps per revolution in clockwise direction

void setup() {
  myStepper.setSpeed(1000); //Set speed
}

void loop() {
  myStepper.step(steps); //Run the number of steps defined in "steps"
  steps = steps*-1; //Switch direction of rotation
}
