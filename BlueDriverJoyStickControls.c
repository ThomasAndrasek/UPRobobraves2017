// Read Buttons to see if any are pushed

// fork has been removed
// int forkSpeed = 0;

task controllerPolling(){
	while(true){
 		if(vexRT[Btn7U] == 1){
			// Turn drive train into strafe mode to enable easier access around the field
			SensorValue[LeftDriver] = 0;
			SensorValue[RightDriver] = 0;
			//strafeMode = !strafeMode;
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

		if(vexRT[Btn8L] == 1){
			SensorValue[in1] = 0;
		}

		if(vexRT[Btn7L] == 1){
			setHeading(0, 127, true);
		}

		if(vexRT[Btn8U] == 1){
			throwerSpeed = 80;
		}
		else if(vexRT[Btn8R]){
			throwerSpeed = -80;
		}

		delay(5);
	}
}

task driving(){
	while(true)
	{
		motor[rightDrive]   = rightDriveSpeed;
		motor[leftDrive]    = leftDriveSpeed;
	}
		delay(5);
}
