#include "../include/main.h"
#include "../globals/globals.hpp"

#include "scoring.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

const unsigned redHue = 55; const unsigned blueHue = 78;

const unsigned turn_roller(const int rate) {
    const unsigned tolerance = 10;
    
    const unsigned currHue = (redHue-tolerance < optical_sensor.get_hue() 
        && optical_sensor.get_hue() < redHue+tolerance) ? redHue : blueHue;
    while (currHue - tolerance < optical_sensor.get_hue() &&
            optical_sensor.get_hue() < currHue + tolerance) {
        roller = rate;
        master.print(0, 0, "%s", "hi");
    }
    roller = MOTOR_BRAKE_BRAKE;
    master.print(0, 0, "%s", "hello");
    return (currHue == redHue) ? redHue : blueHue;
}

void aim_shot()
{ bool aimed = false;
    while (aimed == false) {
        pros::vision_object_s_t goal = vision_sensor.get_by_size(0);
        double centre = goal.x_middle_coord;
        if (centre > 10){
            move(50, -50);
        }
        else if (centre < -10){
            move(-50, 50);
        }
        else{
            aimed = true;
        }
           }
           move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}