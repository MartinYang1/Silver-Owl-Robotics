#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"

void opcontrol() {
	int intake_state = 1;
    flywheel = 105;
	while(true)
	{
		leftBackMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		rightBackMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);


int x=master.get_analog(ANALOG_LEFT_Y);
int y=master.get_analog(ANALOG_RIGHT_X);
//int z=master.get_analog(ANALOG_LEFT_X);
		leftFrontMotor = (x+y);
		leftBackMotor = (x+y);
		rightFrontMotor = (x-y);
		rightBackMotor = x-y;
		leftMidMotor=x+y;
		rightMidMotor =x-y;



		int auto_fire = 0;
		//input.append( "m");
		//input.append(std::to_string(left));
		//input.append(std::to_string(right));
		//input.append(".");

		if(master.get_digital_new_press(DIGITAL_L1))
		{
			auto_fire = 1;
			pusher.set_value(1);
			pros::delay(150);
			pusher.set_value(0);
			pros::delay(150);
			pusher.set_value(1);
			pros::delay(150);
			pusher.set_value(0);
			pros::delay(160);
			pusher.set_value(1);
			pros::delay(150);
			pusher.set_value(0);
			pros::delay(100);
			auto_fire = 0;
		}
		if (auto_fire == 0)
		
{
		if(master.get_digital_new_press(DIGITAL_L2))
		{
			pusher.set_value(1);
		}
		else if (master.get_digital(DIGITAL_L2) == 0)
		{
			pusher.set_value(0);
		}
}

 		
		if(master.get_digital_new_press(DIGITAL_LEFT))
		{
			intake_state = 0;
		}

		if(master.get_digital_new_press(DIGITAL_DOWN))
		{
			if (intake_state > -1)
			{
				intake_state = -1;
			}
		}
		if(master.get_digital_new_press(DIGITAL_UP))
		{
			if (intake_state < 1)
			{
				intake_state = 1;
			}
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
	if (master.get_digital(DIGITAL_RIGHT))//expander
	{
			expander1.set_value(1);
			expander2.set_value(1);
			pros::delay(50);
	}
	else //expander
	{
			expander1.set_value(0);
			expander2.set_value(0);
			pros::delay(25);
	}

	//double pastTime = currentTime();
	//input.append("break ");
	//input.append(std::to_string(currentTime()));
	// if (master.get_digital_new_press(DIGITAL_UP))
	// {
	// 	running = false;
	// }
	}
	pros::delay(200);
	// ofs.open(filename, std::ofstream::out | std::ofstream::app);
	// ofs << input << std::endl;
}