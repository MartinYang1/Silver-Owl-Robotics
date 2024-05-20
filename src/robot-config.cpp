#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT11, ratio6_1, true);
motor LM = motor(PORT12, ratio6_1, true);
motor RF = motor(PORT20, ratio6_1, false);
motor RM = motor(PORT19, ratio6_1, false);
motor LB = motor(PORT15, ratio6_1, true);
motor RB = motor(PORT18, ratio6_1, false);
motor Roller = motor(PORT6, ratio6_1, false);
digital_out Climb = digital_out(Brain.ThreeWirePort.F);
digital_out Wing = digital_out(Brain.ThreeWirePort.B);
digital_out LeftBackWing = digital_out(Brain.ThreeWirePort.H);
motor PU = motor(PORT3, ratio6_1, true);
inertial Gyro = inertial(PORT5);
digital_out RightBackWing = digital_out(Brain.ThreeWirePort.G);
motor Roller2 = motor(PORT4, ratio18_1, true);
digital_out SideHang = digital_out(Brain.ThreeWirePort.E);

// Important variables
const double wheelDiam = 2.75;
const double wheelToMotorRatio = 48.0/36;

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