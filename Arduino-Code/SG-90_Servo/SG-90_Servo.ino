#include <Servo.h> //Make sure to install the Servo.h library first
Servo myServo;     //Create a new Servo object

void setup() {
  myServo.attach(9);  //Initialize servo and set connection to pin D9
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 45){
      myServo.write(angle); //Set the servo to the desired angle
      delay(500); //Wait 500ms to give the servo sufficient time to move 
                  //to the desired angle
    }
}
