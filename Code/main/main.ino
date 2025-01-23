#include <QTRSensors.h>
#include "motors.h"
#include <VL53L0X.h> //Include the VL53L0X library
#include "Wire.h" //The Wire.h library is required for I2C communication

//variables
int max_vel=180;
int error=0;
int last_time=0;
int seconds;
int last_error=0;
int UMBRAL_WHITE=30;
int umbral_dist=40;
int time_for_task_1=(60)*1000;//60 seconds



int distance;
int last_distance;
int diff=0;
int right_vel=50;
int left_vel=-50;



float kp=0.025;
float ki=0;
float kd=0;
float vel=0;
bool read=true;

//pines del motor      
#define NUM_SENSORS 8
#define TIMEOUT 2500
#define EMITTER_PIN 4 
const int pinAIN2=10;
const int pinAIN1=9;
const int pinBIN1=5;
const int pinBIN2=6;
const int pinSTBY=12;


//QTR DECLARATION
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
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

VL53L0X L0X1 = VL53L0X();



void setup() {
  // INITIALIZE QTR SENSORS
  
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){14,15,16,17,18,19,20,21},8);//{14,15,16,17,18,19,20,21},8;
  qtr.setEmitterPin(EMITTER_PIN);
  //Wire.begin();
  // CALIBRATION
  delay(500);

  //if(!L0X1.init()){ //Initialize sensor 1 and wait for answer
  //                  //If the answer is false, then send an error
  //                  //message and wait for restart
  //  Serial.println("Sensor error");
  //  while(1); //Arduino enters infinite loop
  //}

  //L0X1.setTimeout(500);
  //L0X1.setMeasurementTimingBudget(200000); //Every 200ms a measurement is possible
  //L0X1.startContinuous();
  Serial.begin(9600);
  Serial.println("CALIBRATION");
  for(int i=0;i<400;i++){
    qtr.calibrate();
  }
  Serial.println("CALIBRATION DONE");
  //two_motors.setup();
  delay(1000);
}

void loop() {
  switch(task){
        //TASK1//
        case doing_task_1:{
          two_motors.avanzar_after_PID(255,255);//CHANGING OUR MOTORS VELOCITY
          
          position=qtr.readLineBlack(sensorValues);//READ LINE
          for (uint8_t i = 0; i < 8; i++){
            Serial.print(sensorValues[i]);
            Serial.print('\t');
          }
          
          
          Serial.print(position);
          Serial.print('\t');
          error=((position)-(3500));//CALCULATIN THE ERROR RESPECTING THE CENTER VALUE
          seconds=(millis()-last_time);//GAP OF TIME
          vel=two_motors.PID(error,seconds,last_error,ki,kp,kd,max_vel);//USING PID FOR CALCULATIN THE VARIATION OF VELOCITY OUR MOTORS NEED
          Serial.print('\t');
          Serial.println(vel);
          two_motors.avanzar_after_PID(max_vel-vel,max_vel+vel);//CHANGING OUR MOTORS VELOCITY
          last_error=error;
          last_time=millis();
          delay(100);
          
          /*
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
          */
          break;
        }


        case doing_task_2:{
          Serial.println("in task 2");
          //two_motors.avanzar_after_PID(left_vel,right_vel);
          //Serial.print("Sensor[mm]: ");
          //distance=L0X1.readRangeContinuousMillimeters();
          //Serial.println(distance);
          ////Uncomment the code below for single measurement
          ////Serial.println(L0X1.readRangeSingleMillimeters());
          //if (L0X1.timeoutOccurred()) { Serial.println(" TIMEOUT"); } 


          //if(read){
          //   last_distance=distance;
          //   read=false;
          //}
          //else{
          //  diff=distance-last_distance;
          //  if(diff<umbral_dist){
          //    right_Vel=100;left_vel=100;
          //  }
          //}
          
          break;
        }
    
  }
  
}
