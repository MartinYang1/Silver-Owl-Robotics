#include "../include/main.h"
#include "globals/globals.hpp"
void opcontrol()
{
    pusher.set_value(0);
    expander_1.set_value(0);
    expander_2.set_value(0);
    double x= master.get_analog(ANALOG_LEFT_Y);
    double y= master.get_analog(ANALOG_RIGHT_X);
    left_front=left_back=left_middle=x+y;
    right_front=right_back=right_middle=x-y;
    if(master.get_digital(DIGITAL_L2))
    {
        pusher.set_value(1);//firing the piston
    }
    else if(master.get_digital(DIGITAL_L2) == 0)
    {
        pusher.set_value(0);//retracting the position
    }
    int flywheel_state;
    flywheel_state=1;
    if(master.get_digital(DIGITAL_R1))
    {
         if (flywheel_state==2)
        {
            flywheel_state=2;
        }
        else()
        {
            flywheel_state++;

        }
    }
    else if(master.get_digital(DIGITAL_R2))
    {
        if (flywheel_state==0)
        {
            flywheel_state=0;
        }
        else()
        {
            flywheel_state--;

        }
    }
    switch (flywheel_state)
    {
        case(2):
            flywheel=127;
            break;
        case(1):
            flywheel=105;
        case(0):
            flywheel=0;
    }
    int intake_state;
    intake_state=0;
    if(master.get_digital(DIGITAL_UP))
    {
         if (intake_state==1)
        {
            intake_state=1;
        }
        else()
        {
            intake_state++;
        }
    }
    else if(master.get_digital(DIGITAL_DOWN))
    {
        if (intake_state==0)
        {
            intake_state=0;
        }
        else()
        {
            intake_state--;
        }
    }
    switch(intake_state)
    {
        case(1):
        intake=127;
        break;
        case(0):
        intake=0;
        break;
    }
    pros::delay(50);
}