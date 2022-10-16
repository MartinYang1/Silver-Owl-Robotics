#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"

void opcontrol() {
	while (true) {
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		move(power + turnRate, power - turnRate);
	}
}