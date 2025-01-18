#ifndef MOTORS_H
#define MOTORS_H
class Motors {
    int pinMotorA[2];
    int pinMotorB[2];
    int pinSTBY;
  public:
    Motors(int,int,int,int,int);
    float PID(int, int, int,float,float,float,int );
    void avanzar_after_PID(int, int);
    void setup();
};

#endif
