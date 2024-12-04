#define LED 3
#define BUTTON 2

int button_state = LOW; //Contains the current state the button is in
boolean reset = true; //True - Button has been released before that press

//old_time - time when the button was pushed last
//debounce_time - time, the button has to be pushed continuously 
unsigned long old_time = 0, debounce_time = 20;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  //Interrupt routine "interruptRoutine" is to be executed if
  //interrupt at pin D2 (0 denotes the interrupt vector for D2)
  //is triggered
  //Change -> react to changes in the button state
  attachInterrupt(0, interruptRoutine, CHANGE);
}

void loop() {
  //loop() function is empty here, but can contain a lot of code if necessary
}

void interruptRoutine() { //void -> function has no return
  
  //Debounce by comparing last time this method has been executed 
  //(by a change in the button state) with the current system time. 
  //More than the debvounce time (here 20ms) has to pass for the function
  //to continue 
  
  if ((millis() - old_time) > debounce_time){
    button_state = digitalRead(BUTTON); //Read the button state
    
    //Change the LED state only if the button has been released before
    if ((reset)&(button_state==HIGH)){ //Button is currently pressed and has been released before
      reset = false; 
      digitalWrite(LED, !digitalRead(LED)); //change LED state
    }
    else{
        reset = true;  //Set the reset to true, as the button has been released
    }
    old_time = millis(); //Save the current time to debounce the next push
  }
  
}
  
