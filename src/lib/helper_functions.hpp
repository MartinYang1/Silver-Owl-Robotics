#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

extern inline double get_heading();
extern inline double move_speed();
extern double PID(double input, double target, double Kp, double Ki, double Kd);

#endif