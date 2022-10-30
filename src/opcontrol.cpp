#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"

void opcontrol() {
	flywheel = 127;
    pros::delay(6000);
	unsigned shootingSpeed = 2200;
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
			intake=127;
		}
		else
		{
			flywheel_piston.set_value(0);
		}
		if(master.get_digital(DIGITAL_L2))
		{
			intake=0;
		}
		else if(master.get_digital(DIGITAL_L1))
		{
			intake=-127;
		}
		else 
		{
			intake=127;
		}
	

		if(master.get_digital(DIGITAL_UP) && master.get_digital (DIGITAL_DOWN) && master.get_digital (DIGITAL_RIGHT) && master.get_digital (DIGITAL_LEFT))
		{
			expander1_piston.set_value(1);
		}
		
	}
}