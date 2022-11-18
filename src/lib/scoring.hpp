#ifndef SCORING_H
#define SCORING_H

#include "movement.hpp"

extern const double motorToFlywheel;    // the gear ratio from the motor to the flywheel

extern void aim_shot(vector *pCenter);
extern const unsigned turn_roller(const int rate);
extern void regulateFlywheel(void *param);
extern void regulateFlywheel_2(void *param);
extern void shoot(const unsigned gateDelay = 1000);

#endif