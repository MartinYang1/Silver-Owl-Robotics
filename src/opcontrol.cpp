#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"

void opcontrol() {
	unsigned shootingSpeed = 2100;
	pros::Task regulateFlywheelSpeed(regulateFlywheel, &shootingSpeed);
	expander1_piston.set_value(0);
	expander2_piston.set_value(0);

	flywheel_piston.set_value(0);
	int intake_state=1;
	int flywheel_state=0;
	while (true) {
		shootingSpeed = 2100;
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*-1;
		int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*-1;
		move(power - turnRate, power + turnRate);
		if(master.get_digital(DIGITAL_L1))
		{
			intake=-127;
		}
		else if(master.get_digital(DIGITAL_L2))
		{
			intake=0;
		}
		else 
		{
			intake=127;
		}
		if (master.get_digital(DIGITAL_R2) )
 {
			flywheel_piston.set_value(1);
			intake=127;
		}
		else
		{
			flywheel_piston.set_value(0);
		}
		if (master.get_digital(DIGITAL_R1))
 {
			//vector center11 = {};
			//aim_shot(&center11);
		}

		if(master.get_digital(DIGITAL_UP) && master.get_digital (DIGITAL_DOWN) && master.get_digital (DIGITAL_RIGHT) && master.get_digital (DIGITAL_LEFT))
		{
			expander1_piston.set_value(1);
			expander2_piston.set_value(1);
		}
		else
		{
			expander1_piston.set_value(0);
			expander2_piston.set_value(0);
		}
		
	}
}