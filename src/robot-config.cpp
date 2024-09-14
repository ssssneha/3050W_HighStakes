#include "vex.h"

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1 = controller(primary);

// Initiate and define base motors
motor leftFwd = motor(PORT8, ratio6_1, true);
motor leftMid = motor(PORT2, ratio6_1, true);
motor leftBack = motor(PORT10, ratio6_1, true);
//36 to 60
//6 to 10
//3 to 5

motor rightFwd = motor(PORT12, ratio6_1, false);
motor rightMid = motor(PORT11, ratio6_1, false);
motor rightBack = motor(PORT3, ratio6_1, false);

inertial gyro4 = inertial(PORT10);


// Initiate and define Catapult motor
motor catapult = motor(PORT5, ratio6_1, true);

//Initiate and define Intake motor
motor intake = motor(PORT4, ratio6_1, true);

//Initatie and define pneumatics for wings
pneumatics clamp = pneumatics(Brain.ThreeWirePort.H);
pneumatics lWing = pneumatics(Brain.ThreeWirePort.A);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}