#include <QTRSensors.h>
#include "motors.h"


//variables
int max_vel=250;
int error=0;
int last_time=0;
int seconds;
int last_error=0;
int UMBRAL_WHITE=30;
int time_for_task_1=(60)*1000;//60 seconds
float kp=0.16;
float ki=0.003;
float kd=0.6;
float vel;


//pines del motor      
#define NUM_SENSORS 5
#define TIMEOUT 2500
#define EMITTER_PIN 2 
const int pinAIN2=7;
const int pinAIN1=8;
const int pinBIN1=9;
const int pinBIN2=10;
const int pinSTBY=12;


//QTR DECLARATION
QTRSensors qtr;
unsigned int sensorValues[NUM_SENSORS];
unsigned int position=0;


//MOTORS DECLARATION 
Motors two_motors(pinAIN1,pinAIN2,pinBIN1,pinBIN2,pinSTBY);

//STATES DECLARATION
enum states{
  doing_task_1,//Doing task 1(after a certain time or all sensors detect white state will change to doing_task_2)
  doing_task_2,//Doing task 2(once the sensor detects a really near distance state will change to finish state)
  finish_state
};
states task=doing_task_1;



void setup() {
  // INITIALIZE QTR SENSORS
  qtr.setTypeRC(); 
  qtr.setSensorPins((const uint8_t[]){14,15,16,17,18,19,20,21}, 8);
  
  // CALIBRATION
  delay(500);
  for(int i=0;i<400;i++){
    qtr.calibrate();
  }
  delay(1000);
  two_motors.setup();
}

void loop() {
  switch(task){
        //TASK1//
        case doing_task_1:{
          
          position=qtr.readLineBlack(sensorValues);//READ LINE
          error=((position)-(3500));//CALCULATIN THE ERROR RESPECTING THE CENTER VALUE
          seconds=(millis()-last_time);//GAP OF TIME
          vel=two_motors.PID(error,seconds,last_error,ki,kp,kd,max_vel);//USING PID FOR CALCULATIN THE VARIATION OF VELOCITY OUR MOTORS NEED
          two_motors.avanzar_after_PID(max_vel-vel,max_vel+vel);//CHANGING OUR MOTORS VELOCITY 
          last_error=error;
          last_time=millis();
          //
          bool change_state=true;
          for(int i=0;i<8;i++){
             if(sensorValues[i]>UMBRAL_WHITE){
                 change_state=false;
                 break;
             }
          }
          if(millis()>time_for_task_1 || change_state){
            task=doing_task_2;
          }
          break;
        }


        case doing_task_2:{
          
        }
    
  }
  
}
