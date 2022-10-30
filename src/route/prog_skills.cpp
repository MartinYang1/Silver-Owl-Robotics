#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

vector center2 = {};

void prog_skills() {
    // initial setup
    unsigned timeElapsed = 0;
    unsigned shootSpeed = 3400;
    setup_robot(timeElapsed, center2, shootSpeed);
    delay(800);
}