#ifndef MOVEMENT_H
#define MOVEMENT_H

struct vector {
    double x = 0, y = 0;
    float dist = 0, heading = 0;
};

extern void move(double leftVolt, double rightVolt);
extern void move_straight(double desiredSpeed, double desiredDist);
extern void turn(double leftVolt, double rightVolt, float desiredAngle);
#endif