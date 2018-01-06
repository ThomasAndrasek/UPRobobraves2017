// Read Buttons to see if any are pushed

// fork has been removed
// int forkSpeed = 0;

task controllerPolling(){
	while(true){
 		if(vexRT[Btn7U] == 1){
			// Turn drive train into strafe mode to enable easier access around the field
			SensorValue[LeftDriveEncoder] = 0;
			SensorValue[RightDriveEncoder] = 0;
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

		if(vexRT[Btn8L] == 1){
			SensorValue[in1] = 0;
		}

		/*if(vexRT[Btn7L] == 1){
			setHeading(0, 127, true);
		} */

		if(vexRT[Btn8U] == 1){
			if((SensorValue[dgtl2] != 0) && (SensorValue[dgtl3] != 0)) {
				armSpeedRight = 127;
			}
		}
		else if(vexRT[Btn8R]){
			if((SensorValue[dgtl2] != 0) && (SensorValue[dgtl3] != 0)) {
				armSpeedRight = 127;
			}
		}
		else
		{
			armSpeedRight = 0;
		}

		if( vexRT[Btn8UXmtr2] == 1 )
		{
			armPosition = 0;
			elbowPosition = -180;
		}

		if ( vexRT[Btn8RXmtr2] == 1 )
		{
			armPosition = 340;
			elbowPosition = -70;
		}

		if ( vexRT[Btn8DXmtr2] == 1 )
		{
			armPosition = 340;
			elbowPosition = -30;
		}

		if( vexRT[Btn8LXmtr2] == 1 )
		{
			armPosition = 10;
			elbowPosition = -30;
		}

		if ( vexRT[Btn7UXmtr2] == 1 )
		{
			elbowPosition = -190;
			coneIntakeSpeed = 80;
			elbowPosition = -170;
		}

		if(vexRT[Btn6U]) {
			coneIntakeSpeed = 127;
		}
		else if(vexRT[Btn5U]) {
			coneIntakeSpeed = -127;
		}
		else {
			coneIntakeSpeed = 0;
		}

		if(vexRT[Btn6UXmtr2]) {
			coneIntakeSpeed = 127;
		}
		else if(vexRT[Btn5UXmtr2]) {
			coneIntakeSpeed = -127;
		}
		else {
			coneIntakeSpeed = 0;
		}

		if( vexRT[Btn6D] )
		{
			lifterSpeed = 127;
		}
		else if( vexRT[Btn6U] )
		{
			lifterSpeed = -127;
		}
		else if( vexRT[Btn6DXmtr2] )
		{
			lifterSpeed = 127;
		}
		else if( vexRT[Btn5DXmtr2] )
		{
			lifterSpeed = -127;
		}
		else {
			lifterSpeed = 0;
		}

		if ( vexRT[Btn8UXmtr2] )
		{
			intakeElbowSpeed = 127;
		}
		else if ( vexRT[Btn8DXmtr2] )
		{
			intakeElbowSpeed = -127;
		}
		else
		{
			intakeElbowSpeed = 0;
		}

		if((vexRT[Ch3Xmtr2] > 20) || (vexRT[Ch3Xmtr2] < - 20)) {
			intakeElbowSpeed = vexRT[Ch3Xmtr2];
		}
		else
		{
			intakeElbowSpeed = 0;
		}

		if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch2Xmtr2] < - 20)) {
			armSpeedRight = vexRT[Ch2Xmtr2];
		}
		else {
			armSpeedRight = 0;
		}

		delay(5);
	}
}

task driving(){
	while(true)
	{
		motor[rightDrive]  = rightDriveSpeed;
		motor[leftDrive]   = leftDriveSpeed;
		motor[LifterLeft]  = lifterSpeed;
		motor[LifterRight] = lifterSpeed;
		motor[ConeIntake]  = coneIntakeSpeed;
		motor[ArmLeft]     = armSpeedLeft;
		motor[ArmRight]    = armSpeedRight;
		motor[intakeElbow] = intakeElbowSpeed;
	}
		delay(5);
}
