#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

	vector center =
	{
		.x = 0,
		.y = 0,
        .dist = 0,
		.heading = 0
	};

void test() {
    
    // pros::vision_zero_e_t oof{pros::E_VISION_ZERO_CENTER};
    // vision_sensor.set_zero_point(oof);
    // while (true) {
    //     master.print(0, 0, "%d", optical_sensor.get_proximity());
    //     pros::delay(20);
    // }
    //      imu_sensor.reset();
    //  pros::delay(2000);
    //  imu_sensor.tare_heading();
    //  pros::delay(200);
    // move_straight(50);
    // turn_roller(-100);
    // shoot(4000, 0);
    // pros::delay(5000);
    // shoot(4000, 1);
    //     shoot(4000, 1);
    // shoot(4000, 1);
    imu_sensor.reset();
    pros::delay(2000);
    imu_sensor.tare_heading();
    pros::delay(100);
     //void turn(const int baseLeftVolt, const int baseRightVolt, int desiredAngle, vector *pCentre)
    turn(80, 80, 80, &center);
    master.print(0, 0, "%d", imu_sensor.get_heading());
    pros::delay(1000);

    //  imu_sensor.reset();
    //  pros::delay(2000);
    //  imu_sensor.tare_heading();
    // // // move_straight(80.0, MOTOR_BRAKE_COAST);
    // int a = 5;
    // int *b = &a;
    // pros::Task track_position(odometry, (&center));
    // pros::delay(100);
    // turn(30, -30, 90, &center);
    // track_position.remove();
    // pros::delay(500);
    // master.print(0, 0, "%f", center.x);
    // unsigned timeElapsed = 10;
    // pros::Task track_time(stopwatch, &timeElapsed);
    // move_straight(4, 80);
    // master.print(0, 0, "%d", timeElapsed);
    // // aim_shot();
    
    // pros::delay(2000);x
    //turn_roller(80);
    //shoot(200, 1);
    //master.print(0, 0, "%f", imu_sensor.get_heading());

    
}
