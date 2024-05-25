#include "../movement.hpp"
#include "../helper_functions.hpp"

//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void test() {
    // declare initial conditions
    PIDDataSet TestPara={4,0.1,0.2};

    // moves forward
    MoveEncoderPID(TestPara, -100 , 24 ,0.2,0,true);
    // turns to 90 degrees, 0.4s for calculations, brake when heading reached
    TurnMaxTimePID(TestPara, 90, 0.4, true);
    // Move backwards at 80 power, 10 inches, 0.2s to max speed, 
    MoveEncoderPID(TestPara, 80 , 10 ,0.2,90,true);
    // Turn to 60 degrees, 0.4s for calculations, braking
    TurnMaxTimePID(TestPara, 60, 0.4, true);
    // Move foward at 50 power, for 10 inches, 0.2 to accelerate to max speed, absolute heading, braking
    MoveEncoderPID(TestPara, -50 , 10 ,0.2,60,true);

    //MoveEncoderPID(TestPara, 100 , 560 ,0.2,0,true);
}