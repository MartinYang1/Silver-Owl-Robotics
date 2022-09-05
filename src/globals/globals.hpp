#ifndef GLOBALS_H
#define GLOBALS_H

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern pros::Controller master;
extern pros::Imu imu_sensor;
extern pros::Motor leftFrontMotor;
extern pros::Motor rightFrontMotor;
extern pros::Motor leftBackMotor;
extern pros::Motor rightBackMotor;
extern pros::Motor right_middle;
extern pros::Motor left_middle;
extern pros::Motor flywheel;
extern pros::Motor intake;
extern pros::ADIDigitalOut pusher;
extern pros::ADIDigitalOut expander_1;
extern pros::ADIDigitalOut expander_2;


extern int autonSelection;

enum AutonEnum {S_BLUE5 = -1, B_BLUE3 = -2, S_BLUE7 = -3, S_BLUE8 = -4, B_BLUE6_C = -5, S_RED5 = 1, B_RED3 = 2, S_RED7 = 3, S_RED8 = 4, B_RED6_C = 5, NOTHING = 10, SKILLS = 0};

template<typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif

