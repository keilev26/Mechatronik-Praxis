#define LED1 2 //LED1 Pin
#define LED2 3 //LED2 Pin

long previousMillis1 = 0;  //System time when LED 1 was last switched
long previousMillis2 = 0;  //System time when LED 2 was last switched

long interval1 = 400;  //Switching interval for LED1 [ms]
long interval2 = 750;  //Switching interval for LED2 [ms]

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);      
}

void loop()
{

  //Retrieve current system time
  unsigned long currentMillis = millis();

  //Check timing for LED1
  if(currentMillis - previousMillis1 > interval1) {
    
    //Store current system time for next interval 
    previousMillis1 = currentMillis;   

    //Switch LED
    digitalWrite(LED1, !digitalRead(LED1));
  }

  //Check timing for LED2
  if(currentMillis - previousMillis2 > interval2) {
    
    //Store current system time for next interval 
    previousMillis2 = currentMillis;   

    //Switch LED
    digitalWrite(LED2, !digitalRead(LED2));
  }
}
