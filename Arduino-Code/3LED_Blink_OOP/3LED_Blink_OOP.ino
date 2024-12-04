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

//Create three LED objects
LED led1(2,400);
LED led2(3,750);
LED led3(1,200);

void setup() {    
}

void loop()
{
  led1.blinking();
  led2.blinking();
  led3.blinking();
}
