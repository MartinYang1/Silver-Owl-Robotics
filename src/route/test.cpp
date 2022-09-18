#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

void test() {
    // pros::vision_zero_e_t oof{pros::E_VISION_ZERO_CENTER};
    // vision_sensor.set_zero_point(oof);
    //  imu_sensor.reset();
    //  pros::delay(2000);
    //  imu_sensor.tare_heading();
    // // move_straight(80.0, MOTOR_BRAKE_COAST);
    //turn(30, -30, 360);
    // // aim_shot();
    // pros::delay(2000);x
    turn_roller(80);
    //master.print(0, 0, "%f", imu_sensor.get_heading());

    
}
