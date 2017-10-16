#pragma config(Sensor, in1,    liftPoten,      sensorNone)
#pragma config(Sensor, in2,    leftClawPoten,  sensorPotentiometer)
#pragma config(Sensor, in3,    rightClawPoten, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftQuad,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightQuad,      sensorQuadEncoder)
#pragma config(Sensor, dgtl10, leftPiston,     sensorDigitalOut)
#pragma config(Sensor, dgtl12, rightPiston,    sensorDigitalOut)
#pragma config(Motor,  port1,           claw2,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           test,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveLeftFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           driveLeftBack, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           driveRightFront, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           driveRightBack, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           forklift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          claw,          tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

#pragma competitionControl(Competition)


#define BCI_USE_TIMER
#define BCI_USE_POS_PID

#include "Vex_Competition_Includes.c"
#include "\InTheZoneLibrary.c"
#include "..\BCI-master\BCI.h"
#include "..\BCI-master\drivingFunctions.c"
#include "..\BCI-master\turningFunctions.c"


void pre_auton()
{

}

task autonomous()

{
    string side = "right";
    //runBasicCompAuton();
    //runProgSkills(side);
}

task usercontrol()
{
    char direction = 1; //controls direction
    bool btnEightRightPressed = false; //tracks if button was pressed

    while(true)
    {

        //Buttons and Joysticks
        int  rightJoy = vexRT[Ch2];
        int  leftJoy = vexRT[Ch3];
        word rightTriggerUp = vexRT[Btn6U]; //for up lift
        word rightTriggerDown = vexRT[Btn6D]; //for down lift
        word leftTriggerUp = vexRT[Btn5U]; //for pincer close
        word leftTriggerDown = vexRT[Btn5D]; //for pincer open
        word btnEightUp = vexRT[Btn8U];
        word btnEightDown = vexRT[Btn8D]; //for lift to set point
        word btnSevenUp = vexRT[Btn7U]; //for folding claws
        word btnSevenD = vexRT[Btn7D]; //180 degrees

        word btnEightRight = vexRT[Btn8R]; //for toggling reverse direction

        if(btnEightRight == 1 && !btnEightRightPressed){ //if button was pressed and was not already being pressed, change sign

            direction = -direction;
            btnEightRightPressed = true;
        }
        else if(btnEightRight == 0 && btnEightRightPressed) //if button is no longer being pressed, update bool
            btnEightRightPressed = false;

        if(fabs(rightJoy) >= 15)
            if(direction==1)
                setRightMotors(rightJoy);
            else
                setLeftMotors(rightJoy);
        else
            if(direction==1)
                setRightMotors(0);
            else
                setLeftMotors(0);

        if(fabs(leftJoy) >= 15)
            if(direction==1)
                setLeftMotors(leftJoy);
            else
                setRightMotors(leftJoy);
        else
            if(direction==1)
                setLeftMotors(0);
            else
                setRightMotors(0);


        //Lift Motors

        if(rightTriggerUp == 1)
            setLiftPower(127);
        else if(rightTriggerDown == 1)
            setLiftPower(-127);
        else
            setLiftPower(0);

        if(btnEightUp == 1)
            setForkliftPower(0);
        else if(btnEightDown == 1)
            setForkliftPower(1);

        //pincer
        if(leftTriggerDown == 1)
            setClawPower(127);
        else if(leftTriggerUp == 1)
            setClawPower(-127);
        else
            setClawPower(0);
    }
}
