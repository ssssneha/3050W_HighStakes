#include "stdio.h"
#include "vex.h"
#include <auton.h>
#include <math.h>
#include <iostream>
#include <string>

int drivePID(float target, float accuracy = 1);
int PIDturn(float target);
int belt(int speed);


// 1 = blue
// -1 = red

void autonSelector(enum AUTON strat, float side){
    switch(strat){
        case fourR:
            fourRings(side);
        break;
        case safe:
            safety();
        case skill:
            skills();
        break;
    }
}

void fourRings(float side){
  // Path
  drivePID(-30);
  clamp.set(!clamp.value());
  intake.spin(reverse);
  belt(48);
  wait(1, sec);
  PIDturn(-115*side);
  drivePID(15);
  PIDturn(-90*side);
  drivePID(9);
  PIDturn(10*side);
  drivePID(23);
  PIDturn(115*side);
  intake.stop(coast);
  belt(0);
  drivePID(32*side);

  /*drivePID(-3);
  PIDturn(186.489);
  drivePID(60.494);
  PIDturn(180);*/
}

void safety(){
  // Path
  drivePID(-30);
  clamp.set(!clamp.value());
  wait(1, sec);
  intake.spin(reverse);
  belt(48);
  wait(1, sec);
}

void skills(){
  // Path
}