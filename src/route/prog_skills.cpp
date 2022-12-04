#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

void prog_skills() {
    // initial setup
    vector center = {};

    unsigned timeElapsed = 0;
    unsigned desiredSpeed = 2200;
    leveler.set_value(1);
    pros::Task track_time(stopwatch, &timeElapsed);
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
// first shot
    pros::Task track_position(odometry, &center);
    while (desiredSpeed != INT16_MAX) {
        delay(15);
    }
    desiredSpeed = 2200;
    pros::delay(150);
    shoot(1000);
// first roller
    leveler.set_value(0);
    desiredSpeed = 3350;
    move_straight(42.0, &center);
    turn(35, 0, 89, &center);
    move_straight(51, &center); turn_roller(100); delay(100); turn_roller(100);
// Second Roller
    move_straight(-15.0, &center);
    turn(-23, 23, 2, &center);
    move_straight(51, &center); turn_roller(100); delay(100); turn_roller(100);
// Second Shot (and Pick up)
    intake = 127;
    move_straight(-2.0, &center);
    turn(-23, 23, 237, &center);
    pros::delay(100);
    move_straight(49.0,43, &center);
    turn(30,-30, 320, &center);
    move_straight(2.5, &center);
    shoot(1000);
// Third Shot (and pick up)
    intake = 127;
    move_straight(-2.0, &center);
    desiredSpeed = 2250;
    leveler.set_value(1);
    turn(-22,22, 225.5,&center);
    pros::delay(100);
    move_straight(67.0, 64.0, &center);
    turn(-24,24, 177, &center);
    pros::delay(100);
    move_straight(-20.0, -54.0, &center);
    shoot(1000);
// Third Roller
    move_straight(36.0, 54.0, &center);
    turn(-20,20, 273, &center);
    pros::delay(100);
    move_straight(51, &center); turn_roller(100); delay(100); turn_roller(100);
// Fourth Roller
    move_straight(-16.5, &center);
    turn(-23, 23, 183, &center);
    move_straight(51, &center); turn_roller(100); delay(100); turn_roller(100);
// Fourth Shot
    intake = 127;
    desiredSpeed = 2480;
    move_straight(-2.2, &center);
    turn(-23, 23, 55, &center);
    move_straight(36.0, 54.0, &center);
    turn(-23, 23, 310, &center);
    move_straight(-10.4, &center);
    shoot(1000);
// Fifth Shot
    intake = 127;
    move_straight(14.8, &center);
    turn(23, -23, 51, &center);
    move_straight(72.5, 54.0, &center);
    turn(-23, 23, 357, &center);
    move_straight(-25.0, &center);
    shoot(1000);
// Expansion
    move_straight(50.0, 54.0, &center);
    turn(23, -23, 47, &center);
    expander1_piston.set_value(1);
    expander2_piston.set_value(1);




    track_time.remove();
    regulate_shooting_speed.remove();
    track_position.remove();
    master.print(0, 0, "%d", timeElapsed);
}