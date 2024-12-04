//Pins for L293D
#define E1 10  // Enable pin motor 1
#define E2 11  // Enable pin motor 2

#define C1 8   // Control pin 1 motor 1
#define C2 9   // Control pin 2 motor 1
#define C3 12  // Control pin 1 motor 2 
#define C4 13  // Control pin 2 motor 2
 
void setup() {
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
 
    pinMode(C1, OUTPUT);
    pinMode(C2, OUTPUT);
    pinMode(C3, OUTPUT);
    pinMode(C4, OUTPUT);
}
 
void loop() {
  
    //Set both motors to run in one direction
    digitalWrite(C1, HIGH);
    digitalWrite(C2, LOW);
    digitalWrite(C3, HIGH);
    digitalWrite(C4, LOW);

    for(int i = 0; i<255; i++){ //Increase speed
      analogWrite(E1,i);  
      analogWrite(E2,i);  
      delay(10);
    }
    for(int i = 255; i>0; i--){ //Decrease speed
      analogWrite(E1,i); 
      analogWrite(E2,i); 
      delay(10);
    }
 
    //Stop motors
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
    delay(200);
 
    //Reverse rotation direction
    digitalWrite(C1, LOW);
    digitalWrite(C2, HIGH);
    digitalWrite(C3, LOW);
    digitalWrite(C4, HIGH);

    for(int i = 0; i<255; i++){ //Increase speed
      analogWrite(E1,i);  
      analogWrite(E2,i);  
      delay(10);
    }
    for(int i = 255; i>0; i--){ //Decrease speed
      analogWrite(E1,i); 
      analogWrite(E2,i); 
      delay(10);
    }

    //Stop motors
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
    delay(200);
}
