#include <vector>
#include <algorithm>

#include "../include/main.h"
#include "../globals/globals.hpp"

#include "scoring.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

const double motorToFlywheel = 36;

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
        roller = rate;
        pros::delay(15);
    }
    roller = MOTOR_BRAKE_BRAKE;
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
        pros::delay(15);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

void shoot(void *param) {
    unsigned desiredSpeed; double currSpeed = 0;
    while (true) {
        desiredSpeed = *static_cast<unsigned*>(param);
        master.print(0, 0, "%f", currSpeed);
        currSpeed = std::abs(flywheel.get_actual_velocity()) * motorToFlywheel;
        flywheel = 110+PID(currSpeed, desiredSpeed, 0.18, 0.04, 0.15);
        pros::delay(35);
    }
}