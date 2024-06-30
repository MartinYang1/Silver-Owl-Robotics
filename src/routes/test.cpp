#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void test() {
    // declare initial conditions
    //PIDDataSet TestPara={4,0.1,0.2};
    PIDDataSet TestPara={1.5,0.1,0.15};
    MoveEncoderPID(TestPara, 100, 36 , 0.4,0,true);
    MoveEncoderPID(TestPara, 30, 10, 0.4,0,true);
    Clamp.set(false);
    wait(200,msec);
    MoveEncoderPID(TestPara, 100, 0.2, 0.4,0, true);
    Tilt.set(false);
    MoveEncoderPID(TestPara, 100, 5, 0.4, 0, true);
    TurnMaxTimePID(TestPara, -100, 0.9, true);
    RunRoller(-100);
    //wait(1000,msec);
    MoveEncoderPID(TestPara, -100, 24, 0.5, -100, true);
    TurnMaxTimePID(TestPara, 40, 0.9, true);
    Pistake.set(true);
    MoveEncoderPID(TestPara, -100, 60, 0.4, 40, true);
    Pistake.set(false);
    /*MoveEncoderPID(TestPara, 100 , 65 ,0.4,0,true);
    TurnMaxTimePID(TestPara, 90, 0.4, true);
    MoveEncoderPID(TestPara, 100 , 50 ,0.4,90,true);
    wait(1000,msec);
    MoveEncoderPID(TestPara, -100 , 90 ,0.4,90,true);
        MoveEncoderPID(TestPara, -100 , 90 ,0.4,0,true);*/

    // // moves forward
    // MoveEncoderPID(TestPara, -100 , 24 ,0.2,0,true);
    // // turns to 90 degrees, 0.4s for calculations, brake when heading reached
    // TurnMaxTimePID(TestPara, 90, 0.4, true);
    // // Move backwards at 80 power, 10 inches, 0.2s to max speed, 
    // MoveEncoderPID(TestPara, 80 , 10 ,0.2,90,true);
    // // Turn to 60 degrees, 0.4s for calculations, braking
    // TurnMaxTimePID(TestPara, 0, 0.4, true);
    // // Move foward at 50 power, for 10 inches, 0.2 to accelerate to max speed, absolute heading, braking
    // MoveEncoderPID(TestPara, -50 , 10 ,0.2,60,true);

    //MoveEncoderPID(TestPara, 100 , 560 ,0.2,0,true);
}
void test2(){  
    
     PIDDataSet TestPara={1.5,0.1,0.15};
    MoveEncoderPID(TestPara, 100, 12, 0.4, 0, true);
    TurnMaxTimePID(TestPara, 30, 0.5,true);
    MoveEncoderPID(TestPara, 100, 13, 0.4, 30, true);
    MoveEncoderPID(TestPara, 40, 13, 0.4, 30, true);
    Clamp.set(false);
    wait(200,msec);
    MoveEncoderPID(TestPara, 100, 0.2, 0.4,30, true);
    Tilt.set(false);
    MoveEncoderPID(TestPara, 100, 3, 0.4,30, true);
    TurnMaxTimePID(TestPara, -84, 0.8, true);
    RunRoller(-100);
    MoveEncoderPID(TestPara, -100, 25, 0.4,-84, true);
    TurnMaxTimePID(TestPara,60, 0.5, true);
    Pistake.set(true);
    MoveEncoderPID(TestPara, -100, 60, 0.4, 60, true);
    Pistake.set(false);
    wait(500,msec);
    MoveEncoderPID(TestPara, 100, 10, 0.4, 60, true);
    TurnMaxTimePID(TestPara, -12, 0.9, true);
    MoveEncoderPID(TestPara, 100, 23, 0.4, -12, false);

}