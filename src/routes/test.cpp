#include "../movement.hpp"
#include "../helper_functions.hpp"

void test() {
    // declare initial conditions
    PIDDataSet TestPara={4,0.1,0.2};

    MoveEncoderPID(TestPara, -100 , 24 ,0.2,0,true);
    TurnMaxTimePID(TestPara, 90, 0.4, true);
    MoveEncoderPID(TestPara, 80 , 40 ,0.2,0,true);
    //MoveEncoderPID(TestPara, 100 , 560 ,0.2,0,true);
}