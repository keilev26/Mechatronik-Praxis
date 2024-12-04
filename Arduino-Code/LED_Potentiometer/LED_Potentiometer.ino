#define LED 3
#define POTI 0 //Analog pin the potentiometer is connected to 

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH); //switch LED off
}

void loop() {
  int potiVal = analogRead(POTI); //read the voltage at pin A0
  
  //Convert the measured value (0-1023) to a number between 20 and 1000
  int delayVal = map(potiVal,0,1023,20,1000); 
  digitalWrite(LED, !digitalRead(LED)); //Switch LED state
  delay(delayVal); //wait the amount of time that is set through the potentiometer
}
