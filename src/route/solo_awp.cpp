#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

vector center = {};

void solo_awp() {
    // initial setup
    unsigned timeElapsed = 0;
    unsigned shootSpeed = 3400;
    setup_robot(timeElapsed, center, shootSpeed);
    delay(800);
    
    // shoot preloads and turn roller
    turn(-50, 50, -3, &center);
    flywheel_piston.set_value(1); delay(800); flywheel_piston.set_value(0);
    pros::delay(50);
    turn(50, -50, 0 - center.heading, &center);
    delay(50);

    move_straight(60); turn_roller(100); delay(100);
    move_straight(-5.0, &center);

    // pick up next 3 discs and shoot them
    intake=100;
    turn(-25, 25, -124, &center);
    move_straight(60.0, 35, &center);
    master.print(0, 0, "%s", "completed");
    pros::delay(20);
    
    turn(25,-25, -45 - (int)(center.heading),&center);
    flywheel_piston.set_value(1); delay(1200); flywheel_piston.set_value(0);
    turn(25,-25, -135 - (int)(center.heading),&center);
    
    // pick up stack of 3 discs and shoot them
    move_straight(60.0, 25, &center);
    turn(25,-25, -25 - (int)(center.heading),&center);
    flywheel_piston.set_value(1); delay(1200); flywheel_piston.set_value(0);
    turn(25,-25, -135 - (int)(center.heading),&center);

    // turn 2nd roller
    move_straight(10.0, 25, &center);
    turn(25,-25, -90 - (int)(center.heading),&center);
    move_straight(60); turn_roller(100);
    //turn()

    //master.print(0, 0, "%d", timeElapsed);
}