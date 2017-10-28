void lineFollow(bool firstLoop) {
	outerCurrentLineError = 0;
	innerCurrentLineError = 0;
	if(SensorValue[lineFollowerOuter] < SensorValue[lineFollowerCenter]){
		outerCurrentLineError = (SensorValue[lineFollowerCenter] - SensorValue[lineFollowerOuter]);
	}
	if(SensorValue[lineFollowerInner] < SensorValue[lineFollowerCenter]){
		innerCurrentLineError = (SensorValue[lineFollowerCenter] - SensorValue[lineFollowerInner]) * -1;
	}
	if(firstLoop == true){
		lineSumError = 0;
	}

	currentLineError = outerCurrentLineError + innerCurrentLineError;
	lineSumError = lineSumError + currentLineError;
	lineDeltaPower = ( currentLineError * PID_KP_LINE ) + (lineSumError * PID_KI_LINE );

	rightDriveSpeed = lineDeltaPower;
}

// reeeeeeeeeeeeeeeeeeee
// =(

bool findLine(int oRightDriveSpeed, int mLoopCounter){
	bool foundLine = false;

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	int loopCounter = 0;

	if(foundLine == false) {
		while((foundLine == false) && (loopCounter < mLoopCounter * 4)){
			if(loopCounter < mLoopCounter){
				rightDriveSpeed = oRightDriveSpeed;
			}
			else if(loopCounter < mLoopCounter * 3){
				rightDriveSpeed = oRightDriveSpeed * -1;
			}
			else {
				rightDriveSpeed = oRightDriveSpeed;
			}
			if((SensorValue[lineFollowerCenter] + 1000 < SensorValue[lineFollowerInner]) && (SensorValue[lineFollowerCenter] + 1000 < SensorValue[lineFollowerOuter])){
				foundLine = true;
				rightDriveSpeed = 30 * sgn(oRightDriveSpeed) * -1;
				delay(100);
			}
			loopCounter = loopCounter + 1;
			delay(3);
		}
	}
	return foundLine;
}

// =(

void driveForward(int distanceCM, int targetSpeed, bool brake, int lineFollower){
	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	leftDriveSpeed = 25 * sgn(distanceCM);
	rightDriveSpeed = 25 * sgn(distanceCM);

	delay(100);

	leftDriveSpeed = targetSpeed * sgn(distanceCM);
	rightDriveSpeed = targetSpeed * sgn(distanceCM);

	int targetClicks = distanceCM * 11;

	bool firstLoop = true;

	// Wait until distance is traveled
	while(abs(SensorValue[LeftDriver]) < abs(targetClicks)){
		if(lineFollower == 1){
			lineFollow(true);
			firstLoop = false;
		}
		delay(2);
	}
	//brake, then coast
	if(brake == true) {

		leftDriveSpeed = -10 * sgn(distanceCM);
		rightDriveSpeed = -10 * sgn(distanceCM);

		delay(100);
	}
	leftDriveSpeed = 0;
	rightDriveSpeed = 0;

	lineFollower = false;

}

/*void armPosition(int mArmPosition, int mThrowerSpeed, int timeOut) {
	clearTimer(T1);
	if((SensorValue[dgtl2] != 1) && (SensorValue[dgtl3] != 1)) {
		if(mArmPosition > SensorValue[ThrowerEncoder]) {
			while((mArmPosition > SensorValue[ThrowerEncoder]) && (timeOut > time1[T1])) {

			throwerSpeed = mThrowerSpeed;

			delay(2);
			}
		}
		else {
			while((mArmPosition < SensorValue[ThrowerEncoder]) && (timeOut > time1[T1])) {
				throwerSpeed = mThrowerSpeed * -1;

				delay(2);
			}
		}
	}
	throwerSpeed = 0;
}*/

void mobileGoalLift(int position) {
	if(position == 1) {
		while(SensorValue[dgtl2] != 1)
		{
			mobileArmSpeed = 127;

			delay(2);
		}
	}
	else {
		while(SensorValue[dgtl3] != 1) {
			mobileArmSpeed = -127;

			delay(2);
		}
	}
}

void spin(int degrees, int spinPower, bool brake) {
	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	long spinTargetClicks = degrees * 2.35;

	while(abs(spinTargetClicks) > abs(SensorValue[LeftDriver])){
		leftDriveSpeed = spinPower * sgn(degrees);
		rightDriveSpeed = -1 * spinPower * sgn(degrees);

		delay(2);
	}

	if(brake == true) {
		leftDriveSpeed = -10 * sgn(degrees);
		rightDriveSpeed = 10 * sgn(degrees);
	}
	delay(100);

	leftDriveSpeed = 0;
	rightDriveSpeed = 0;
}

void setHeading(int desiredHeading, int spinPower, bool brake) {
	bool turnRight = true;

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	int deltaRotation = desiredHeading - SensorValue[in1];

	if(sgn(deltaRotation) < 0){
		turnRight = true;
	}
	else {
		turnRight = false;
	}

	if(turnRight == true){
		while(desiredHeading > SensorValue[in1]){
			leftDriveSpeed = spinPower;
			rightDriveSpeed = -1 * spinPower;

			delay(2);
		}
	}
	else{
		while(desiredHeading < SensorValue[in1]){
			leftDriveSpeed = -1 * spinPower;
			rightDriveSpeed = spinPower;

			delay(2);
		}
	}

	if(brake == true) {
		leftDriveSpeed = -10 * sgn(deltaRotation);
		rightDriveSpeed = 10 * sgn(deltaRotation);
	}
	delay(100);

	leftDriveSpeed = 0;
	rightDriveSpeed = 0;
}

task mobileGoalScore() {
	driveForward(300, 80, true, 0);
	mobileGoalLift(0);
	driveForward(10, 20, true, 0);
	mobileGoalLift(1);
	driveForward(-50, 40, true, 0);
	spin(180, 40, true);
	driveForward(300, 60, true, 0);
	mobileGoalLift(0);
}
