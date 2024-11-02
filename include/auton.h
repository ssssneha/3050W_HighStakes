#pragma once

enum AUTON
{
    fourR,
    safe,
    skill,
    goalRush,
};
void autonSelector(enum AUTON strat, float side);