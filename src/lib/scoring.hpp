#ifndef SCORING_H
#define SCORING_H

extern const unsigned blueHue;  // the hue of the roller's blue side, detected by the optical sensor
extern const unsigned redHue;  // the hue of the roller's red side, detected by the optical sensor

extern void aim_shot();
extern const unsigned turn_roller(const int rate);
#endif