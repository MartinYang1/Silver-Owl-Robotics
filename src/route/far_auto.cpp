#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

void far_auto() {
    // initial setup
    vector center = {};
    unsigned timeElapsed = 0;
    unsigned desiredSpeed = 3350;

    setup_robot();
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
    pros::Task track_time(stopwatch, &timeElapsed);
    pros::Task track_position(odometry, &center);

    // turn roller
    move_straight(22.0, &center);
    turn(30, 0, 89, &center);
    move_straight(51, &center); turn_roller(100); delay(100);
    
    // shoot preloads
    move_straight(-4.0, &center);
    turn(25, -25, 94, &center);
    while (desiredSpeed != INT16_MAX) {
        delay(15);
    }
    delay(50);
    shoot(1200);
    move_straight(5.0, 50.0,&center);
    desiredSpeed = 2840;

    // pick up row of 3 discs
    intake = 127;
    turn(25,-25,221,&center);
    move_straight(70.0, 50.0, &center);
    turn(-25,25,144,&center);
    delay(50);
    shoot(1200);
    move_straight(1.5, 50.0, &center);
    turn(-25,25,90,&center);
    //pickup discs next to the goal
    intake=127;
    move_straight(45.0, 50.0, &center);
    move_straight(-40.0,-50.0,&center);
    turn(25,-25,135.0,&center);
    move_straight(-5.0,-50.0,&center);
    shoot(1200);

    // cleanup program
    track_time.remove();
    regulate_shooting_speed.remove();
    track_position.remove();
    master.print(0, 0, "%d", timeElapsed);
 }