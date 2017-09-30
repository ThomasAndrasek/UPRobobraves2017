// Read Buttons to see if any are pushed

bool strafeMode = false;

int strafeSpeed = 0;
int rightDriveSpeed = 0;
int leftDriveSpeed = 0;
int throwerSpeed = 0;

task controllerPolling(){
	while(true){
 		if(vexRT[Btn7U] == 1){
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
			throwerSpeed = vexRT[Ch3];
		}
		else {
			throwerSpeed = 0;
		}

		if(
			// Turn drive train into strafe mode to enable easier access around the field
			vexRT[Btn5U] == 1)
		{
			throwerSpeed = 127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			throwerSpeed = -127;
		}
		else
		{
			throwerSpeed = 0;
		}
		delay(5);
	}
}
// Add driver joystick Controls here
task driving(){

	// PID Variables

			float pid_Kp = .12;
			float pid_Ki = .00001;
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
		motor[leftThrow] = throwerSpeed;
		motor[rightThrow] = throwerSpeed;
		// Tank Drive Mode
		if(strafeMode == false){
			//Right Drive;
				motor[rightDrive] 	= rightDriveSpeed;
				motor[leftDrive] 		= leftDriveSpeed;
				sumError = 0;
		}
//In strafeMode
		else {

			// PID Logic

			currentLeftClicks =  SensorValue[LeftDriver];
			currentRightClicks =  SensorValue[RightDriver];

			// get error ( targetSpeed - realSpeed )
			currentError = currentLeftClicks - currentRightClicks;
			sumError = sumError + currentError;


			// apply new pid Power (set drive variable) (drive speed)
			deltaPower = ( currentError * pid_Kp ) + (sumError * pid_Ki );

			adjustedLeftDriveSpeed = leftDriveSpeed - deltaPower;
			adjustedRightDriveSpeed = rightDriveSpeed + deltaPower;


			//writeDebugStreamLine("***** Drive Loop ******");
			motor[rightDrive] 	= adjustedRightDriveSpeed;
			motor[leftDrive] 		= adjustedLeftDriveSpeed;
			motor[strafeDrive] 	= strafeSpeed;
			motor[strafeFront]  = strafeSpeed;
		}
	}
		delay(5);
}
// End Driver joystick Controls
