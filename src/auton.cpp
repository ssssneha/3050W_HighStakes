#include "stdio.h"
#include "vex.h"
#include <auton.h>
#include <math.h>
#include <iostream>
#include <string>
#include <odometry.h>

/*
     █████╗   ██╗   ██╗  ████████╗   ██████╗   ███╗   ██╗
    ██╔══██╗  ██║   ██║  ╚══██╔══╝  ██╔═══██╗  ████╗  ██║
    ███████║  ██║   ██║     ██║     ██║   ██║  ██╔██╗ ██║
    ██╔══██║  ██║   ██║     ██║     ██║   ██║  ██║╚██╗██║
    ██║  ██║  ╚██████╔╝     ██║     ╚██████╔╝  ██║ ╚████║
    ╚═╝  ╚═╝   ╚═════╝      ╚═╝      ╚═════╝   ╚═╝  ╚═══╝
*/

/*
  ███████╗██╗  ██╗██╗██╗     ██╗     ███████╗     ██████╗ ██████╗ ██╗██████╗ 
  ██╔════╝██║ ██╔╝██║██║     ██║     ██╔════╝    ██╔════╝ ██╔══██╗██║██╔══██╗
  ███████╗█████╔╝ ██║██║     ██║     ███████╗    ██║  ███╗██████╔╝██║██║  ██║
  ╚════██║██╔═██╗ ██║██║     ██║     ╚════██║    ██║   ██║██╔══██╗██║██║  ██║
  ███████║██║  ██╗██║███████╗███████╗███████║    ╚██████╔╝██║  ██║██║██████╔╝
  ╚══════╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝╚═════╝ 

  +-----------------+-----------------+
  |+ blue           | + red           |
  |      Grid       |      Grid       |
  |      Section    |      Section    |
  |        1        |        2        |
  |                 |                 |
  +-----------------+-----------------+
  |- blue           | - red           |
  |      Grid       |      Grid       |
  |      Section    |      Section    |
  |        3        |        4        |
  |                 |                 |
  +-----------------+-----------------+
*/


int drivePID(float target, float accuracy = 1, float kp = 4.5);
int PIDturn(float target, float accuracy = 1);
int belt(int speed);

void safety();

void test();
void increment();
void driveStop(brakeType E = brake);
void turnToPoint(point target);
void arcTurn(float distance, float radius, float speed);
void autonSelector(AUTON strat, float side);



// 1 = blue
// -1 = red

void autonSelector(AUTON strat, float side){
    switch(strat){
        case positiveSide:
            positive(side);
        break;
        case negativeWP:
            negative(side);
        break;
        case soloWP:
            winPoint(side);
        break;
        case skill:
            skills();
        break;
    }
}

/*
  ██╗███╗   ██╗    ██╗   ██╗███████╗███████╗
  ██║████╗  ██║    ██║   ██║██╔════╝██╔════╝
  ██║██╔██╗ ██║    ██║   ██║███████╗█████╗  
  ██║██║╚██╗██║    ██║   ██║╚════██║██╔══╝  
  ██║██║ ╚████║    ╚██████╔╝███████║███████╗
  ╚═╝╚═╝  ╚═══╝     ╚═════╝ ╚══════╝╚══════╝
*/

void skills(){
  // Path
  //drivePID(50);
  //intake.spin(reverse);

  // alliance stake
  intake.setVelocity(100, percent);
  belt(86);
  drivePID(-3);
  // turn to and clamp mogo
  PIDturn(-110);
  drivePID(-26,1,3.0);
  clamp.set(!clamp.value());
  intake.spin(reverse);
  // grid section 2
  //belt(48);
  PIDturn(0);
  drivePID(24);
  PIDturn(55);
  drivePID(35);
  drivePID(-12);
  wait(500, msec);
  PIDturn(179);
  drivePID(24);
  drivePID(24);
  PIDturn(-35);
  drivePID(-7);
  clamp.set(!clamp.value());
  drivePID(8);
  drivePID(-7);
  
  // grid section 1
  drivePID(16);
  PIDturn(0);
  drivePID(46);
  PIDturn(-45);
  drivePID(48);
  PIDturn(-90);
  drivePID(-48);
  drivePID(40);
  PIDturn(90);
  drivePID(-5, 1, 3.0);
  clamp.set(!clamp.value());
  
}

