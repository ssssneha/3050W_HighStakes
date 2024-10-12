/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       3050W                                                     */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  ---                                                       */                   
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
  ██████╗    ██████╗   ███████╗   ██████╗ 
  ╚════██╗  ██╔═████╗  ██╔════╝  ██╔═████╗
  █████╔╝   ██║██╔██║  ███████╗  ██║██╔██║
  ╚═══██╗   ████╔╝██║  ╚════██║  ████╔╝██║
  ██████╔╝  ╚██████╔╝  ███████║  ╚██████╔╝
  ╚═════╝    ╚═════╝   ╚══════╝   ╚═════╝ 

  ██╗    ██╗    ██╗    ██╗         ██████╗      ██████╗     █████╗     ██████╗     ██████╗ 
  ██║    ██║    ██║    ██║         ██╔══██╗    ██╔════╝    ██╔══██╗    ██╔══██╗    ██╔══██╗
  ██║ █╗ ██║    ██║    ██║         ██║  ██║    ██║         ███████║    ██████╔╝    ██║  ██║
  ██║███╗██║    ██║    ██║         ██║  ██║    ██║         ██╔══██║    ██╔══██╗    ██║  ██║
  ╚███╔███╔╝    ██║    ███████╗    ██████╔╝    ╚██████╗    ██║  ██║    ██║  ██║    ██████╔╝
   ╚══╝╚══╝     ╚═╝    ╚══════╝    ╚═════╝      ╚═════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝    ╚═════╝ 

*/


#include "vex.h"
#include "iostream"
#include <robot-config.h>
#include <odometry.h>
#include <PID.h>
#include <auton.h>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

int drivePID(float target, float accuracy);
int PIDturn(float target);
void autonSelector(enum AUTON strat, int side);
void skills();

enum AUTON strat;
float side;
int i;

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

void belt(int speed){
  lift1.spin(fwd, speed, pct);
  lift2.spin(fwd, speed, pct);
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

void increment(){
  i++;
}


/*
  ██████╗   ██████╗   ███████╗       █████╗   ██╗   ██╗  ████████╗   ██████╗   ███╗   ██╗
  ██╔══██╗  ██╔══██╗  ██╔════╝      ██╔══██╗  ██║   ██║  ╚══██╔══╝  ██╔═══██╗  ████╗  ██║
  ██████╔╝  ██████╔╝  █████╗        ███████║  ██║   ██║     ██║     ██║   ██║  ██╔██╗ ██║
  ██╔═══╝   ██╔══██╗  ██╔══╝        ██╔══██║  ██║   ██║     ██║     ██║   ██║  ██║╚██╗██║
  ██║       ██║  ██║  ███████╗      ██║  ██║  ╚██████╔╝     ██║     ╚██████╔╝  ██║ ╚████║
  ╚═╝       ╚═╝  ╚═╝  ╚══════╝      ╚═╝  ╚═╝   ╚═════╝      ╚═╝      ╚═════╝   ╚═╝  ╚═══╝
*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
  /*while (true){
    switcher.pressed(increment);

    if (i==1){
      Brain.Screen.clearLine();
      strat = fourR;
      Brain.Screen.print("Four Rings");
    }
    else if (i==2){
      Brain.Screen.clearLine();
      strat = skill;
      Brain.Screen.print("Skills");
    }
    else if (i==3){
      Brain.Screen.clearLine();
      strat = safe;
      Brain.Screen.print("Safety");
    } 
    else{
      i=0;
    }
  }
  */

  
}

