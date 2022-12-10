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
    unsigned desiredSpeed = 3394;
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);

    // turn roller
    move_straight(15.9, &center);
    turn(35, 0, 89, &center);
    move_straight(51, &center); delay(400); turn_roller(80); delay(400);
    
    // shoot preloads
    move_straight(-3.0, &center);
    turn(29, -29, 93, &center);
    while (desiredSpeed != INT16_MAX) {
        delay(15);
    }
    desiredSpeed = 3480;
    shoot(700);
    move_straight(3.0, 60.0,&center);
    desiredSpeed = 3205;

    // pick up row of 3 discs
    intake = 127;
    turn(29,-29,219,&center);
    move_straight(67.3, 55.0, &center);
    turn(-29,29,141.6,&center);
    move_straight(1.5, 50.0,&center);
    shoot(800);
    // desiredSpeed = 2720;
    // move_straight(1, 61.0, &center);
    // turn(-29,29,90,&center);
    // //pickup discs next to the goal
    // intake=127;
    // move_straight(43.0, 80.0, &center);
    // move_straight(-40.0,-61.0,&center);
    // turn(29,-29,135.0,&center);
    // move_straight(-5.0,-61.0,&center);
    // shoot(800);

    // cleanup program

    regulate_shooting_speed.remove();

    master.print(0, 0, "%d", timeElapsed);
 }