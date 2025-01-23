#include <Arduino.h>
#include "motors.h"
Motors::Motors(int pinAIN1, int pinAIN2, int pinBIN1, int pinBIN2,int pinSTBY){
   //this->pinSTBY=pinSTBY;
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
}
void Motors::avanzar_after_PID(int speedA, int speedB){
  if(speedA>0){
    analogWrite(pinMotorA[1], speedA);
    digitalWrite(pinMotorA[2], LOW);
  }else{
    digitalWrite(pinMotorA[1], LOW);
    analogWrite(pinMotorA[2], -speedA);
  }
  if(speedB>0){
    analogWrite(pinMotorB[1], speedB);
    digitalWrite(pinMotorB[2], LOW);
  }else{
    digitalWrite(pinMotorB[1], LOW);
    analogWrite(pinMotorB[2], -speedB);
  }
}
float Motors::PID(int error, int seconds,int last_error,float ki,float kp,float kd,int max_vel){
  float vel;
  if(error<=3500 && error>=-3500 ){
    float derivative_error= 1.0*(error-last_error)/seconds;
    float integral_error=1.0*(error+last_error)*seconds/2.0;
    float proportional_error=1.0*error;
    
    Serial.print(seconds);
    Serial.print('\t');
    Serial.print('\t');
    Serial.print(derivative_error);
    Serial.print('\t');
    Serial.print(integral_error);
    Serial.print('\t');
    Serial.print(proportional_error);
    Serial.print('\t');
    Serial.print('\t');
    vel=(1.0*kp*proportional_error+1.0*ki*integral_error+1.0*kd*derivative_error);
    Serial.print(vel);
    Serial.print('\t');
    if(vel>max_vel){vel=max_vel;}
    if(vel<-max_vel){vel=-max_vel;}


    
  }
  else{
    vel=-10000;
  }
  return vel;
}