/*
   █████╗   ██╗   ██╗  ████████╗   ██████╗   ███╗   ██╗      ████████╗   █████╗   ███████╗  ██╗  ██╗  ███████╗
  ██╔══██╗  ██║   ██║  ╚══██╔══╝  ██╔═══██╗  ████╗  ██║      ╚══██╔══╝  ██╔══██╗  ██╔════╝  ██║ ██╔╝  ██╔════╝
  ███████║  ██║   ██║     ██║     ██║   ██║  ██╔██╗ ██║         ██║     ███████║  ███████╗  █████╔╝   ███████╗
  ██╔══██║  ██║   ██║     ██║     ██║   ██║  ██║╚██╗██║         ██║     ██╔══██║  ╚════██║  ██╔═██╗   ╚════██║
  ██║  ██║  ╚██████╔╝     ██║     ╚██████╔╝  ██║ ╚████║         ██║     ██║  ██║  ███████║  ██║  ██╗  ███████║
  ╚═╝  ╚═╝   ╚═════╝      ╚═╝      ╚═════╝   ╚═╝  ╚═══╝         ╚═╝     ╚═╝  ╚═╝  ╚══════╝  ╚═╝  ╚═╝  ╚══════╝
*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  /*
    fourR, safe, skill
    1 = blue
    -1 = red

    left = red
    right = blue

    a = fourRings
    b = safety
    x = skills
  */



  /*if (i == 1){
    Brain.Screen.clearLine();
    strat = fourR;
    Brain.Screen.print("Four Rings");
  }
  else if (i == 2){
    Brain.Screen.clearLine();
    strat = skill;
    Brain.Screen.print("Skills");
  }
  else{
    Brain.Screen.clearLine();
    strat = safe;
    Brain.Screen.print("Safety");
  } 


  autonSelector(strat, side);
  s
  
*/

  //side = -1;
  //autonSelector(skill, side);
  intake.spin(reverse);
  belt(45);

}

/*
  ██╗   ██╗  ███████╗  ███████╗  ██████╗        ██████╗   ██████╗   ███╗   ██╗  ████████╗  ██████╗    ██████╗   ██╗     
  ██║   ██║  ██╔════╝  ██╔════╝  ██╔══██╗      ██╔════╝  ██╔═══██╗  ████╗  ██║  ╚══██╔══╝  ██╔══██╗  ██╔═══██╗  ██║     
  ██║   ██║  ███████╗  █████╗    ██████╔╝      ██║       ██║   ██║  ██╔██╗ ██║     ██║     ██████╔╝  ██║   ██║  ██║     
  ██║   ██║  ╚════██║  ██╔══╝    ██╔══██╗      ██║       ██║   ██║  ██║╚██╗██║     ██║     ██╔══██╗  ██║   ██║  ██║     
  ╚██████╔╝  ███████║  ███████╗  ██║  ██║      ╚██████╗  ╚██████╔╝  ██║ ╚████║     ██║     ██║  ██║  ╚██████╔╝  ███████╗
   ╚═════╝   ╚══════╝  ╚══════╝  ╚═╝  ╚═╝       ╚═════╝   ╚═════╝   ╚═╝  ╚═══╝     ╚═╝     ╚═╝  ╚═╝   ╚═════╝   ╚══════╝
*/

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
      intake.spin(fwd, -48.0, pct);
      belt(48);
      //48
    }
    else if (controller1.ButtonUp.pressing()){
      intake.spin(fwd, 48.0, pct);
      belt(-48);
    }
    else if (controller1.ButtonL2.pressing()){
      intake.spin(fwd, -100.0, pct);
      belt(100);
      //48
    }
    else{
      intake.stop(coast);
      belt(0);
    }

    if (controller1.ButtonB.pressing()){
      clamp.set(!clamp.value());
      wait(0.25, sec);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

/*
  ███╗   ███╗   █████╗   ██╗  ███╗   ██╗
  ████╗ ████║  ██╔══██╗  ██║  ████╗  ██║
  ██╔████╔██║  ███████║  ██║  ██╔██╗ ██║
  ██║╚██╔╝██║  ██╔══██║  ██║  ██║╚██╗██║
  ██║ ╚═╝ ██║  ██║  ██║  ██║  ██║ ╚████║
  ╚═╝     ╚═╝  ╚═╝  ╚═╝  ╚═╝  ╚═╝  ╚═══╝
*/
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
