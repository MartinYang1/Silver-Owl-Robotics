#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

extern const unsigned wheelDiam;    // the diameter of the wheels of the drive train
extern const double motorToWheelRatio;    // the gear ratio of the motor to the drive train wheel
extern double get_dist_travelled();
extern double get_heading();
extern double get_move_speed();
extern double get_move_voltage();
extern double PID(double input, double target, double Kp, double Ki, double Kd, int direction = 1);

#endif