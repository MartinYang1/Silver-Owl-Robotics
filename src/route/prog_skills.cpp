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
    shoot(1300);
// first roller
    desiredSpeed = 2400;
    move_straight(43.7, &center);
    turn(35, 0, 91, &center);
    move_straight(51, &center); turn_roller2(90); 
// Second Roller
    move_straight(-15.0, &center);
    intake = 127;
    turn(-25, 25, 2, &center);
    move_straight(51, &center); turn_roller2(90);
    flywheel_piston.set_value(0);
// Second Shot (and Pick up)
    intake = 127;
    move_straight(-2.0, &center);
    turn(-25, 25, 236, &center);
    pros::delay(100);
    move_straight(50.2,43, &center);
    turn(-30,30, 124, &center);
    move_straight(-2.5, &center);
    shoot(1300);
// Third Shot (and pick up)
    intake = 127;
    move_straight(2.0, &center);
    desiredSpeed = 2310;
    leveler.set_value(1);
    turn(22,-22, 225.5,&center);
    pros::delay(100);
    move_straight(67.0, 64.0, &center);
    turn(-25,25, 177, &center);
    pros::delay(100);
    move_straight(-20.0, -54.0, &center);
    shoot(1300);
// Third Roller
    move_straight(36.0, 52.0, &center);
    turn(21,-21, 273, &center);
    pros::delay(100);
    move_straight(51, &center); turn_roller2(90); 
// Fourth Roller
    move_straight(-16.5, &center);
    intake = 127;
    turn(-23, 23, 183, &center);
    move_straight(51, &center); turn_roller2(90); 
// Fourth Shot
    intake = 127;
    desiredSpeed = 2310;
    move_straight(-2.2, &center);
    turn(-23, 23, 55, &center);
    move_straight(36.0, 54.0, &center);
    turn(-22, 22, 297, &center);
    move_straight(-9.8, -55.0, &center);
    shoot(1000);
// Fifth Shot
    intake = 127;
    desiredSpeed = 2240;
    move_straight(12.5, &center);
    turn(23, -23, 51, &center);
    move_straight(72.5, 54.0, &center);
    turn(-23, 23, 2, &center);
    move_straight(-25.0, &center);
    shoot(1000);
// Expansion
    desiredSpeed = 0;
    move_straight(47.5, 54.0, &center);
    turn(23, -23, 48, &center);
    move_straight(7.5, &center);

    expander1_piston.set_value(1);
    expander2_piston.set_value(1);
    side_piston.set_value(1);
	side2_piston.set_value(1);
    pros::delay(800);

    move_straight(-4.1, &center);



    track_time.remove();
    regulate_shooting_speed.remove();
    track_position.remove();
    master.print(0, 0, "%d", timeElapsed);
}