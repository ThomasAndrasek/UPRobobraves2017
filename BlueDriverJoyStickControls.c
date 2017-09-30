// Read Buttons to see if any are pushed

// fork has been removed
// int forkSpeed = 0;

task controllerPolling(){
	while(true){
 		if(vexRT[Btn7U] == 1){
			// Turn drive train into strafe mode to enable easier access around the field
			SensorValue[LeftDriver] = 0;
			SensorValue[RightDriver] = 0;
			strafeMode = !strafeMode;
			delay(300);
		}

		if((vexRT[Ch2] > 20) || (vexRT[Ch2] < -20)) {
			rightDriveSpeed = vexRT[Ch2];
		}
		else {
			rightDriveSpeed = 0;
		}
		if((vexRT[Ch3] > 20) || (vexRT[Ch3] < - 20)) {
			leftDriveSpeed = vexRT[Ch3];
		}
		else {
			leftDriveSpeed = 0;
		}

		if(strafeMode	== true){
			rightDriveSpeed = leftDriveSpeed;
			if ((vexRT[Ch1] > 20) || (vexRT[Ch1] < - 20)) {
				strafeSpeed = vexRT[Ch1];
			}
			else {
				strafeSpeed = 0;
			}
		}
		if((vexRT[Ch3Xmtr2] > 20) || (vexRT[Ch3Xmtr2] < - 20)) {
			throwerSpeed = vexRT[Ch3Xmtr2];
		}
		else if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch2Xmtr2] < - 20)) {
			if(vexRT[Ch2Xmtr2] > 0){
				throwerSpeed = 40 + vexRT[Ch2Xmtr2] / 2;
			}
			else {
				throwerSpeed = vexRT[Ch2Xmtr2] / 4;
			}
		}
		else {
			throwerSpeed = 0;
		}
	//	if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch4Xmtr2] < - 20)) {
	//	forkSpeed = vexRT[Ch4Xmtr2];
	//}
	//	else {
	//		forkSpeed = 0;
	//	}

		if(vexRT[Btn5U] == 1)
		{
			slideLeftSpeed = -70;
		}
		else if(vexRT[Btn5D] == 1)
		{
			slideLeftSpeed = -120;
		}
		else if(vexRT[Btn6U] == 1)
		{
			slideLeftSpeed = 70;
		}
		else if(vexRT[Btn6D] == 1)
		{
			slideLeftSpeed = 120;
		}
		else {
			slideLeftSpeed = 0;
		}

		if(vexRT[Btn8L] == 1){
			sensorValue[in1] = 0;
		}

		if(vexRT[Btn7L] == 1){
			setHeading(0, 127, true);
		}

		/*if(vexRT[Btn6UXmtr2] == 1)
		{
			liftSpeed = 127;
		}
		else if(vexRT[Btn6DXmtr2] == 1)
		{
			liftSpeed = -127;
		}

		else {
			liftSpeed = 0;
		} */
		if(vexRT[Btn8U] == 1){
			throwerSpeed = 80;
		}
		else if(vexRT[Btn8R]){
			throwerSpeed = -80;
		}

		if(vexRT[Btn5UXmtr2] == 1){
			startTask(armPositionHigh);
		}
		else if(vexRT[Btn5DXmtr2] == 1){
			startTask(armPositionLow);
		}
	//	if(vexRT[Btn6U] == 1)
	//	{
	//		forkSpeed = 127;
	//	}
	//	else if(vexRT[Btn6D] == 1)
	//	{
	//		forkSpeed = -127;
	//	}
	//	else
	//	{
	//		forkSpeed = 0;
	//	}
		delay(5);
	}
}
// Add driver joystick Controls here
task driving(){
	// PID Variables

			float pid_Kp = .12;
			float pid_Ki = 0.00001;
			float pid_Kd = 0;

			long currentLeftClicks = 0;
			int deltaPower = 0;

			float currentError = 0;
			float sumError = 0;

			long currentRightClicks = 0;

			SensorValue[LeftDriver] = 0;
			SensorValue[RightDriver] = 0;

			int adjustedRightDriveSpeed = 0;
			int adjustedLeftDriveSpeed = 0;

	while(true)
	{
		// Tank Drive Mode
		if(strafeMode == false){
			//Right Drive;
				motor[rightDrive]   = rightDriveSpeed;
				motor[leftDrive]    = leftDriveSpeed;
			//	motor[liftLeft]     = liftSpeed;
			//	motor[liftRight]    = liftSpeed;
				motor[strafeDrive] 	= slideLeftSpeed;
				motor[strafeFront]  = slideLeftSpeed;

				currentLeftClicks = 0;
				currentRightClicks = 0;
				currentError = 0;
				sumError = 0;

				strafeSpeed = slideLeftSpeed;
		}
//In strafeMode
		else {

			currentLeftClicks =  SensorValue[LeftDriver];
			currentRightClicks =  SensorValue[RightDriver] * -1;

			// get error ( targetSpeed - realSpeed )
			currentError = currentLeftClicks - currentRightClicks;
			sumError = sumError + currentError;


			// apply new pid Power (set drive variable) (drive speed)
			deltaPower = ( currentError * pid_Kp ) + (sumError * pid_Ki );

			adjustedLeftDriveSpeed = leftDriveSpeed - deltaPower;
			adjustedRightDriveSpeed = rightDriveSpeed + deltaPower;

			motor[rightDrive] 	= adjustedRightDriveSpeed;
			motor[leftDrive] 		= adjustedLeftDriveSpeed;
			motor[strafeDrive] 	= strafeSpeed;
			motor[strafeFront]  = strafeSpeed;
		}
	}
		delay(5);
}

// End Driver joystick Controls
