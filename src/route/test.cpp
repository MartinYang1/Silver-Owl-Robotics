#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

void test() {
    // initial setup
    vector center = {};

    unsigned timeElapsed = 0;
    unsigned desiredSpeed = 3200;
    setup_robot();
    
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
    pros::Task track_time(stopwatch, &timeElapsed);
    pros::Task track_position(odometry, &center);

    move_straight(-12.0, &center);
    turn(20, -20, 90, &center);
    turn(5, -20, 270, &center);
    turn(15, 35, 180, &center);
    turn(-20, -20, 90, &center);
    // turn roller and shoot preloads
    // move_straight(22.0, &center);
    // turn(30, 0, 89, &center);
    // move_straight(51, &center); turn_roller(100); delay(400);
    
    // while (desiredSpeed != INT16_MAX) {
    //     delay(15);
    // }
    // indexer = 127;
    // shoot(1200);

    //turn roller
    //turn to aim for shots
    //shoot
    //turn to aim at row of 3 discs
    //turn to shoot
    //turn and drive to low zone 3 discs
    


    track_time.remove();
    regulate_shooting_speed.remove();
    track_position.remove();
}
