#include <Servo.h>

class LED //The LED class
{
  //Member variables
  int pin; //The pin, the LED is connected to
  long interval; //The switching interval
  unsigned long previousMillis; //The system time at which the LED was last switched.

//The constructor
public:
LED(int pinP,long intervalP){ //The required parameters to create a  
                              //new object of class LED

  //Allocation and initialization of variables
  pin = pinP;
  interval = intervalP;
  pinMode(pin,OUTPUT);
  previousMillis = 0;
  }

//The method to check if enough time has passed for switching the LED
void blinking()  {
    unsigned long currentMillis = millis();
     
    if(currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      digitalWrite(pin, !digitalRead(pin));  
    }   
  }
  
};

class Servomotor //The servomotor class
{
  Servo servo; //an object of class servo through which the servo is adressed
  
  int pin; //pin to which servo is connected
  int pos; //current servo position
  int angleIncrement; //angle by which servo should move with each increment
  int interval; //time interval for every servo increment
  unsigned long previousMillis;

public:
Servomotor(int pinP, int intervalP, int angleIncrementP){
  pin = pinP;
  interval = intervalP;
  angleIncrement = angleIncrementP;
  }
  
void initialize(){ //Method to initialize the servomotor object
                   //has to be called in the setup() method
  servo.attach(pin);
}

void moveServo(){
    unsigned long currentMillis = millis();
     
    if(currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      pos += angleIncrement; //Increment servo posiiton by defined angle increment

      if (pos >= 180){ //If end position is reached
        pos = 180;
        angleIncrement = -angleIncrement; //change direction of motion
      }
      else if (pos <= 0){ //If counter-clockwise end position is reached
        pos = 0;
        angleIncrement = -angleIncrement; //change direction of motion
      }
      servo.write(pos); //Move servo to new position
    }
  }  
};

//Create three LED objects
LED led1(2,400);
LED led2(3,750);
LED led3(1,200);

//Create two servomotor objects
Servomotor s1(5,15,1);
Servomotor s2(6,350,15);

void setup() {    
s1.initialize();
s2.initialize();
}

void loop()
{
  led1.blinking();
  led2.blinking();
  led3.blinking();

  s1.moveServo();
  s2.moveServo();
}
