#include <vector>
#include <algorithm>

#include "../include/main.h"
#include "../globals/globals.hpp"

#include "scoring.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

const double motorToFlywheel = 7 / 1;

/** Turns the roller to its opposite colour side
 * 
 * @param rate the voltage for the motor, from -127 to 127
 * 
 * @return the hue of the new colour that the roller has turned to
 */
const unsigned turn_roller(const int rate) {
    optical_sensor.set_led_pwm(100);
    pros::delay(50);

    unsigned short currHue = optical_sensor.get_hue();
    while (currHue - 30 <= optical_sensor.get_hue() && optical_sensor.get_hue() <= currHue + 30) {
        roller = rate; roller2 = rate;
        pros::delay(15);
    }
    roller = MOTOR_BRAKE_BRAKE; roller2 = MOTOR_BRAKE_BRAKE;
    optical_sensor.set_led_pwm(0);
    pros::delay(50);
    return optical_sensor.get_hue();
}

void aim_shot() {
    bool isAiming = false;
    while (!isAiming) {
        pros::vision_object_s_t goal = vision_sensor.get_by_size(0);
        double centre = goal.x_middle_coord;
        if (centre > 5){
            move(50, -50);
        }
        else if (centre < -5){
            move(-50, 50);
        }
        else{
            isAiming = true;
        }
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

void shoot(const unsigned desiredSpeed, bool actuatePiston) {
    double currSpeed = std::abs(flywheel.get_actual_velocity()) * motorToFlywheel;
    while (currSpeed < desiredSpeed - 5) {
        master.print(0, 0, "%f", flywheel.get_actual_velocity());
        currSpeed = std::abs(flywheel.get_actual_velocity()) * motorToFlywheel;
        flywheel = PID(currSpeed, desiredSpeed, 2, 0, 0), flywheel2 = PID(currSpeed, desiredSpeed, 2, 0, 0);
        pros::delay(15);
    }
    flywheel = currSpeed; flywheel2 = currSpeed;
    pros::delay(200);
    if (actuatePiston) {
        flywheel_piston.set_value(1);
        pros::delay(200);
        flywheel_piston.set_value(0);
    }
}