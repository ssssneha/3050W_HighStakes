#include "stdio.h"
#include "vex.h"
#include <auton.h>
#include <math.h>
#include <iostream>
#include <string>

/*
     █████╗   ██╗   ██╗  ████████╗   ██████╗   ███╗   ██╗
    ██╔══██╗  ██║   ██║  ╚══██╔══╝  ██╔═══██╗  ████╗  ██║
    ███████║  ██║   ██║     ██║     ██║   ██║  ██╔██╗ ██║
    ██╔══██║  ██║   ██║     ██║     ██║   ██║  ██║╚██╗██║
    ██║  ██║  ╚██████╔╝     ██║     ╚██████╔╝  ██║ ╚████║
    ╚═╝  ╚═╝   ╚═════╝      ╚═╝      ╚═════╝   ╚═╝  ╚═══╝
*/


int drivePID(float target, float accuracy = 1, float kp = 4.5);
int PIDturn(float target);
int belt(int speed);
void fourRings(float side);
void safety();
void skills();
void rush();
void increment();
void driveStop(brakeType E = brake);

// 1 = blue
// -1 = red



void autonSelector(AUTON strat, float side){
    switch(strat){
        case fourR:
            fourRings(side);
        break;
        case safe:
            safety();
        case skill:
            skills();
        case goalRush:
            rush();
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
  //drivePID(50);
  //intake.spin(reverse);
  intake.setVelocity(-48, percent);
  belt(48);
  wait(2, sec);
  intake.stop(coast);
  belt(0);
  drivePID(13);
  PIDturn(-90);
  wait(200, msec);
  drivePID(-18);
  wait(500, msec);
  clamp.set(!clamp.value());
  PIDturn(35);
  intake.spin(reverse);
  belt(45);
  drivePID(48);
  PIDturn(177);
  drivePID(45,1,2);
  PIDturn(45);
}

void rush(){
  drivePID(-30);
  wait(500, msec);
  PIDturn(30);
  drivePID(-8);
  clamp.set(!clamp.value());

}