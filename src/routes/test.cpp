#include "../movement.hpp"
#include "../helper_functions.hpp"

void test() {
    // declare initial conditions
    PIDDataSet TestPara={4,0.1,0.2};

    MoveEncoderPID(TestPara, -100 , 24 ,0.2,0,true);
    TurnMaxTimePID(TestPara, 90, 0.4, true);
    MoveEncoderPID(TestPara, 80 , 10 ,0.2,90,true);
    TurnMaxTimePID(TestPara, 60, 0.4, true);
    MoveEncoderPID(TestPara, -50 , 10 ,0.2,60,true);

    //MoveEncoderPID(TestPara, 100 , 560 ,0.2,0,true);
}