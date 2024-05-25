/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//#include "STDLib.cpp"
#include "vex.h"

#include "screen_gui.hpp"
#include "movement.hpp"
#include "routes/routes.hpp"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

bool SP;
void pre_auton(void) {
  PX=0;
  JX=0;
  ASV=0;
  SP=false;
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
Gyro.calibrate();

//Ensure Robot Launch Position is set before auto proceeds, once plugged into field control,
//start program and do not temper bot under all circumstances

//1. IF ANY ADJUSTMENT IS NEEDED, QUIT PROGRAM, THEN ADJUST, RESTART PROGRAM AFTER ADJUSTMENTS COMPLETED
//2. DO NOT START PROGRAM BEFORE PLUGGING IN FIELD CONTROL, THIS MAY DISABLE AUTO
//3. ONLY SIGNAL JUDGES TO BEGIN MATCH AFTER THE ZEROING PROMPT ON SCREEN HAS CLEARED

//Print precautionary message
Brain.Screen.drawRectangle(0,0,500,500);

Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(2,10);
Brain.Screen.print("FLIR TIMEOUT");


waitUntil(!Gyro.isCalibrating());


Zeroing(true,true);
DisplayASL();
DisplayWords();

bool EXIT=false;
while(!EXIT)
{
if(Brain.Screen.xPosition()<100)
{
if(Brain.Screen.yPosition()<75&&Brain.Screen.yPosition()>25)ASV=1;
else if(Brain.Screen.yPosition()<150&&Brain.Screen.yPosition()>100)ASV=3;
else if(Brain.Screen.yPosition()<225&&Brain.Screen.yPosition()>175)ASV=5;
}
else if(Brain.Screen.xPosition()>375)
{
if(Brain.Screen.yPosition()<75&&Brain.Screen.yPosition()>25)ASV=2;
else if(Brain.Screen.yPosition()<150&&Brain.Screen.yPosition()>100)ASV=4;
else if(Brain.Screen.yPosition()<225&&Brain.Screen.yPosition()>175)ASV=6;
}

if(Brain.Screen.xPosition()>187&&Brain.Screen.xPosition()<287)
{
if(Brain.Screen.yPosition()<55&&Brain.Screen.yPosition()>5)EXIT=true;
else if(Brain.Screen.yPosition()>125&&Brain.Screen.yPosition()<225)ASV=7;
}

if(Brain.Screen.pressing()&&!SP) UpdateDynamic();

SP=Brain.Screen.pressing();

}

Brain.Screen.clearScreen();
if(ASV==1){
  Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("GOAL SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("6 BALL");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#39FF14");

}

if(ASV==2){
Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("MATCHLOAD");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("StealAWP");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#39FF14");
}

if(ASV==3){

Brain.Screen.setFillColor(black);

    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("GOAL SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("5 BALL");
Brain.Screen.setFont(monoM);  
  Brain.Screen.setFillColor("#39FF14");
}

if(ASV==4){

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("MATCHLOAD");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("Elim-Steal");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

}

if(ASV==5){

Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("GOAL SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("GS-AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

}

if(ASV==6){
  
  Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("MATCHLOAD");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("ONLY AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

  }

if(ASV==7){

Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("SKILLS");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("SKILLS");
Brain.Screen.setFont(monoM); 
Brain.Screen.setFillColor("#39FF14");

}


Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(5,10);
Brain.Screen.print("AUTO CONFIRMED");



  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  /*int LGV;
  int ABSHDG=60;
  Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5,17);
    ChassisDataSet TCDS;
    while(true){
      TCDS=ChassisUpdate();
          Brain.Screen.setCursor(5,20);
        Brain.Screen.print("%d-------------",(int)LGV);
   LGV=TCDS.HDG-ABSHDG;
  if(LGV>180) LGV=LGV-360;
    }*/
  

//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

//Do not change the below
PIDDataSet TestPara={4,0.1,0.2};
Zeroing(true,true);



//can start editing if nessary
if(ASV==1)//Quali close 6 triball auto 
{
  test();
}

if(ASV==2)// awp mid steal
{
  RunRoller(-100);
  wait(70,msec);
  RunRoller(100);
  MoveEncoderPID(TestPara, -100 , 22 ,0.2 ,12,true);
  wait(100,msec);
  RunRoller(0);
  MoveEncoderPID(TestPara, 100 , 400 ,0.2 ,10,true);
  TurnMaxTimePID(TestPara, 45, 0.2, true);
  MoveEncoderPID(TestPara, 100 , 280 ,0.2 ,45,true);
  TurnMaxTimePID(TestPara, -44, 0.3, true);
  MoveEncoderPID(TestPara, -100 , 90 ,0.2 ,-44,true);
  TurnMaxTimePID(TestPara, -40, 0.3, true);
  LeftBackWing.set(true);
  RightBackWing.set(true);
  MoveEncoderPID(TestPara, 100 , 280 ,0.2 ,-40,true);
  LeftBackWing.set(false);
  RightBackWing.set(false);
  TurnMaxTimePID(TestPara, -179, 0.3, true);
  TurnMaxTimePID(TestPara, 100, 0.3, true);
  RunRoller(-100);
  MoveEncoderPID(TestPara, -100 , 490 ,0.2 ,95,true);
  TurnMaxTimePID(TestPara, 91, 0.3, true);
  wait(1,sec);
  RunRoller(0);

}

if(ASV==3)// 5 Ball rush
{
  RunRoller(-100);
  wait(80,msec);
  RunRoller(100);
  MoveEncoderPID(TestPara, -100 , 840 ,0.2 ,-12,true);
  MoveEncoderPID(TestPara, 100 , 850 ,0.2 ,-12,true);
  RunRoller(0);
  RunRoller(-100);
  TurnMaxTimePID(TestPara, 55, 0.2, true);
  wait(300,msec);
  RunRoller(100);
  MoveEncoderPID(TestPara, -100 , 500 ,0.2 ,-90,true);
  MoveEncoderPID(TestPara, 100 , 600 ,0.2 ,-90,true);
  TurnMaxTimePID(TestPara, -135, 0.2, true);
  RightBackWing.set(true);
  MoveEncoderPID(TestPara, 100 , 300 ,0.2 ,-141,true);
  RightBackWing.set(false);
  RunRoller(0);
  MoveTimePID(TestPara,100 , 1.2 ,0.3,-168,true);
  MoveEncoderPID(TestPara, -100 , 150,0.2 ,-179,true);
  MoveTimePID(TestPara,-100 , 1.3 ,0.3,13,true);
  MoveEncoderPID(TestPara, 100 , 170,0.2 ,0,true);
  RunRoller(100);
  MoveEncoderPID(TestPara,-100 , 850 ,0.3,-80,true);//turn and grab first field ball
  TurnMaxTimePID(TestPara,165,0.5,true);
  RunRoller(-100);
} 

if(ASV==4)// Elim-Steal
{
  RunRoller(-100);
  wait(90,msec);
  RunRoller(100);
  MoveEncoderPID(TestPara, -100 , 765 ,0.2 ,12,true);
  wait(100,msec);
  MoveEncoderPID(TestPara, 100 , 400 ,0.2 ,10,true);
  TurnMaxTimePID(TestPara, 45, 0.2, true);
  MoveEncoderPID(TestPara, 100 , 400 ,0.2 ,45,true);
  TurnMaxTimePID(TestPara, -43, 0.3, true);
  MoveEncoderPID(TestPara, -100 , 200 ,0.2 ,-43,true);
  RightBackWing.set(true);
  MoveEncoderPID(TestPara, 100 , 250 ,0.2 ,-43,true);
  RightBackWing.set(false);
  TurnMaxTimePID(TestPara, -179, 0.3, true);
  TurnMaxTimePID(TestPara, 95, 0.3, true);
  RunRoller(-100);
  MoveEncoderPID(TestPara, -100 , 550 ,0.2 ,95,true);
  MoveEncoderPID(TestPara, 100 , 540 ,0.2 ,95,true);
  TurnMaxTimePID(TestPara, 130, 0.3, true);
  MoveEncoderPID(TestPara, 100 , 100 ,0.2 ,130,true);
  RunRoller(0);
  RightBackWing.set(true);
  
}

if(ASV==5)// empty
{
   //test();
}


if(ASV==6)//AWP only
{
  RunRoller(-100);
  wait(50,msec);
  RunRoller(100);
  MoveEncoderPID(TestPara, -100 , 530 ,0.3,0,true); 
  TurnMaxTimePID(TestPara,-37,0.3,true);
  RunRoller(-100);
  wait(200,msec);
  TurnMaxTimePID(TestPara,0,0.3,true);
  MoveEncoderPID(TestPara, 100 , 330 ,0.3,0,true); 
  TurnMaxTimePID(TestPara,45,0.3,true);
  MoveEncoderPID(TestPara, 100 , 170 ,0.3,45,true);
  TurnMaxTimePID(TestPara,-44,0.3,true);
  MoveEncoderPID(TestPara, -100 , 280 ,0.3,-44,true);
  TurnMaxTimePID(TestPara,-41,0.3,true);
  RightBackWing.set(true);
  MoveEncoderPID(TestPara, 100 , 240 ,0.3,-41,true);
  RightBackWing.set(false);
  TurnMaxTimePID(TestPara,-179,0.3,true);
  TurnMaxTimePID(TestPara,95,0.3,true);
  MoveEncoderPID(TestPara, -100 , 540 ,0.3,95,true); 
}


if(ASV==7)//temporary prog skills
{ 
  RunRoller(-100);
  TurnMaxTimePID(TestPara, 20, 0.3, true);
  MoveTimePID(TestPara, 100, 0.9 , 0.2, 20, true);
  //above test, below actual
  //MoveEncoderPID(TestPara, 100 , 185 ,0.2,0,true); //push triballs into blue goal 
  //TurnMaxTimePID(TestPara, 40, 0.3, true);
  //MoveTimePID(TestPara, 100, 0.9 , 0.2, 40, true);
  MoveEncoderPID(TestPara, -100 , 145 ,0.2,45,true);
  TurnMaxTimePID(TestPara, -65.7, 0.4, true);
  MoveEncoderPID(TestPara, 23 , 20 ,0.2,-65.7,true);
  RightBackWing.set(true);
  RunRoller(0);
  RunPuncher(100); //matchloading
  //wait(4,sec);
  wait(25.5,sec);
  RightBackWing.set(false);
  RunPuncher(-100); //matchloading finish
  TurnMaxTimePID(TestPara, 10, 0.3, true);
  RunPuncher(0);
  MoveEncoderPID(TestPara, -100, 310 , 0.2, 10, true); //turn face elevation bar
  Wing.set(true);
  MoveEncoderPID(TestPara, -100, 1600 , 0.2, -43, true); //drive under and across
  Wing.set(true);
  PU.setStopping(coast);
  MoveEncoderPID(TestPara, -100, 390 , 0.2, -65, true);
  Wing.set(false);
  MoveTimePID(TestPara, -100, 1, 0.2,-129, true); //side push right
  MoveEncoderPID(TestPara, 100, 150 , 0.2, -136, true);
  RunRoller(-100);
  MoveTimePID(TestPara, -100, 1, 0.7,-129, true); //side push right 2
  RunRoller(100);
  MoveEncoderPID(TestPara, 100, 180 , 0.2, -136, true);
  TurnMaxTimePID(TestPara, 150, 0.4, true);
  MoveEncoderPID(TestPara, -100,720 , 0.2, 150, true);//move to fpr
  MoveEncoderPID(TestPara, 100,110 , 0.2, 45, true);
  RunRoller(0);
  //TurnMaxTimePID(TestPara, 118, 0.3, true); 
  RightBackWing.set(true);
  wait(100,msec);
  MoveTimePID(TestPara, 100, 1.5, 0.2, 118, true);//front push right
  RightBackWing.set(false);
  MoveEncoderPID(TestPara, -100, 500 , 0.2, 118, true);
  MoveEncoderPID(TestPara, 100 ,820 , 0.2, 45, true); //move left for fpl
  //TurnMaxTimePID(TestPara,165, 0.2, true); //turn for front push left
  RightBackWing.set(true);
  MoveTimePID(TestPara, 100, 1.2, 0.2, 145, true); //front push left
  RightBackWing.set(false);
  MoveEncoderPID(TestPara, -100 ,500 , 0.2, -179, true);//move away
  MoveEncoderPID(TestPara, 100 ,555 , 0.2, -136, true); //move to front push mid
  //TurnMaxTimePID(TestPara,135, 0.3, true);
  RightBackWing.set(true);
  MoveTimePID(TestPara, 100, 1.2, 0.2, 135, true); //front push mid
  RightBackWing.set(false);
  RunRoller(100);
  MoveEncoderPID(TestPara, -100 ,240 , 0.2, 135, true);//move to long bar
  MoveEncoderPID(TestPara, -100 ,900 , 0.2, -120, true); //move to left side
  Wing.set(true);
  MoveEncoderPID(TestPara, -100 ,200 , 0.2, -38, true);
  MoveEncoderPID(TestPara, -100 ,150 , 0.2, -10, true);
  Wing.set(false);
  RunRoller(0);
  Climb.set(true);
  MoveTimePID(TestPara, -100, 1.35, 0.2, 29, true);// side push left 
  MoveEncoderPID(TestPara, 100, 200, 0.2, 40, true);
  MoveEncoderPID(TestPara, -100 , 355, 0.2, -179, true);
  MoveTimePID(TestPara, -100, 1.3, 0.2, 130, true);
  Climb.set(false);

}
//MoveTimePID(TestPara, -100, 0.5,0.1,-40,true);//score 2nd triball
//(PID Parameters, motor speed -100 - 100, time for travel 0 - inf, time to accelerate to full speed, Absolute Heading, Braking?)

    // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
CStop();
}
int RV;
int LV;
int DriveTask(void){
  while(true)
  {
    RV=Controller1.Axis3.position(percent)-Controller1.Axis1.position(percent)*turninverse;
    LV=Controller1.Axis3.position(percent)+Controller1.Axis1.position(percent)*turninverse;
    Move(LV,RV);
  }

return 0;
}
int V;
int ATask(void)
{
  double pow;
    while(true)
  {
    pow=((Controller1.ButtonR2.pressing()-Controller1.ButtonR1.pressing())*100);
    RunRoller(-pow);
    
  
  //RunPuncher((Controller1.ButtonB.pressing())*100);
  }
  
  return 0;
}

int JY;
int PY;
int JW,PW;
int PTask(void)
{
    while(true)
    {

    if(PW==0&&Controller1.ButtonB.pressing()&&JW==0)
    {
      JW=1;
      PW=1;
      RunPuncher(100);
    }

    else if(!Controller1.ButtonB.pressing())JW=0;

    else if(PW==1&&Controller1.ButtonB.pressing()&&JW==0)
    {
      JW=1;
      PW=0;
      RunPuncher(0);
    }


    if(PY==0&&Controller1.ButtonL2.pressing()&&JY==0)
    {
      JY=1;
      PY=1;
      RightBackWing.set(true);
      LeftBackWing.set(true);
    }

    else if(!Controller1.ButtonL2.pressing())JY=0;

    else if(PY==1&&Controller1.ButtonL2.pressing()&&JY==0)
    {
      JY=1;
      PY=0;
      RightBackWing.set(false);
      LeftBackWing.set(false);
    }




    if(PX==0&&Controller1.ButtonX.pressing()&&JX==0)
    {
      JX=1;
      PX=1;
      Climb.set(true);
    }

    else if(!Controller1.ButtonX.pressing())JX=0;

    else if(PX==1&&Controller1.ButtonX.pressing()&&JX==0)
    {
      JX=1;
      PX=0;
      Climb.set(false);
    }



    if(PB==0&&Controller1.ButtonL1.pressing()&&JB==0)
    {
      JB=1;
      PB=1;
      Wing.set(true);
    }

    else if(!Controller1.ButtonL1.pressing())JB=0;
    
    else if(PB==1&&Controller1.ButtonL1.pressing()&&JB==0)
    {
      JB=1;
      PB=0;
      Wing.set(false);
    }
    
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    
     

    task Dtask=task(DriveTask);
    task Atask=task(ATask);
    task Ptask=task(PTask);
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//


int main() {
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  
  

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
  