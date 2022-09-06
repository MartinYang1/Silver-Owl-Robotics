#ifndef MOVEMENT_H
#define MOVEMENT_H

struct vector {
    double x = 0, y = 0;
    float dist = 0, heading = 0;
};

extern void move(const int leftVolt, const int rightVolt);
extern void move_straight(const int desiredSpeed, double desiredDist);
extern void move_straight(const unsigned time);
extern void turn(double leftVolt, double rightVolt, float desiredAngle);
#endif