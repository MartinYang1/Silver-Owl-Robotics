#include "main.h"
#include "selection.h"
#include "globals/globals.hpp"
//#include "route/route.hpp"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	imu_sensor.reset();
	pros::lcd::register_btn1_cb(on_center_button);
	selectorInit();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	imu_sensor.reset();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

  switch (autonSelection)
	{
		case S_RED5: //autoroute 2
			auto_route2();
			break;
		case S_BLUE5:
		auto_route2();
			break;
		case S_RED7:
		auto_route1();
		break;
		case S_BLUE7: //autoroute 1
		auto_route1();
		break;
		case S_RED8:
		martin_stupid();
			break;
		case S_BLUE8://programming 
		martin_stupid();
			break;	
		case B_RED3:
		auto_route3();
		break;
		case B_BLUE3:
		auto_route3();
		break;
			
		case B_RED6_C:
		just_shoot();
		case B_BLUE6_C:
		low_shot();
		case SKILLS:
		martin_stupid();
			break;
		case NOTHING:
		blank();

	}

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

