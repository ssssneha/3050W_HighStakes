/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Tank Drive                                                */
/*    This sample allows you to control the V5 Clawbot using the both         */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LeftMotor            motor         1
// RightMotor           motor         10
// ClawMotor            motor         3
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "iostream"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

void driveStop(brakeType E = brake){
  // hold - previous poisition
  // brake - stop
  // coast - stop motors
  leftFwd.stop(E);
  leftMid.stop(E);
  leftBack.stop(E);

  rightFwd.stop(E);
  rightMid.stop(E);
  rightBack.stop(E);
}

void drive(int left, int right, int waitTime){
  leftFwd.spin(fwd, left, pct);
  leftMid.spin(fwd, left, pct);
  leftBack.spin(fwd, left, pct);

  rightFwd.spin(fwd, right, pct);
  rightMid.spin(fwd, right, pct);
  rightBack.spin(fwd, right, pct);
  
  wait(waitTime, msec);
}

void PIDturn(float target, float accuracy = 10){
  float kp = 0.5; // Proportional constant
  float ki = 0; // Integral constant
  float kd = 0.125; // Derivative constant
  float yawDeg = gyro4.yaw(deg);

  float error = target - yawDeg; // Yaw returns -180 to 180, 0 being robot's starting position.
  float totalError = 0;
  float prevError = error;

  while(fabs(error)>accuracy){
    yawDeg = gyro4.yaw(deg);
    float error = target - yawDeg;
    float output = kp*error + ki*totalError + kd*(error-prevError);
    std::cout<<error<<","<<yawDeg<<std::endl;
    totalError+=error;
    prevError = error;

    drive(output, -output, 10);
  }
  driveStop(hold);
}

void drivePID(float target, float accuracy = 1){
  //target ex. 15 inch forward
  //listing variables
  //constants
  float kp = 1;
  float ki = 0;
  float kd = 0;
  //distance and radius
  float distance = target;
  float radius = 3.25/2;

  float integral = 0;
  float derivative;
  float power = 0;

  float yawDeg = gyro4.yaw(deg);
  const float initialYaw = yawDeg;
  float error = target - yawDeg;

  float totalError = 0;
  float prevError = error;
  float angularError;
  
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
    distance = 3/5 * ((leftBack.position(deg) + rightBack.position(deg)) / 2);
    distance = distance * (M_PI/180) * radius;

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

int controllerPrint(){
  while(true){
    controller1.Screen.setCursor(0, 0);
    controller1.Screen.print("L Spin = %.lf", leftFwd.isSpinning());
    controller1.Screen.setCursor(1, 0);
    controller1.Screen.print("R Spin = %.lf", rightFwd.isSpinning());
    controller1.Screen.print("Auton side");
    this_thread::sleep_for(50);
  }
leftFwd.isSpinning();

}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  //lWing.set(false);
  //rWing.set(false);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

    //full screen is 480-240
    /*
    Brain.Screen.drawRectangle(0, 0, 240, 120, red);
    Brain.Screen.drawRectangle(240, 0, 240, 120, red);
    Brain.Screen.drawRectangle(0, 120, 240, 120, blue);
    Brain.Screen.drawRectangle(240, 120, 240, 120, blue);
    waitUntil(Brain.Screen.pressing());
    if (Brain.Screen.xPosition()<240 && Brain.Screen.yPosition()<120)
    {
      std::cout<<"red 1 (left)"<<std::endl;
    }
    if (Brain.Screen.xPosition()<240 && Brain.Screen.yPosition()>120)
    {
      std::cout<<"red 2 (right)"<<std::endl;
    }
    if (Brain.Screen.xPosition()>240 && Brain.Screen.yPosition()<120)
    {
      std::cout<<"blue 1 (left)"<<std::endl;
    }
    if (Brain.Screen.xPosition()>240 && Brain.Screen.yPosition()>120)
    {
      std::cout<<"blue 2 (right)"<<std::endl;
    }
    */

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  thread controllerPrinting = thread(controllerPrint); // Allows controller print function to run on it's own.
  // Use thread to run too things at a time.

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    int leftJoystick = controller1.Axis3.position();
    int rightJoystick = controller1.Axis2.position();

    drive(leftJoystick, rightJoystick, 0);

    if (controller1.ButtonR2.pressing()){
      intake.spin(fwd, 85.0, pct);
    }

    if (controller1.ButtonB.pressing()){
      clamp.set(!clamp.value());
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
