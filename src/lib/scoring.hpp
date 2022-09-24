#ifndef SCORING_H
#define SCORING_H

extern const unsigned redHue[4]; extern const unsigned blueHue[2];

extern void aim_shot();
extern const unsigned turn_roller(const int rate);
extern void shoot(const unsigned desiredSpeed, bool actuatePiston);

#endif