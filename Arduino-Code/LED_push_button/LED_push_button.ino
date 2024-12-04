#define LED 3
#define BUTTON 2

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT); //Define pin D2 as an input -> high impedance

}

void loop() {
  int buttonState = digitalRead(BUTTON); //Read the current button state
  digitalWrite(LED, buttonState); //Switch LED accordingly
}
