using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LF;
extern motor LM;
extern motor RF;
extern motor RM;
extern motor LB;
extern motor RB;
extern motor Roller;
extern digital_out Climb;
extern digital_out Wing;
extern digital_out RightBackWing;
extern motor PU;
extern inertial Gyro;
extern digital_out LeftBackWing;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );