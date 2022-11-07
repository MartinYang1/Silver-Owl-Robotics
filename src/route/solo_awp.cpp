#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

void solo_awp() {
    // initial setup
    vector center = {};

    unsigned timeElapsed = 0;
    unsigned desiredSpeed = 3400;
    setup_robot();
    
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
    pros::Task track_time(stopwatch, &timeElapsed);
    pros::Task track_position(odometry, &center);
    const double a[2] = {0, 40};
    move_straight(a, -1, &center, MOTOR_BRAKE_BRAKE);
    track_time.remove();
    regulate_shooting_speed.remove();
    track_position.remove();
    master.print(0, 0, "%d", timeElapsed);
    // delay(50);
    
    // // shoot preloads and turn roller
    // turn(-50, 50, -3, &center);
    // flywheel_piston.set_value(1); delay(800); flywheel_piston.set_value(0);
    // pros::delay(50);
    // turn(50, -50, 0 - center.heading, &center);
    // delay(50);

    // move_straight(60); turn_roller(100); delay(100);
    // move_straight(-5.0, &center);
    //track_time.remove();
    //master.print(0, 0, "%d", timeElapsed);
    // pick up next 3 discs and shoot them
    // shootSpeed = 2000; intake=127;
    // turn(-25, 25, -124, &center);
    // move_straight(60.0, 22, &center);
    // pros::delay(20);
    
    // turn(35,-35, -50 - (int)(center.heading),&center);
    // pros::delay(500);
    // flywheel_piston.set_value(1); delay(1200); flywheel_piston.set_value(0);
    // turn(-35,35, -134 - (int)(center.heading),&center);
    
    // pick up stack of 3 discs and shoot them (maybe)
    //move_straight(75.0, 35, &center);
    //turn(25,-25, -25 - (int)(center.heading),&center);
    //flywheel_piston.set_value(1); delay(1200); flywheel_piston.set_value(0);
    //turn(25,-25, -124 - (int)(center.heading),&center);

    // turn 2nd roller
    //move_straight(10.0, 25, &center);
    // turn(35,-35, -90 - (int)(center.heading),&center);
    // move_straight(60); turn_roller(100);
    //turn()

    //master.print(0, 0, "%d", timeElapsed);
}