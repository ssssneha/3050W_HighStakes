#include "vex.h"

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1 = controller(primary);

// Initiate and define base motors
motor leftFwd = motor(PORT3, ratio6_1, true);
motor leftMid = motor(PORT4, ratio6_1, false);
motor leftBack = motor(PORT5, ratio6_1, true);
//36 to 60
//6 to 10
//3 to 5

motor rightFwd = motor(PORT8, ratio6_1, false);
motor rightMid = motor(PORT19, ratio6_1, true);
motor rightBack = motor(PORT9, ratio6_1, false);

inertial gyro4 = inertial(PORT17);

//Initiate and define Intake motor
motor intake = motor(PORT16, ratio6_1, true);

//Initiate and define Lift motors
motor lift1 = motor(PORT7, ratio6_1, true);
motor lift2 = motor(PORT6, ratio18_1, false);

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