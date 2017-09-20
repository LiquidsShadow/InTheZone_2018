
#pragma config(Sensor, in1,    liftPoten,      sensorNone)
#pragma config(Sensor, in2,    leftClawPoten,  sensorPotentiometer)
#pragma config(Sensor, in3,    rightClawPoten, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           pincer,        tmotorVex393_HBridge, openLoop)
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

#include "Vex_Competition_Includes.c"

void setLeftDrivePower(int power)
{
    motor[driveLeftFront] = sign;
    motor[driveLeftBack] = sign;
}
void setRightDrivePower(int powe)
{
    motor[driveRightFront] = sign;
    motor[driveRightBack] = sign;
}

void setLiftPower(int power)
{
    motor[liftLeft] = power;
    motor[liftRight] = power;
}

void setForkliftPower(int power)
{
    motor[forklift] = power;
}

void setClawPower(int power)
{
    motor[claw] = power;
}

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
    bool pinpointDrive = false;
    while(true)
    {
        int setPoint = 3000;
        
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
        
        word btnSixU = vexRTBtn6U]; //for toggling reverse direction
        int sign = 1; //controls direction
        bool btnSixUPressed = false; //tracks if button was pressed
        
        
        if(btnSixD == 1 && !btnSixUPressed){ //if button was pressed and was not already being pressed, change sign
            sign = -sign;
            btnSixUPressed = true;
        }
        else if(btnSixU == 0 && btnSixUPressed) //if button is no longer being pressed, update bool
            btnSixUPressed = false;
        
        if(fabs(rightJoy) >= 15)
            setRightDrivePower(sign*rightJoy);
        else
            setRightDrivePower(0, sign);
        
        if(fabs(leftJoy) >= 15)
            setLeftDrivePower(sign*leftJoy);
        else
            setLeftDrivePower(0, sign);
        
        
        //Lift Motors
        
        if(rightTriggerUp == 1)
            setLiftPower(127);
        else if(rightTriggerDown == 1)
            setLiftPower(-127);
        else
            setLiftPower(0);
        
        if(btnEightUp == 1)
            setForkliftPower(127);
        else if(btnEightDown == 1)
            setForkliftPower(-127);
        else
            setForkliftPower(0);
        
        //pincer
        if(leftTriggerDown == 1)
            setClawPower(127);
        else if(leftTriggerUp == 1)
            setClawPower(-127);
        else
            setClawPower(0);
    }
}