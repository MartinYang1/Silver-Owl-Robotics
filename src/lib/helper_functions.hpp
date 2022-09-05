#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

extern const unsigned wheelDiam = 4;    // the diameter of the wheels of the drive train

extern inline double get_dist_travelled();
extern inline double get_heading();
extern inline double move_speed();
extern double PID(double input, double target, double Kp, double Ki, double Kd);

#endif