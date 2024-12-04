#define LED 3
#define BUTTON 2

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP); //Set D2 to input with internal pull-up

}

void loop() {
  int buttonState = digitalRead(BUTTON); //Read the current button                   //state
  digitalWrite(LED, !buttonState); //Switch LED accordingly
}
