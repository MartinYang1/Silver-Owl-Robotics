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
    
    unsigned timeElapsed = 0;
    while ((currHue - 10 <= optical_sensor.get_hue() && optical_sensor.get_hue() <= currHue + 10) && timeElapsed < 3300) {
        roller = rate;
        timeElapsed += 15;
        pros::delay(15);
    }
    roller = -rate;
    pros::delay(80);
    roller = MOTOR_BRAKE_BRAKE;
    optical_sensor.set_led_pwm(0);
    pros::delay(50);
    return optical_sensor.get_hue();
}

/** Aims the flywheel shooter toward the center of the high goal (AIMBOT)
 * using the vision sensor
 * 
 * @param pCenter the pointer to the vector data structure for the robot
*/
void aim_shot(vector *pCenter) {
    bool isAiming = false;
    while (!isAiming) {
        pros::vision_object_s_t goal = vision_sensor.get_by_size(0);
        double centre = goal.x_middle_coord;
        if (centre > 130){
            move(-40, 40);
        }
        else if (centre < 150){
            move(40, -40);
        }
        else{
            isAiming = true;
        }
        pros::delay(15);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
    pCenter->heading = get_heading();
}

/** Regulates the flywheel voltage 
 * using PID to meet the desired RPM
 * 
 * @param param the desired RPM for the flywheel
*/
void regulateFlywheel(void *param) {
    unsigned desiredSpeed = *static_cast<unsigned*>(param); double currSpeed = 0;
    int prevError = 0, integral = 0;
    flywheel = 127;
    while (std::abs(flywheel.get_actual_velocity()) * motorToFlywheel < desiredSpeed)
    {
        pros::delay(15);
    }
    *static_cast<unsigned*>(param) = INT16_MAX;
    while (true) {
        desiredSpeed = *static_cast<unsigned*>(param);
        //master.print(0, 0, "%f", currSpeed);
        currSpeed = std::abs(flywheel.get_actual_velocity()) * motorToFlywheel;
        flywheel = 113+PID(currSpeed, desiredSpeed, 0.34, 0.06, 0.12, prevError, integral);
        pros::delay(35);
    }
}
void regulateFlywheel_2(void *param) {
    unsigned desiredSpeed = *static_cast<unsigned*>(param); double currSpeed = 0;
    int prevError = 0, integral = 0;
    flywheel = 127;
    pros::delay(1700);
    *static_cast<unsigned*>(param) = INT16_MAX;
    while (true) {
        desiredSpeed = *static_cast<unsigned*>(param);
        //master.print(0, 0, "%f", currSpeed);
        currSpeed = std::abs(flywheel.get_actual_velocity()) * motorToFlywheel;
        flywheel = 113+PID(currSpeed, desiredSpeed, 0.335, 0.06, 0.12, prevError, integral);
        pros::delay(35);
    }
}

/** Unlocks the gate to fire the discs in posession
 * and then closes the gate
 * 
 * @param gateDelay the number of milliseconds to open the gate for
*/
void shoot(const unsigned gateDelay) {
    flywheel_piston.set_value(1);
    indexer = 109;
    pros::delay(gateDelay); 
    flywheel_piston.set_value(0);
}
