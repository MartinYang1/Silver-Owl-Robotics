#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

	vector center =
	{
		// .x = 0.0,
		// .y = 0.0,
        // .dist = 0.0,
		// .heading = 0.0
	};

void test() {
    
    // pros::vision_zero_e_t oof{pros::E_VISION_ZERO_CENTER};
    // vision_sensor.set_zero_point(oof);
    // while (true) {
    //     master.print(0, 0, "%d", optical_sensor.get_proximity());
    //     pros::delay(20);
    // }
    // imu_sensor.reset();
    // pros::delay(2000);
    // imu_sensor.tare_heading();
    // pros::delay(100);
    // turn(80, 80, 80, &center);
    // master.print(0, 0, "%d", imu_sensor.get_heading());
    // pros::delay(1000);

    //  imu_sensor.reset();
    //  pros::delay(2000);
    // pros::Task track_position(odometry, &center);
    // pros::delay(100);
    // move_straight(10.0, MOTOR_BRAKE_COAST);
    
//     turn(80,80,450,&center);
// pros::delay(40);
//     turn(80,80,-450,&center);
    // unsigned timeElapsed = 0;
    // pros::Task track_time(stopwatch, &timeElapsed);
    imu_sensor.tare_heading();
    pros::delay(50);
     pros::Task track_position(odometry, &center);
     move_straight(24.0);
   // turn(50, 0, 90, &center);
   // master.print(0, 0, "%f", center.x);
    // track_time.remove();
    // // aim_shot();
    
}
