#define TRIG 7
#define ECHO 6

int distance;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
  Serial.begin(9600); //Initiaize serial communication with a 
                      //baud rate  of 9600
  digitalWrite(TRIG,LOW); //Set TRIGGER pin to LOW
  delayMicroseconds(2);
}
void loop() {
  ping(TRIG); //call the ping() function and pass the pin number to 
              //to which the TRIGGER pin is connected
  distance = measure(ECHO); //call the measure() function and pass the
                            //pin number to which the ECHO pin is connected 

  //Screen output
  Serial.print("Distance: ");
  Serial.print(distanz);
  Serial.println("cm");

  delay(500);
}

//The ping function has no return but a parameter defining the pin
//number to which the TRIGGER pin is connected
void ping(int trigPin){
  //Trigger ultrasound pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

//The ping function returns the calculated distance 
//and requires a parameter defining the pin number
//to which the ECHO pin is connected
int measure(int echoPin){
  //measure the length of the HIGH signal at the ECHO pin
  long timeEcho = pulseIn(echoPin, HIGH);
  //Calculate distance and return the result
  return timeEcho*0.034/2; //in cm
}
