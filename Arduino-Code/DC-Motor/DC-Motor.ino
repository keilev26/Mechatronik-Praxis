#define DCMOTOR 6 //Pin that is connected to transitor base
 
void setup() 
{ 
  pinMode(DCMOTOR, OUTPUT);
} 
 
 
void loop() 
{ 
  for(int i = 0; i<255; i++){ //Increase speed
    analogWrite(DCMOTOR,i);  
    delay(50);
  }
  for(int i = 255; i>0; i--){ //Decrease speed
    analogWrite(DCMOTOR,i); 
    delay(10);
  }
} 
