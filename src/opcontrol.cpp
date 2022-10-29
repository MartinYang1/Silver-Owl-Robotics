#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"

void opcontrol() {
	flywheel = 127;
    pros::delay(6000);
	unsigned shootingSpeed = 3000;
	pros::Task flywheel_regulation(shoot, &shootingSpeed);
	expander1_piston.set_value(0);
	flywheel_piston.set_value(0);
	int intake_state=1;
	int flywheel_state=0;
	while (true) {
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*-1;
		int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*-1;
		move(power - turnRate, power + turnRate);

		if (master.get_digital(DIGITAL_R1) )
 {
			flywheel_piston.set_value(1);
		
		}
		else
		{
			flywheel_piston.set_value(0);
		}
		if(master.get_digital(DIGITAL_L1))
		{
				intake_state = 0;
		}
		else {
				intake_state = 1;
			}

		if(master.get_digital_new_press(DIGITAL_L2))
		{
			if (intake_state > -1)
			{
				intake_state = -1;
			}
		}

		if(master.get_digital(DIGITAL_X) && master.get_digital (DIGITAL_B) && master.get_digital (DIGITAL_A) && master.get_digital (DIGITAL_Y))
		{
			expander1_piston.set_value(1) ;
			pros::delay(50);
		}
		switch(intake_state)
		{
			case -1:
			intake = -127;
			break;
			case 0:
			intake = 0;
			break;
			case 1:
			intake = 127;
			break;
		}
	}
}