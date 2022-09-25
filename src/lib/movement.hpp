#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../include/main.h"
#include "pros/motors.h"

struct vector {
    double x = 0, y = 0;
    float dist = 0, heading = 0;
};

extern void move(const int leftVolt, const int rightVolt);
extern void move_straight(const double desiredDist, decltype(MOTOR_BRAKE_BRAKE) stopType = MOTOR_BRAKE_BRAKE);
extern void move_straight(const float time, const int volt);
extern void move_straight(const int volt);

extern void turn(const int baseLeftVolt, const int baseRightVolt, const float desiredAngle);

#endif