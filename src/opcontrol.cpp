#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"

void opcontrol() {
	unsigned shootingSpeed = 2200;
	pros::Task regulateFlywheelSpeed(regulateFlywheel_o, &shootingSpeed);
	expander1_piston.set_value(0);
	expander2_piston.set_value(0);
	leveler.set_value(1);

	flywheel_piston.set_value(0);
	int intake_state=1;
	int flywheel_state = 1;
	while (true) {
		shootingSpeed = 2455;
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*-1;
		int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*-1;
		move(power - turnRate, power + turnRate);
		if (master.get_digital(DIGITAL_R2))
 		{
			flywheel_piston.set_value(1);
			intake=112;
		}
		else if(master.get_digital(DIGITAL_L1))
		{
			intake=-127;
			flywheel_piston.set_value(0);
		}
		else if(master.get_digital(DIGITAL_L2))
		{
			flywheel_piston.set_value(0);
			intake=0;
		}
		else 
		{
			flywheel_piston.set_value(0);
			intake=127;
		}
		if (flywheel_state == 1){
			shootingSpeed = 2455;
		}
		else{
		flywheel = 0;
		shootingSpeed = 0;
		}
		if(master.get_digital_new_press(DIGITAL_UP) && master.get_digital (DIGITAL_DOWN) && master.get_digital (DIGITAL_RIGHT) && master.get_digital (DIGITAL_LEFT))
		{
			expander1_piston.set_value(1);
			expander2_piston.set_value(1);
			regulateFlywheelSpeed.remove();
			pros::delay(500);
			flywheel_state = 0;
		}
		else
		{
			expander1_piston.set_value(0);
			expander2_piston.set_value(0);
		}
		
	}
}