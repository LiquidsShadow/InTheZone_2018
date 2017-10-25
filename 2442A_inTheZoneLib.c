
/*
Sets left drive motors to a power.
@param pwr -	a power
*/
void setLeftMotors(int pwr)
{
	motor[driveLeftBack] = pwr;
	motor[driveRightBack] = pwr;
}
/*
Sets right drive motors to a power.
@param pwr - a power
*/
void setRightMotors(int pwr)
{
	motor[driveRightBack] = pwr;
	motor[driveRightFront] = pwr;
}
/*
Sets both right and left motors to a power
@param pwr - a power
*/
void setAllDriveMotors(int pwr)
{
	setLeftMotors(pwr);
	setRightMotors(pwr);
}
/*
Sets mobile base lift motor(s) to a power.
@param liftPower - a power.
*/
void setMobileBaseLiftPower(int pwr)
{
	motor[mobileBaseLiftLeft] = pwr;
	motor[mobileBaseLiftRight] = pwr;
}
/*
Sets main lift motor(s) to a power
@param liftPower - a power.
*/
void setMainLiftPower(int liftPower)
{
	motor[mainLiftLeft] = -liftPower;
	motor[mainLiftRight] = liftPower;
}
/*
Sets mobile base lift to a position while proportionally decreasing motor power as lift reaches desired position
@param liftPos - a position
*/
void setMobileBaseLiftToPos(int liftPos)
{
	// from last year: used 0.15 for lift

	// MBL - Mobile Base Lift
	int curr = SensorValue[mobileBaseLiftPot];
	int diff = curr - liftPos;
	int pwr = (int) (0.15 * diff);

	while (abs(pwr) >= 5)
	{
		setMobileBaseLiftPower(pwr);

		// update variables
		curr = SensorValue[mobileBaseLiftPot];
		diff = curr - liftPos;
		pwr = (int) (0.15 * diff);
	}
}
/*
Sets main lift to a position while proportionally decreasing motor power as lift reaches desired position
@param liftPos - a position
*/
void setMainLiftToPos(int liftPos)
{
	// ML - Main Lift
	int curr = SensorValue[mainLiftPot];
	int diff = curr - liftPos;
	int pwr = (int) (0.15 * diff);

	while (abs(pwr) >= 5)
	{
		setMainLiftPower(pwr);

		// update variables
		curr = SensorValue[mainLiftPot];
		diff = curr - liftPos;
		pwr = (int) (0.15 * diff);
	}
}
/*
Sets pincer motor(s) to a power
@param pincerPower - power to set the pincer motors to
*/
void setPincerPower(int pincerPower)
{
	motor[leftPincer] = pincerPower;
	motor[rightPincer] = pincerPower;
}
/*
Sets pincer to a position while decreasing motor power
@param pincerPos - a position
*/
void setPincersToPos(int pincerPos)
{
	// from last year: used 0.25 as the conversion factor for pincers
	int curr = SensorValue[pincerPot];
	int diff = pincerPos - curr;
	int pwr = (int) -(0.25 * diff);

	while (abs(pwr) >= 5)
	{
		setPincerPower(pwr);
		curr = SensorValue[pincerPot];
		diff = pincerPos - curr;
		pwr = (int) -(0.25 * diff);
	}
}
/*
Runs user control
*/
void runUserControl()
{


	while(true)
	{
		// Joysticks
		int  rightJoy = vexRT[Ch2]; // right joystick
		int  leftJoy = vexRT[Ch3]; // left joystick
		// Buttons
		word btn8UP = vexRT[Btn8U]; // button raise mobile base lift
		word btn8DOWN = vexRT[Btn8D]; // button to lower mobile base lift
		// Triggers
		word rightTriggerUP = vexRT[Btn6U]; // trigger to raise main lift
		word rightTriggerDOWN = vexRT[Btn6D]; // trigger to lower main lift
		word leftTriggerUP = vexRT[Btn5U]; // trigger to open pincers
		word leftTriggerDOWN = vexRT[Btn5D]; // trigger to close pincers

		// positions for lift/pincer control
		int posMLU = 0; // main lift up : need value here
		int posMLD = 0; // main lift down : need value here
		int posMBLU = 0; // mobile base lift up : need value here
		int posMBLD = 0; // mobile base lift down : need value here
		int posPinO = 0; // pincer open : need value here
		int posPinC = 0; // pincer closed : need value here

		// Drive Control
		if(leftJoy > 15 || leftJoy < -15) //dead zones
		{
			setLeftMotors(leftJoy);
		}
		else
		{
			setLeftMotors(0);
		}

		if(rightJoy > 15 || rightJoy < -15) //dead zones
		{
			setRightMotors(rightJoy);
		}
		else
		{
			setRightMotors(0);
		}


		// Mobile base lift control -> change to proportional set...Pos() when ready; use "set..Power" for testing
		if(btn8UP == 1)
		{
			setMobileBaseLiftPower(127);
			//setMobileBaseLiftToPos(posMBLU);
		}
		else if(btn8DOWN == 1)
		{
			setMobileBaseLiftPower(-127);
			//setMobileBaseLiftToPos(posMBLD);
		}
		else
		{
			setMobileBaseLiftPower(0);
		}

		// Main lift control -> change to proportional set...Pos() when ready; use "set..Power" for testing

		if(rightTriggerUP == 1)
		{
			setMainLiftPower(-127);
			//setMainLiftToPos(posMLU);
		}
		else if(rightTriggerDOWN == 1)
		{
			setMainLiftPower(127);
			//setMainLiftToPos(posMLD);
		}
		else
		{
			setMainLiftPower(0);
		}


		// Pincer control -> change to proportional set...Pos() when ready;1 use "set..Power" for testing

		if(leftTriggerUP == 1)
		{
			setPincerPower(127);
			//setPincersToPos(posPinO);
		}
		else if(leftTriggerDOWN == 1)
		{
			setPincerPower(-127);
			//setPincersToPos(posPinC);
		}
		else
		{
			setPincerPower(0);
		}

	}
}

/*
Runs programming skills
*/
void runProgrammingSkills()
{
}

/*
Runs autonomous
@param - string side
*/
void runAuton(string side)
{
	// can only start this once we have values for movement

	// - side independent -
	// drive forward for a certain amount
	// reverse for a portion of the forwards movement
	// - side dependent -
	// turn to line up robot w/ scoring zone
	// - side independent -
	// drive forward to move mobile base into scoring zone


}
