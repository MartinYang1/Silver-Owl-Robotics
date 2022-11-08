#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

void test() {
    vector center3 = {};

    //setup_robot();
    //pros::Task track_position(odometry, &center3);
    //move_straight(48.0, &center3);
    //turn(30, 20, 90, &center3);
    //track_position.remove();
    
    // 20 volts for spot turns, 30 volts for turning around a point
    //turn(-20, 20, 340, &center3);
    //turn(20, -20, 135, &center3);
    // turn(-30, 0, 270, 0, &center3);
    // turn(0, 30, 180, 0, &center3);
    aim_shot(&center3);
}
