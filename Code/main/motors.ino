#include <Arduino.h>
#include "motors.h"
Motors::Motors(int pinAIN1, int pinAIN2, int pinBIN1, int pinBIN2,int pinSTBY){
   this->pinSTBY=pinSTBY;
   this->pinMotorA[0]=pinAIN1;
   this->pinMotorA[1]=pinAIN2;
   this->pinMotorB[0]=pinBIN1;
   this->pinMotorB[1]=pinBIN2;
}
void Motors::setup(){
  pinMode(pinMotorA[0], OUTPUT);
  pinMode(pinMotorA[1], OUTPUT);
  pinMode(pinMotorB[0], OUTPUT);
  pinMode(pinMotorB[1], OUTPUT);
  digitalWrite(pinSTBY,HIGH);
}
void Motors::avanzar_after_PID(int speedA, int speedB){
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
float Motors::PID(int error, int seconds,int last_error,float ki,float kp,float kd,int max_vel){
  if(error<=2000 && error>=-2000 ){
    float derivative_error= (error-last_error)/seconds;
    float integral_error=(error+last_error)*seconds/2.0;
    float proportional_error=error*1.0;
    float vel=(int)(kp*proportional_error+ki*integral_error+kd*derivative_error);
    if(vel>max_vel){vel=max_vel;}
    if(vel<-max_vel){vel=-max_vel;}
  }
  else{
    vel=-10000;
  }
  return vel;
}
