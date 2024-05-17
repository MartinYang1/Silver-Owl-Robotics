struct PIDDataSet{
  double kp;
  double ki;
  double kd;
};

void test() {
    // declare initial conditions
    PIDDataSet TestPara={4,0.1,0.2};

    MoveEncoderPID(TestPara, 100 , 560 ,0.2,0,true);
    //MoveEncoderPID(TestPara, 100 , 560 ,0.2,0,true);
}