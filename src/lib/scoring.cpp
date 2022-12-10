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
    pros::delay(100);
    move(18, 18);

    unsigned short currHue = optical_sensor.get_hue();
    unsigned short stHue = optical_sensor.get_hue();
    unsigned timeElapsed = 0;
    while ((stHue - 10 <= currHue && currHue <= stHue + 10) && timeElapsed < 1600) {
        roller = rate;
        currHue = optical_sensor.get_hue();
        timeElapsed += 15;
        pros::delay(15);
    }
    roller = -rate;
    optical_sensor.set_led_pwm(0);
    pros::delay(130);
    roller = 0;
    move(0, 0);
    return optical_sensor.get_hue();
}
const unsigned turn_roller2(const int rate) {
    optical_sensor.set_led_pwm(100);
    pros::delay(100);
    move(12, 12);

    unsigned short currHue = optical_sensor.get_hue();
    unsigned short stHue = optical_sensor.get_hue();
    unsigned timeElapsed = 0;
    
   
    while ((currHue >= 100) && timeElapsed < 2300) {
        roller = rate;
        currHue = optical_sensor.get_hue();
        timeElapsed += 15;
    }
    pros::delay(120);
    timeElapsed = 0;
    while ((currHue <= 100) && timeElapsed < 3200) {
        roller = rate;
        currHue = optical_sensor.get_hue();
        timeElapsed += 15;
        pros::delay(15);
    }
    roller = -rate;
    optical_sensor.set_led_pwm(0);
    pros::delay(370);
    roller = 0;
    move(0, 0);
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
        flywheel = 113+PID2(currSpeed, desiredSpeed, 0.34, 0.1, 0.14, prevError, integral);
        pros::delay(35);
    }
}
void regulateFlywheel_o(void *param) {
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
        flywheel = 110+PID(currSpeed, desiredSpeed, 0.43, 0.05, 0.14, prevError, integral);
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
    indexer = 117;
    pros::delay(gateDelay); 
    flywheel_piston.set_value(0);
}
