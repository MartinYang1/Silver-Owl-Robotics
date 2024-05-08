#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT19, ratio18_1, false);
motor LM = motor(PORT18, ratio18_1, false);
motor RF = motor(PORT13, ratio18_1, true);
motor RM = motor(PORT12, ratio18_1, true);
motor LB = motor(PORT14, ratio18_1, false);
motor RB = motor(PORT15, ratio18_1, true);
motor Roller = motor(PORT6, ratio6_1, false);
digital_out Climb = digital_out(Brain.ThreeWirePort.F);
digital_out Wing = digital_out(Brain.ThreeWirePort.B);
digital_out RightBackWing = digital_out(Brain.ThreeWirePort.H);
motor PU = motor(PORT3, ratio6_1, true);
inertial Gyro = inertial(PORT20);
digital_out LeftBackWing = digital_out(Brain.ThreeWirePort.G);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}