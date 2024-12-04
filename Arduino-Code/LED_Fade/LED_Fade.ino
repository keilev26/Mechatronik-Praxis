#define LED 3 

void setup() {
 pinMode(LED,OUTPUT); 
}

void loop() {
  //Slowly light up LED
  //for-loop that increases i from 0 to 254 in steps of 1.
  //PWM outputs supports 255 voltage steps.
  for (int i = 0; i<255; i++){
    analogWrite(LED, i); //current voltage is 5V*i/255
    delay(20); //wait for 20ms
  }

  //Slowly shade the LED
  //for-loop that decreases i from 255 to 1 in steps of 1
  for (int i = 255; i>0; i--){
    analogWrite(LED, i); 
    delay(20); 
  }
  
}
