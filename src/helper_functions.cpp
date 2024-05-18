#include "vex.h"
#include <math.h>

/** Gets the distance travelled in a linear path by the robot
 * 
 * @param degreesTravelled the degrees travelled
 * @return the distance travelled by the motors, in inches
 */
double get_dist_travelled(double degreesTravelled) {
    return degreesTravelled * wheelToMotorRatio / 360 * (M_PI*wheelDiam);
}
