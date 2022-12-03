#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"

void opcontrol() {
	unsigned shootingSpeed = 2470;
	pros::Task regulateFlywheelSpeed(regulateFlywheel_o, &shootingSpeed);
	expander1_piston.set_value(0);
	expander2_piston.set_value(0);
	leveler.set_value(1);

	flywheel_piston.set_value(0);
	int intake_state=1;
	int flywheel_state=0;
	while (true) {
		
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*-1;
		int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*-1;
		move(power - turnRate, power + turnRate);
		if (master.get_digital(DIGITAL_R2))
 		{
			flywheel_piston.set_value(0);
			intake=112;
		}
		else if(master.get_digital(DIGITAL_L1))
		{
			intake=-127;
			flywheel_piston.set_value(1);
		}
		else if(master.get_digital(DIGITAL_L2))
		{
			flywheel_piston.set_value(1);
			intake=0;
		}
		else 
		{
			flywheel_piston.set_value(1);
			intake=127;
		}
		if (master.get_digital(DIGITAL_R1))
 		{
			leveler.set_value(0);
			shootingSpeed=3500;
		}
		else if (master.get_digital(DIGITAL_X))
		{
			leveler.set_value(1);
			shootingSpeed = 2470;
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