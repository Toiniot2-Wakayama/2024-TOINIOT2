#pragma once
#ifndef MOTOR_NOUSE

#include "Arduino.h"
#include <math.h>

constexpr int MOTOR_NUM = 4;
const uint8_t MOTOR_PIN[MOTOR_NUM][2] = { { 19, 3 }, { 17, 2 }, { 25, 5 }, { 23, 4 } };
const uint8_t DEFAULT_MOTOR_DIR[MOTOR_NUM] = {1,0,0,1};
enum MOTOR : uint8_t{
  LF = 0,
  LB,
  RB,
  RF,

  PH = 0,
  EN,
};

void motorSetup(){
  for(int j=0;j<MOTOR_NUM;j++){
    for(int i=0;i<2;i++)
      pinMode(MOTOR_PIN[j][i], OUTPUT);
  }

  return;
}

void motorDebug(){
  static int count=0;
  int power = sin(count/40.0)*255;
  for(int i=0;i<4;i++){
    digitalWrite(MOTOR_PIN[i][0], power<0?0:1);
    analogWrite(MOTOR_PIN[i][1], abs(power));
  }
  
  count++;
  return;
}

// blend 0-100
void setDir(short* motor, double dir, double goal_dir, uint8_t power, int blend){
  short mpDir = 0;
  dir -= goal_dir;
  dir = dir < -180 ? dir + 360 : dir;
  dir = dir > 180 ? dir - 360 : dir;

  double P_GAIN_DIR = 0.95;
  if(!(-10<dir && dir<10)){
    mpDir = (dir * P_GAIN_DIR) * (-1);
    for(int i=0;i<4;i++){
      motor[i] = mpDir;
    }
    // Serial.print("dir:");
    // Serial.println(dir);
    // Serial.print("mpDir:");
    // Serial.println(mpDir);
  }
  
  return;
}

void setMove(uint8_t* motor, double dir, uint8_t power, int blend){

  return;
}

void setMotor(short* motor){
  for(int i=0;i<MOTOR_NUM;i++){
    bool flag = DEFAULT_MOTOR_DIR[i];
    if(motor[i]<0) flag = !flag;
    digitalWrite(MOTOR_PIN[i][MOTOR::PH], flag);
    analogWrite(MOTOR_PIN[i][MOTOR::EN], abs(motor[i]*255*0.01));
  }
  return;
}

#endif