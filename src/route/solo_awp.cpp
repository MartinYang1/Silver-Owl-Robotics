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
    unsigned desiredSpeed = 3500;
    pros::Task track_time(stopwatch, &timeElapsed);
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);

    pros::Task track_position(odometry, &center);
    
    // shoot preloads and turn roller
    move_straight(51, &center); turn_roller(100);
    move_straight(-3.4, &center);
    //pick up next 3 discs and shoot them
    desiredSpeed = 3450; 
    intake = 127;
    turn(-25, 25, 232, &center);
    move_straight(49,51, &center, MOTOR_BRAKE_COAST);
    pros::delay(180);
    
    turn(23,-23, 317, &center);
    shoot(1050);
    intake = 127;
    turn(-23,23, 225.5,&center);
    pros::delay(40);
    
    // pick up stack of 3 discs and shoot them (maybe)
 
    move_straight(61.0, 64.0, &center);
    turn(25,-25, 278, &center);
    shoot(1000);
    turn(-25,25, 221, &center);
    pros::delay(80);
    move_straight(5.0, 64.0, &center);
    turn(25,-25, 269, &center);
    move_straight(60, &center); turn_roller(100);


    track_time.remove();
    regulate_shooting_speed.remove();
    track_position.remove();
    master.print(0, 0, "%d", timeElapsed);
}