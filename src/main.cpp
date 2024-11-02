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

double redirect(color alliance);
void redirectWall(color alliance);

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

void drive(float left, float right, int waitTime){
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

void clampAuto(bool i){
  bool cont = true;
  while(cont){
    if((dist.objectDistance(mm) < 25) || (i == false)){
      clamp.set(!clamp.value());
      wait(0.25, sec);
      cont = false;
    }
  }
}

int controllerPrint(){
  while(true){
    controller1.Screen.setCursor(0, 0);
    controller1.Screen.print("Color = ", colorS.hue());
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
    x = skills (-1` side)
  */

  side = 1;
  autonSelector(goalRush, side);

}

/*
  ██╗   ██╗  ███████╗  ███████╗  ██████╗        ██████╗   ██████╗   ███╗   ██╗  ████████╗  ██████╗    ██████╗   ██╗     
  ██║   ██║  ██╔════╝  ██╔════╝  ██╔══██╗      ██╔════╝  ██╔═══██╗  ████╗  ██║  ╚══██╔══╝  ██╔══██╗  ██╔═══██╗  ██║     
  ██║   ██║  ███████╗  █████╗    ██████╔╝      ██║       ██║   ██║  ██╔██╗ ██║     ██║     ██████╔╝  ██║   ██║  ██║     
  ██║   ██║  ╚════██║  ██╔══╝    ██╔══██╗      ██║       ██║   ██║  ██║╚██╗██║     ██║     ██╔══██╗  ██║   ██║  ██║     
  ╚██████╔╝  ███████║  ███████╗  ██║  ██║      ╚██████╗  ╚██████╔╝  ██║ ╚████║     ██║     ██║  ██║  ╚██████╔╝  ███████╗
   ╚═════╝   ╚══════╝  ╚══════╝  ╚═╝  ╚═╝       ╚═════╝   ╚═════╝   ╚═╝  ╚═══╝     ╚═╝     ╚═╝  ╚═╝   ╚═════╝   ╚══════╝
*/

void usercontrol(void){
  thread controllerPrinting = thread(controllerPrint); // Allows controller print function to run on it's own.
  // Use thread to run too things at a time.
  bool i = false;
  color alliance;
  side = 1;

  if(side == 1){
    alliance = blue;
  }
  else if(side == -1){
    alliance = red;
  }
  int speed;
  colorS.setLightPower(100,pct);
  timer Timer = timer();
  Timer = 100;
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    float leftJoystick = controller1.Axis3.position();
    float rightJoystick = controller1.Axis2.position();

    float a = 2;

    float left_output = ((100*(pow(fabs(leftJoystick),a)))/pow(100,a))*(leftJoystick/fabs(leftJoystick));
    float right_output = ((100*(pow(fabs(rightJoystick),a)))/pow(100,a))*(rightJoystick/fabs(rightJoystick));

    drive(left_output, right_output, 0);
    if(colorS.isNearObject()){
      std::cout<<"yay";
      colorS.setLight(ledState::on);
    }
    else{
      colorS.setLight(ledState::off);
    }

    if((colorS.hue() < 29 or colorS.hue()>340) and colorS.isNearObject() && Timer.value()>0.25){
      Timer.reset();
      speed=0;
    }else if(Timer.value()<0.25){
      speed=0;
    }
    else{
      speed=48;
    }
    

    if (controller1.ButtonR2.pressing()){
      intake.spin(fwd, -100.0, pct);
      belt(100);
      std::cout<<"Color: "<<colorS.hue()<<std::endl;
      //48
    }
    else if (controller1.ButtonUp.pressing()){
      intake.spin(fwd, 100.0, pct);
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
      i = !i;
      clampAuto(i);
    }

    if (controller1.ButtonDown.pressing()){
      StakeMech.set(!StakeMech.value());
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
