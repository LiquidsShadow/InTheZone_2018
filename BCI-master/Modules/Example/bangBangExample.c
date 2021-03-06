#pragma config(Sensor, dgtl7,  myQuad,  sensorQuadEncoder)
#pragma config(Motor,  port2,   myMotor, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * This is a tuorial for how to use the basic features of bangBang. For
 * extra reference, see BCI\Modules\Core\bangBang.h
 */

//We will have a quadrature encoder for the bangBang controller to run off of and a
//motor to control the robot

#define BCI_USE_BANGBANG
#include "..\..\BCI.h"

bangBang myBB; //Make a bangBang controller

task main()
{
  //Initialize our bangBang controller with sensor myQuad and gains
  //high power = 127, low power = 80
  bangBang_InitController(&myBB, myQuad, 127, 80);

  //Set the target position for our bangBang controller
  bangBang_SetTargetVelocity(&myBB, 10);

  //Run our motor with the output of the bangBang controller
  motor[myMotor] = bangBang_StepController(&myBB);
}
