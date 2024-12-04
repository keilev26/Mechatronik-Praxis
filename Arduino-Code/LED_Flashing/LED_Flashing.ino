//Constants
#define LED 3 //The digital pin that the LED is 
              //connected to

//Global variables
boolean LED_state; //Current LED state (HIGH/LOW)

void setup() {
 pinMode(LED,OUTPUT); //Set digital pin with LED to OUTPUT
                      //results in a low-impedance state
 LED_state = HIGH; //LED pin should be set to HIGH initially
}

void loop() {
  digitalWrite(LED, LED_state); //Set the LED pin to the current  
                                //state saved in LED_state
  LED_state = !LED_state; //Change the value in LED_state to its 
                          //opposing state, i.e. from HIGH to LOW or
                          //from LOW to HIGH, respectively
  delay(200); //Wait 200ms
}
