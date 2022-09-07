#include "../include/main.h"
#include "../globals/globals.hpp"

#include "scoring.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

const unsigned redHue = 55; const unsigned blueHue = 78;

/** Turns the roller to its opposite colour side
 * 
 * @param rate the voltage for the motor, from -127 to 127
 * 
 * @return the hue of the new colour that the roller has turned to
 */
const unsigned turn_roller(const int rate) {
    const unsigned tolerance = 10;
    
    const unsigned currHue = (redHue-tolerance < optical_sensor.get_hue() 
        && optical_sensor.get_hue() < redHue+tolerance) ? redHue : blueHue;
    while (currHue - tolerance < optical_sensor.get_hue() &&
            optical_sensor.get_hue() < currHue + tolerance) {
        roller = rate;
        master.print(0, 0, "%f", optical_sensor.get_hue());
        pros::delay(15);
    }
    roller = MOTOR_BRAKE_BRAKE;
    master.print(0, 0, "%s", "hello");
    return (currHue == redHue) ? redHue : blueHue;
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