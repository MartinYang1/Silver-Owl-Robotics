#include "../include/main.h"
#include "../globals/globals.hpp"

#include "scoring.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"


/** Turns the roller to its opposite colour side
 * 
 * @param rate the voltage for the motor, from -127 to 127
 * 
 * @return the hue of the new colour that the roller has turned to
 */
const unsigned turn_roller(const int rate, const unsigned tolerance) {    
    const unsigned currHue = optical_sensor.get_hue();
    while (currHue - tolerance < optical_sensor.get_hue() &&
            optical_sensor.get_hue() < currHue + tolerance) {
        roller = rate;
        master.print(0, 0, "%f", optical_sensor.get_hue());
        pros::delay(15);
    }
    roller = MOTOR_BRAKE_BRAKE;
    master.print(0, 0, "%s", "hello");
    return optical_sensor.get_hue();
}

void aim_shot() { 
    bool isAiming = false;
    while (!isAiming) {
        pros::vision_object_s_t goal = vision_sensor.get_by_size(0);
        double centre = goal.x_middle_coord;
        if (centre > 10){
            move(50, -50);
        }
        else if (centre < -10){
            move(-50, 50);
        }
        else{
            isAiming = true;
        }
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

void shoot(const unsigned desiredSpeed, bool actuatePiston) {
    const unsigned currSpeed = flywheel.get_actual_velocity();
    while (currSpeed < desiredSpeed - 5) {
        const unsigned currSpeed = flywheel.get_actual_velocity();
        flywheel = PID(currSpeed, desiredSpeed, 2, 0, 0);
    }
    if (actuatePiston) {
        flywheel_piston.set_value(1);
        pros::delay(200);
        flywheel_piston.set_value(0);
    }
}