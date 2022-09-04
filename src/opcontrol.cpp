#include "../include/main.h"
#include "globals/globals.hpp"
#include "lib/autoncontrol.hpp"
#include "lib/robotcontrol.hpp"
#include "pros/misc.h"

void opcontrol() {
	int lift_state = 0;
	int front_goal_grabber_state = 0;
	int back_goal_grabber_state = 0;
	int intake_state = 1;
	while(true)
	{
		lift.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		left_mid.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		right_mid.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
/* //Janit's useless X-drive stuff;
		double L_Y = master.get_analog(ANALOG_LEFT_Y);
		double L_X = master.get_analog(ANALOG_LEFT_X);
		double R_X = master.get_analog(ANALOG_RIGHT_X);
		double u = atan2(L_Y,L_X);
		double g = sqrt(L_X*L_X + L_Y*L_Y);
		double one = g * sin(u + (3.14159265358979/4));
		double two = g * sin(u - (3.14159265358979/4));
		double L_F = 127*(-one - R_X)/(abs(R_X)+2.3-g);
		double L_B = 127*(-two - R_X)/(abs(R_X)+2.3-g);
		double R_B = 127*(one - R_X)/(abs(R_X)+2.3-g);
		double R_F = 127*(two - R_X)/(abs(R_X)+2.3-g);
		left_front = L_F;
		left_back = L_B;
		right_front = R_F;
		right_back = R_B;

*/
int x=master.get_analog(ANALOG_LEFT_Y);
int y=master.get_analog(ANALOG_RIGHT_X);
int z=master.get_analog(ANALOG_LEFT_X);
		left_front = (x+y+z);
		left_back = (x+y-z);
		right_front = (x-y-z);
		right_back = x-y+z;



		int auto_fire = 0;
		//input.append( "m");
		//input.append(std::to_string(left));
		//input.append(std::to_string(right));
		//input.append(".");

		if(master.get_digital_new_press(DIGITAL_L1))
		{
			auto_fire = 1;
			front_goal_grappler.set_value(1);
			pros::delay(150);
			front_goal_grappler.set_value(0);
			pros::delay(150);
			front_goal_grappler.set_value(1);
			pros::delay(150);
			front_goal_grappler.set_value(0);
			lift_state=-1;
			pros::delay(160);
			front_goal_grappler.set_value(1);
			pros::delay(150);
			front_goal_grappler.set_value(0);
			lift_state=0;
			pros::delay(100);
			auto_fire = 0;
		}
		else if (auto_fire == 0)
{
		if(master.get_digital_new_press(DIGITAL_L2))
		{
			front_goal_grappler.set_value(1);
		}
		else if (master.get_digital(DIGITAL_L2) == 0)
		{
			front_goal_grappler.set_value(0);
		}
}
		if(master.get_digital_new_press(DIGITAL_R2))
		{
			if (lift_state == 4)
			{
			lift_state = 4;
		}
		else{
			lift_state ++;
		}
		}
		else if(master.get_digital_new_press(DIGITAL_R1))
		{
			if (lift_state == -1)
			{
			lift_state = -1;
			}
			else
			{
				lift_state --;
			}
		}
		
		if(master.get_digital_new_press(DIGITAL_LEFT))
		{
			intake_state = 0;
		}
		if(master.get_digital_new_press(DIGITAL_Y))
		{
			back_goal_grappler.set_value(0);
		}
		if(master.get_digital_new_press(DIGITAL_B))
		{
			back_goal_grappler.set_value(1);
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
		if(master.get_digital_new_press(DIGITAL_RIGHT))
		{
			left_back = MOTOR_BRAKE_HOLD;
			right_back = MOTOR_BRAKE_HOLD;
			right_mid = MOTOR_BRAKE_HOLD;
			left_mid = MOTOR_BRAKE_HOLD;
			left_front = MOTOR_BRAKE_HOLD;
			left_front = MOTOR_BRAKE_HOLD;
		}



		switch(lift_state)
		{
			
			case -1:
					indexer1 =127;
					indexer2 =127;
				break;
			case 0:
					indexer1 =105;
					indexer2 =105;
				break;
			case 2:
					indexer1 =80;
					indexer2 =80;
				break;
			case 3:
					indexer1 =0;
					indexer2 =0;
				break;
		}

		switch(back_goal_grabber_state)
		{
		case 0:
			break;
		case 1:
			break;
		}

		switch(front_goal_grabber_state)
		{
			case 0:
			break;
			case 1:
			break;
		}

		switch(intake_state)
		{
			case -1:
			indexer4 = -127;
			indexer3 = -127;
			break;
			case 0:
			indexer4 = 0;
			indexer3 =0;
			break;
			case 1:
			indexer4 = 127;
			indexer3 =127;
			break;
		}
	if (master.get_digital(DIGITAL_RIGHT))//expander
	{
			expander.set_value(1);
			expander2.set_value(1);
			delay(50);
	}
	else //expander
	{
			expander.set_value(0);
			expander2.set_value(0);
			delay(25);
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