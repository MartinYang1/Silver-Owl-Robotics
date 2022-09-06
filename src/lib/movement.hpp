#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../include/main.h"
#include "pros/motors.h"

struct vector {
    double x = 0, y = 0;
    float dist = 0, heading = 0;
};

extern void move(const int leftVolt, const int rightVolt);
extern void move_straight(const double desiredDist, pros::motor_brake_mode_e_t stopType = pros::E_MOTOR_BRAKE_BRAKE);
extern void move_straight(const unsigned time);
extern void turn(const int baseLeftVolt, const int baseRightVolt, const float desiredAngle);

#endif