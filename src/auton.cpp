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

void testW();
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
        case tests:
            testW();
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
  int side = 1;
  float a = -90;

  // Path
  intake.setVelocity(100, percent);
  belt(86);
  wait(500, msec);
  // Path

  // Path

  drivePID(5.15);
  PIDturn(338.199+a);
  drivePID(-28.89);
  PIDturn(72.868+a);
  drivePID(21.555);
  PIDturn(317.54+a-180);
  drivePID(36.24);
  PIDturn(359.145+a-180);
  drivePID(14.379);
  PIDturn(303.69+a);
  drivePID(27.853);
  PIDturn(270.655+a);
  drivePID(37.555);
  PIDturn(16.699+a);
  drivePID(-20.163);
  // dropped
  PIDturn(78.139+a);
  drivePID(91.874);
  PIDturn(39.92+a);
  drivePID(54.84);
  PIDturn(0.424+a);
  drivePID(-57.94);
  PIDturn(350.832+a-180);
  drivePID(-68.687);
  PIDturn(39.89+a-180);
  drivePID(37.476);
  PIDturn(315+a);
  drivePID(100.449);
  // moving under ladder
  PIDturn(356.987+a);
  drivePID(16.331);
  PIDturn(265.236+a-180);
  drivePID(-12.92);
  PIDturn(339.995+a);
  drivePID(-47.044);
  PIDturn(37.176+a);
  drivePID(40.128);
  PIDturn(67.733+a);
  drivePID(29.449);
  PIDturn(307.385+a-180);
  drivePID(28.627);
  PIDturn(83.884+a);
  drivePID(36.257);
  PIDturn(347.735+a-180);
  drivePID(-15.152);







  // -1 blue (opposite of normal)
  // Path
  //drivePID(50);
  //intake.spin(reverse);

  // Path
  /*intake.setVelocity(100, percent);
  belt(86);
  //drivePID(-3);
  wait(500, msec);
  PIDturn(-110*side);
  drivePID(-24.542);
  clamp.set(!clamp.value());
  drivePID(-6);
  PIDturn(25);
  drivePID(23.775);
  PIDturn(132);
  drivePID(-32.334);
  PIDturn(90);
  drivePID(13.472);
  PIDturn(129);
  drivePID(18.768);

  PIDturn(180);
  drivePID(47.802);
  PIDturn(-78);
  drivePID(-18.648);
  clamp.set(!clamp.value());
  drivePID(6);
  drivePID(-6);
  // holding ring (add later)
  PIDturn(-12);
  drivePID(91.418);

  PIDturn(263);
  drivePID(55.524);
  PIDturn(166);
  drivePID(-71.548);
  // CRYING
  PIDturn(78);
  drivePID(75.841);
  //PIDturn(34.242);
  drivePID(-75.017);
  clamp.set(!clamp.value());
  PIDturn(135);
  drivePID(20.542);

  PIDturn(-135);
  drivePID(100.656);
  PIDturn(-96);
  drivePID(11.931);

  PIDturn(23.629);
  drivePID(-13.837);
  clamp.set(!clamp.value());
  PIDturn(-157);
  drivePID(-42.097);
  clamp.set(!clamp.value());
  */
  /*
  PIDturn(46.302);
  drivePID(32.876);
  PIDturn(62.916);
  drivePID(26.103);
  PIDturn(297.061);
  drivePID(-27.284);
  PIDturn(270);
  drivePID(-34.069);
  PIDturn(18.667);
  drivePID(-20.628);
  PIDturn(0);
  */






 /*
  // alliance stake
  intake.setVelocity(100, percent);
  belt(86);
  drivePID(-3);
  // turn to and clamp mogo
  PIDturn(-110*side);
  drivePID(-26,1,3.0);
  clamp.set(!clamp.value());
  intake.spin(reverse);
  // grid section 2
  //belt(48);
  PIDturn(-2.5*side);
  drivePID(24);
  PIDturn(55*side);
  drivePID(30);
  drivePID(-12);
  wait(500, msec);
  PIDturn(179*side);
  drivePID(24,1,2.5);
  drivePID(24,1,2.5);
  PIDturn(-35*side);
  drivePID(-7);
  clamp.set(!clamp.value());
  drivePID(8);
  drivePID(-7);
  
  // grid section 1
  drivePID(16);
  PIDturn(0*side);
  drivePID(46);
  PIDturn(-45*side);
  drivePID(48);
  PIDturn(-90*side);
  drivePID(-48);
  drivePID(40);
  PIDturn(90*side);
  drivePID(12);
  clamp.set(!clamp.value());
  */


  
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
  //wait(1000, msec);
  clamp.set(!clamp.value());
  drivePID(-12,1,6);
  PIDturn(-90*side);
  drivePID(-6,1,6);
  intake.setVelocity(100, percent);
  belt(100);
  intake.spin(forward);
  wait(1000, msec);
  drivePID(15,1,6);

  // turn to and clamp mogo
  PIDturn(-215*side);
  wait(100, msec);
  clamp.set(!clamp.value());
  drivePID(-18,1,6);
  drivePID(-8,1,4.5);
  clamp.set(!clamp.value());

  // turn to and intake the rings
  // turn to side ring first

  // 
  // turning to top rings first
  PIDturn(-55*side);
  intake.spin(reverse);
  belt(75);
  drivePID(15,0.5,6);
  wait(250, msec);
  PIDturn(-20*side);
  drivePID(7,1,6);
  PIDturn(-5*side);
  drivePID(10,1,6);
  drivePID(-3,1,6);
  PIDturn(95*side);
  drivePID(20,1,6);
  PIDturn(-200*side);
  drivePID(30,1,10);
  
  /* 
  PIDturn(-90);
  drivePID(24);
  PIDturn(-45);
  drivePID(24);
  */
}

