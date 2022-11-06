#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

vector center3 = {};

void test() {
    setup_robot();
    // turn(20, -20, 90, 1, &center3);   delay(200);  turn(20, -20, 180, 1, &center3); delay(200);
    // turn(20, -20, 270, 1, &center3);

    // delay(500);
    // turn(20, -20, 300, 1, &center3);
    // delay(200);
        turn(-20, 20, 270, 0, &center3);//   delay(200);  turn(-20, 20, 180, -1, &center3); delay(200);
    //turn(-20, 20, 90, -1, &center3);
    // unsigned timeElapsed = 0;
    // pros::Task track_time(stopwatch, &timeElapsed);
    // unsigned shootSpeed = 2600;
    //  setup_robot(timeElapsed, center, shootSpeed);
    //  move_straight(24.0);
    // pros::Task track_position(odometry, &center);
    // turn(25, -25, 90, &center);
    // turn(-25, 25, -179, &center);
    // aim_shot();
}