// working
void winPoint(float side){
  intake.setVelocity(100, percent);
  drivePID(-27,1,3.5);
  clamp.set(!clamp.value());
  //wait(1, sec);
  intake.spin(reverse);
  belt(60);
  wait(500, msec);
  PIDturn(-80*side);
  //belt(0);
  drivePID(24);
  wait(100, msec);
  intake.spin(forward);
  PIDturn(65*side);
  wait(100, msec);
  drivePID(28,1,5.5);
  clamp.set(!clamp.value());
  drivePID(20,1,5.5);
  PIDturn(90*side);
  intake.spin(reverse);

  drivePID(25,1,5.5);
  PIDturn(38*side);
  drivePID(-19.5,1,3.5);
  clamp.set(!clamp.value());
  belt(60);  
  PIDturn(90*side);
  drivePID(23,1,6);
  //wait(500, msec);
  PIDturn(85*side);
  drivePID(-38,1,6);  
}

void negative(float side){
  drivePID(-13);
  PIDturn(-90*side);
  drivePID(-6);
  intake.setVelocity(100, percent);
  belt(100);
  intake.spin(forward);
  wait(1000, msec);
  drivePID(15);
  // turn to and clamp mogo
  PIDturn(-210*side);
  wait(100, msec);
  drivePID(-20);
  drivePID(-6, 1, 3.5);
  clamp.set(!clamp.value());
  // turn to and intake the rings
  PIDturn(-45*side);
  intake.spin(reverse);

  belt(75);
  drivePID(20);
  wait(500, msec);
  PIDturn(-5*side);
  drivePID(10);
  PIDturn(125*side);
  drivePID(20,1,5);
  PIDturn(-170*side);
  drivePID(20,1,10);
  /* 
  PIDturn(-90);
  drivePID(24);
  PIDturn(-45);
  drivePID(24);
  */
}

void positive(float side){
  intake.setVelocity(100, percent);
  //belt(60);
  drivePID(-28);
  //wait(500, msec);
  PIDturn(25*side);
  drivePID(-8,1,3.5);
  clamp.set(!clamp.value());
  belt(60);
  wait(1000, msec);
  belt(0);
  PIDturn(0*side);
  intake.spin(reverse);
  drivePID(15,1,3.5);
  wait(500, msec);
  clamp.set(!clamp.value());
  PIDturn(89*side);

  drivePID(-16);
  drivePID(-6, 1, 3.0);
  clamp.set(!clamp.value());
  belt(60);
  wait(500, msec);
  //intake.stop();
  PIDturn(225*side);
  drivePID(13);
}

/*
  ███╗   ██╗ ██████╗ ████████╗    ██╗███╗   ██╗    ██╗   ██╗███████╗███████╗
  ████╗  ██║██╔═══██╗╚══██╔══╝    ██║████╗  ██║    ██║   ██║██╔════╝██╔════╝
  ██╔██╗ ██║██║   ██║   ██║       ██║██╔██╗ ██║    ██║   ██║███████╗█████╗  
  ██║╚██╗██║██║   ██║   ██║       ██║██║╚██╗██║    ██║   ██║╚════██║██╔══╝  
  ██║ ╚████║╚██████╔╝   ██║       ██║██║ ╚████║    ╚██████╔╝███████║███████╗
  ╚═╝  ╚═══╝ ╚═════╝    ╚═╝       ╚═╝╚═╝  ╚═══╝     ╚═════╝ ╚══════╝╚══════╝
*/

void test(){
  turnToPoint(point(25,25));
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