using namespace vex;

extern brain Brain;

extern controller controller1;

extern motor leftFwd;
extern motor leftMid;
extern motor leftBack;

extern motor rightFwd;
extern motor rightMid;
extern motor rightBack;

extern motor catapult;
extern motor intake;

extern pneumatics clamp;
extern pneumatics lWing;

extern inertial gyro4;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);