void negativeRush(float side){
  // Path
  intake.spin(reverse);
  drivePID(40.526);
  PIDturn(73.56, 30);
  drivePID(-17.295);
  PIDturn(357.879, 30);
  drivePID(14.694);
  PIDturn(332.688, 30);
  drivePID(-37.338);
  PIDturn(333.664, 30);
  drivePID(-91.33);
  PIDturn(356.987, 30);
}

void positive(float side){
  drivePID(-18,1,6);
  drivePID(-8,1,4);
  clamp.set(!clamp.value());
  intake.setVelocity(100, percent);
  belt(100);  
  wait(500, msec);
  PIDturn(85*side);
  drivePID(36);
}

/*
intake.setVelocity(100, percent);
  //belt(60);
  drivePID(-28,1,5);
  //wait(500, msec);
  PIDturn(25*side);
  drivePID(-8,1,3.5);
  clamp.set(!clamp.value());
  belt(60);
  wait(1000, msec);
  belt(0);
  PIDturn(-5*side);
  intake.spin(reverse);
  drivePID(15,1,3.5);
  wait(500, msec);
  clamp.set(!clamp.value());
  wait(500, msec);
  PIDturn(80*side,0.5);

  drivePID(-16);
  drivePID(-6, 1, 3.0);
  clamp.set(!clamp.value());
  belt(60);
  wait(500, msec);
  //intake.stop();
  PIDturn(215*side);
  drivePID(14);
  */
/*
  ███╗   ██╗ ██████╗ ████████╗    ██╗███╗   ██╗    ██╗   ██╗███████╗███████╗
  ████╗  ██║██╔═══██╗╚══██╔══╝    ██║████╗  ██║    ██║   ██║██╔════╝██╔════╝
  ██╔██╗ ██║██║   ██║   ██║       ██║██╔██╗ ██║    ██║   ██║███████╗█████╗  
  ██║╚██╗██║██║   ██║   ██║       ██║██║╚██╗██║    ██║   ██║╚════██║██╔══╝  
  ██║ ╚████║╚██████╔╝   ██║       ██║██║ ╚████║    ╚██████╔╝███████║███████╗
  ╚═╝  ╚═══╝ ╚═════╝    ╚═╝       ╚═╝╚═╝  ╚═══╝     ╚═════╝ ╚══════╝╚══════╝
*/

void testW(){
    // Path

    drivePID(-12.941, 30);
    PIDturn(295.801);
    drivePID(44.295);
    PIDturn(318.532);
    drivePID(30.31);
    PIDturn(75.964);
    drivePID(-18.511, 30);
    PIDturn(339.151);
    drivePID(-120.954, 30);
    PIDturn(0);
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