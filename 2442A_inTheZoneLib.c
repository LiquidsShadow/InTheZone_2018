const float ML_CONV = 0.15; // Main Lift Conversion
const float MBL_CONV = 0.15; // Mobile Base Lift Conversion
const float PINC_CONV = 0.25; // Pincer Conversion
const float DRIVE_CONV_R = 0.75; // Right Drive Conversion
const float DRIVE_CONV_L = 0.9; // Left Drive Conversion

enum DEAD_ZONES { DRIVE_EN = 10, LIFT_PWR = 5, PINC_PWR = LIFT_PWR, JOY = 15 }; // Dead zones for drive, lifts, and pincers
enum CTRL_POS {MLU = 0, MLD = 0, MBLU = 0, MBLD = 0, PIN_O = 0, PIN_C = 0}; // Control positions for lifts and pincers

/*
Sets left drive motors to a power.
@param pwr -	a power
*/
void setLeftMotors(int pwr)
{
	motor[driveLeftBack] = pwr;
	motor[driveLeftFront] = pwr;
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
Drives for a distance:
@param ticks - distance in encoder ticks
- If ticks < 0 => reverse
- If ticks > 0 => forwards
*/
void driveDist(int ticks)
{
	int maxPwr = 127; // will be proportionally decreased as robot approaches destination

	if (sgn(ticks) == -1) // if ticks is negative => set negative motor power
		maxPwr *= -1;

	const int START_EN_L = SensorValue[leftQuad]; // left encoder start
	const int START_EN_R = SensorValue[rightQuad]; // right encoder start
	const int END_EN_L = START_EN_L + ticks; // end encoder value
	const int END_EN_R = START_EN_R + ticks; // end encoder value

	float distR = END_EN_R - SensorValue[rightQuad]; // distance to travel (right)
	float distL = END_EN_L - SensorValue[leftQuad]; // distance to travel (left)

	bool EnR_atDestination = fabs(distR) <= (float) DRIVE_EN; // state of being at destination (right)
	bool EnL_atDestination = fabs(distL) <= (float) DRIVE_EN; // state of being at destination (left)

	/*
	While the robot has not reached its destination:

	- update loop variables
	- proportionally decrease motor power
	*/
	do
	{
		if(!EnR_atDestination)
		{
			distR = END_EN_R - SensorValue[rightQuad];
			setRightMotors((distR/END_EN_R) * maxPwr * DRIVE_CONV_R);
		}
		if(!EnL_atDestination)
		{
			distL = END_EN_L - SensorValue[leftQuad];
			setLeftMotors((distL/END_EN_L) * maxPwr * DRIVE_CONV_L);
		}

		EnR_atDestination = fabs(distR) <= (float) DRIVE_EN;
		EnL_atDestination = fabs(distL) <= (float) DRIVE_EN;
	}
	while (!EnR_atDestination && !EnL_atDestination);

	setAllDriveMotors(0); // clean
}
/*
Turns the robot by an angle
- If ticks < 0 => turn left
- If ticks > 0 => turn right
*/
void turn(int ticks)
{
	int maxPwr = 127; // will be proportionally decreased as robot approaches destination

	const int START_EN_L = SensorValue[leftQuad]; // left encoder start
	const int START_EN_R = SensorValue[rightQuad]; // right encoder start
	const int END_EN_L = START_EN_L + ticks; // end encoder value
	const int END_EN_R = START_EN_R + ticks; // end encoder value

	float distR = END_EN_R - SensorValue[rightQuad]; // distance to travel (right)
	float distL = END_EN_L - SensorValue[leftQuad]; // distance to travel (left)

	bool EnR_atDestination = fabs(distR) <= (float) DRIVE_EN; // state of being at destination (right)
	bool EnL_atDestination = fabs(distL) <= (float) DRIVE_EN; // state of being at destination (left)

	do
	{
		if (!EnL_atDestination)
		{
			if (sgn(ticks) == -1) {

			}
			else {

			}

			distL = END_EN_L - SensorValue[leftQuad];
			EnL_atDestination = fabs(distL) <= (float) DRIVE_EN;
		}
		if (!EnR_atDestination)
		{
			if (sgn(ticks) == -1)	{

			}
			else {

			}

			distR = END_EN_R - SensorValue[rightQuad];
			EnR_atDestination = fabs(distR) <= (float) DRIVE_EN;
		}
	}
	while (!EnR_atDestination && !EnL_atDestination);

	setAllDriveMotors(0);
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
	int pwr = 0;

	do
	{
		// update variable & use temps
		int curr = SensorValue[mobileBaseLiftPot];
		int diff = curr - liftPos;
		pwr = (int) (MBL_CONV * diff);

		setMainLiftPower(pwr);
	}
	while (fabs(pwr) >= (float) LIFT_PWR);
}
/*
Sets main lift to a position while proportionally decreasing motor power as lift reaches desired position
@param liftPos - a position
*/
void setMainLiftToPos(int liftPos)
{
	int pwr = 0;

	do
	{
		// update variables
		int curr = SensorValue[mainLiftPot];
		int diff = curr - liftPos;
		pwr = (int) (ML_CONV * diff);

		setMainLiftPower(pwr);
	}
	while (fabs(pwr) >= (float) LIFT_PWR);
}
/*
Sets pincer motor(s) to a power
@param pincerPower - power to set the pincer motors to
*/
void setPincerPower(int pincerPower)
{
	motor[pincers] = pincerPower;
}
/*
Sets pincer to a position while decreasing motor power
@param pincerPos - a position
*/
void setPincersToPos(int pincerPos)
{
	int pwr = 0;

	do
	{
		// update variables
		int curr = SensorValue[mainLiftPot];
		int diff = curr - pincerPos;
		pwr = (int) (PINC_CONV * diff);

		setPincerPower(pwr);
	}
	while (fabs(pwr) >= (float) PINC_PWR);
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

		// Drive Control
		if(fabs(leftJoy) > (float) JOY) {
			setLeftMotors(leftJoy);
		}
		else {
			setLeftMotors(0);
		}

		if(fabs(rightJoy) > (float) JOY) {
			setRightMotors(rightJoy);
		}
		else {
			setRightMotors(0);
		}

		// Mobile base lift control -> change to proportional set...Pos() when ready; use "set..Power" for testing
		if(btn8UP == 1) {
			setMobileBaseLiftPower(127);
			//setMobileBaseLiftToPos(posMBLU);
		}
		else if(btn8DOWN == 1) {
			setMobileBaseLiftPower(-127);
			//setMobileBaseLiftToPos(posMBLD);
		}
		else {
			setMobileBaseLiftPower(0);
		}

		// Main lift control -> change to proportional set...Pos() when ready; use "set..Power" for testing

		if(rightTriggerUP == 1) {
			setMainLiftPower(-127);
			//setMainLiftToPos(posMLU);
		}
		else if(rightTriggerDOWN == 1) {
			setMainLiftPower(127);
			//setMainLiftToPos(posMLD);
		}
		else {
			setMainLiftPower(0);
		}

		// Pincer control -> change to proportional set...Pos() when ready;1 use "set..Power" for testing
		if(leftTriggerUP == 1) {
			setPincerPower(127);
			//setPincersToPos(posPinO);
		}
		else if(leftTriggerDOWN == 1) {
			setPincerPower(-127);
			//setPincersToPos(posPinC);
		}
		else {
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
