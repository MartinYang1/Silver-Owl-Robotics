#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"
void opcontrol() {
	expander1_piston.set_value(0);
	shoot(2000, 0);
	int intake_state=1;
	int flywheel_state=0;
	while (true) {
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*-1;
		int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*-1;
		move(power + turnRate, power - turnRate);

		if (master.get_digital_new_press(DIGITAL_R1) )
 {
			shoot(2000, 1);
			shoot(2000, 1);
			shoot(2000, 1);
		}
		if(master.get_digital_new_press(DIGITAL_RIGHT))
		{
			intake_state = 0;
		}

		if(master.get_digital_new_press(DIGITAL_L2))
		{
			if (intake_state > -1)
			{
				intake_state = -1;
			}
		}
		if(master.get_digital_new_press(DIGITAL_R1))
		{
			if (intake_state < 1)
			{
				intake_state = 1;
			}
		}
		if(master.get_digital(DIGITAL_X) && master.get_digital (DIGITAL_B))
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