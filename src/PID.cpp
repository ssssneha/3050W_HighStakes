#include "stdio.h"
#include "vex.h"
#include <math.h>
#include <iostream>

/*
    ██████╗ ██╗██████╗ 
    ██╔══██╗██║██╔══██╗
    ██████╔╝██║██║  ██║
    ██╔═══╝ ██║██║  ██║
    ██║     ██║██████╔╝
    ╚═╝     ╚═╝╚═════╝ 

*/

void drive(int left, int right, int waitTime);
void driveStop(brakeType E = brake);

void PIDturn(float target){
  float kp = 0.4; // Proportional constant
  float ki = 0.001; // Integral constant
  float kd = 0.9; // Derivative constant
  float yawDeg = gyro4.yaw(deg);
  float accuracy = 2.5;
  float error = target - yawDeg; // Yaw returns -180 to 180, 0 being robot's starting position.
  float totalError = 0;
  float prevError = error;

  while(fabs(error)>accuracy){
    yawDeg = gyro4.yaw(deg);
    error = target - yawDeg;
    float output = kp*error + ki*totalError + kd*(error-prevError);
    std::cout<<"ANGLE error: "<<error<<", YawDeg: "<<yawDeg<<std::endl;
    totalError+=error;
    prevError = error;

    drive(output, -output, 10);
  }
  driveStop(hold);
}

void drivePID(float target, float accuracy){
  //target ex. 15 inch forward
  //listing variables
  //constants
  float kp = 6.0;
  float ki = 0.0;
  float kd = 0.8;
  //distance and radius
  std::cout<<"target "<<target<<std::endl;
  float distance = 0.1;
  const float radius = 3.25/2;

  float integral = 0;
  float derivative;
  float power = 0;

  float yawDeg = gyro4.yaw(deg);
  const float initialYaw = yawDeg;
  float error = target - yawDeg;

  float totalError = 0;
  float prevError = error;
  float angularError;
  std::cout<<"radius : "<< radius<<std::endl;
  leftBack.resetPosition(); 
  rightBack.resetPosition();
  //convert radius and degrees of turn to distance traveled using circumference
  //convert degrees = radians) * radius of wheel
  //2(pi)*radius = circumference

  //if the absolute value of the error is greater than the accuracy
  //NEED TO FIGURE OUT HOW TO INCORPORATE 3-5 GEAR RATIO
  //for every 5 rotations, the wheels go 3
  //5/3 rotation, wheels go 1
  while(fabs(error)>accuracy)
  {
    std::cout<<"DRIVE error: "<<error<<", Distance: "<<distance<<std::endl;
    distance = 3.0/5.0 * ((leftBack.position(deg) + rightBack.position(deg)) / 2.0) * (M_PI/180.0) * radius;
    std::cout<<"DRIVE error: "<<3/5*(leftBack.position(deg)+rightBack.position(deg))/2 * (M_PI/180.0) * radius<<std::endl;
    yawDeg = gyro4.yaw(deg);
    
    angularError = initialYaw - yawDeg;
    error = target - distance;
    derivative = error - prevError;
    integral += error;
    
    if(error == 0 || error <= 0)
    {
      integral = 0;
    }

    if(fabs(error)>(accuracy+25))
    {
      integral = 0;
    }
  
    power = error*kp + integral*ki + derivative*kd;

    totalError += error;
    prevError = error;
    drive(power, power, 10);

  }
  driveStop(hold);
  //note: retune if anything seems amiss or anything about robot is changed (such as speed).
}