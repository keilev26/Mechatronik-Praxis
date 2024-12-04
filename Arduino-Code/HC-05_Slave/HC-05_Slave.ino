#include <SoftwareSerial.h>
#define LED 3

#define BTRX 4 //-> connect to HC-05 TX pin
#define BTTX 5 //-> connect to HC-05 RX pin
SoftwareSerial SerialBT(BTRX, BTTX); //create new SoftwareSerial object


void setup() {  
  Serial.begin(9600);    // Start serial communication at 9600 Baud (serial monitor)
  SerialBT.begin(9600);  // Start serial communication at 9600 Baud (HC-05)
  digitalWrite(LED,LOW); // Initialize LED pin to LOW
  pinMode(LED,OUTPUT);
}

void loop() {  
  char c;
  // Check for pending serial data
  if (SerialBT.available()) {
    c = SerialBT.read(); // Read data and save it in variable c
    switch(c){ // check value in c
      case 'b': // if value is f, switch off LED
      digitalWrite(LED,LOW);
      break;
      
      case 'B': // if value is t, switch on LED
      digitalWrite(LED,HIGH);
      break;
      } 
  }
}
