#pragma once

enum AUTON
{
    positiveSide,
    negativeWP,
    soloWP,
    skill,
    tests,
};

void autonSelector(enum AUTON strat, float side);
void negative(float side);
void winPoint(float side);
void positive(float side);
void fourRings(float side);
void skills();
void negativeRush(float side);
