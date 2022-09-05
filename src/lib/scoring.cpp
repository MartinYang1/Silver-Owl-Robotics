#include "../include/main.h"
#include "../globals/globals.hpp"

#include "scoring.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

// std::string turn_roller(const int rate) {
    
// }

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