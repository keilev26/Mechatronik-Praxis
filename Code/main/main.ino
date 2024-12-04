#include <QTRSensors.h>

int P=0;
int I=0;
int D=0;
int forward=250;
float kp=0.16;
float ki=0.003;
float kd=0.6;
int LAST=0;
float vel;
#define NUM_SENSORS 5
#define TIMEOUT 2500
#define EMITTER_PIN 2
//pines del motor       
#define pinAIN2 7
#define pinAIN1 8
#define pinBIN1 9
#define pinBIN2 10
#define pinSTBY 12
   
//Variables del sensor
QTRSensors qtr;
unsigned int sensorValues[NUM_SENSORS];
unsigned int position=0;
int pinMotorA[]={pinAIN1,pinAIN2};
int pinMotorB[]={pinBIN1,pinBIN2};

void setup() {
  // Initialize the sensors.
  qtr.setTypeRC(); // or setTypeAnalog()
  qtr.setSensorPins((const uint8_t[]){14,15,16,17,18}, 5);
  
  // calibración
  delay(500);
  for(int i=0;i<400;i++){
    qtr.calibrate();
  }
  delay(3000);
  //pines del motor
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  digitalWrite(pinSTBY,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  qtr.readLineBlack(sensorValues);
  position=qtr.readLineBlack(sensorValues);
  P=((position)-(2000));
  if(P<-2000){
    avanzar(0,0);
  }else if(P>2000){
    avanzar(0,0); 
  }
  else{
    D=P-LAST;
    I=P+LAST;
    vel=(P*kp)+(D*kd)+(I*ki);
    if(vel>forward){vel=forward;}
    if(vel<-forward){vel=-forward;}
    LAST=P;
    avanzar(forward-vel,forward+vel);
  }
}
void avanzar(int speedA,int speedB){
  if(speedA>0){
    analogWrite(pinMotorA[1], speedA);
    analogWrite(pinMotorA[2], 0);
  }else{
    analogWrite(pinMotorA[1], 0);
    analogWrite(pinMotorA[2], speedA);
  }
  
  if(speedB>0){
    digitalWrite(pinMotorB[1], speedB);
    digitalWrite(pinMotorB[2], 0);
  }else{
    digitalWrite(pinMotorB[1], 0);
    digitalWrite(pinMotorB[2], speedB);
  }
}
