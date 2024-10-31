#include "vex.h"
using namespace vex;
// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1 = controller(primary);

// Initiate and define base motors
motor leftFwd = motor(PORT10, ratio6_1, true);
motor leftMid = motor(PORT4, ratio6_1, false);
motor leftBack = motor(PORT3, ratio6_1, true);
//36 to 60
//6 to 10
//3 to 5

motor rightFwd = motor(PORT13, ratio6_1, false);
motor rightMid = motor(PORT14, ratio6_1, true);
motor rightBack = motor(PORT9, ratio6_1, false);

//Initiate and define Gyro sensor
inertial gyro4 = inertial(PORT11);

//Initiate and define Optical sensor
optical colorS = optical(PORT19);

//Initiate and define Intake motor
motor intake = motor(PORT12, ratio18_1, true);

//Initiate and define Belt motors
motor lift1 = motor(PORT5, ratio18_1, false);
motor lift2 = motor(PORT21, ratio6_1, true);

//Initiate and define pneumatics for clamp and wall stake mech
pneumatics clamp = pneumatics(Brain.ThreeWirePort.H);
pneumatics StakeMech = pneumatics(Brain.ThreeWirePort.G);

//Initiate and define AutonSelector
limit switcher = limit(Brain.ThreeWirePort.A);

//Initiate and define AutoClamp
distance dist = distance(PORT7);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}