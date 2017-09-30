void lineFollow(int mStrafeSpeed, bool firstLoop) {
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
	lineDeltaPower = ( currentLineError * pid_Kp_line ) + (lineSumError * pid_Ki_line );

	strafeSpeed = lineDeltaPower;
	/*if(SensorValue[lineFollowerInner] < SensorValue[lineFollowerCenter] + 500) {
		strafeSpeed = mStrafeSpeed;
	}

	else if(SensorValue[lineFollowerOuter] < SensorValue[lineFollowerCenter] + 500) {
		strafeSpeed = mStrafeSpeed * -1;
	}

	else {
		strafeSpeed = 0;
	} */

}

void lineFollowWall(int pStrafeSpeed){
	if((SensorValue[lineFollowerOuter] > (SensorValue[lineFollowerCenter] + 1000)) || (SensorValue[lineFollowerOuter] > (SensorValue[lineFollowerInner] + 800))){
		strafeSpeed = pStrafeSpeed * -1;
	}
	else if(SensorValue[lineFollowerOuter] > 2200){
		strafeSpeed = pStrafeSpeed;
	}
	else {
		strafeSpeed = 0;
	}
}

bool findLine(int oStrafeSpeed, int mLoopCounter){
	bool foundLine = false;
	strafeMode = true;

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	int loopCounter = 0;

	if(foundLine == false) {
		while((foundLine == false) && (loopCounter < mLoopCounter * 4)){
			if(loopCounter < mLoopCounter){
				strafeSpeed = oStrafeSpeed;
			}
			else if(loopCounter < mLoopCounter * 3){
				strafeSpeed = oStrafeSpeed * -1;
			}
			else {
				strafeSpeed = oStrafeSpeed;
			}
			if((SensorValue[lineFollowerCenter] + 1000 < SensorValue[lineFollowerInner]) && (SensorValue[lineFollowerCenter] + 1000 < SensorValue[lineFollowerOuter])){
				foundLine = true;
				strafeSpeed = 30 * sgn(strafeSpeed) * -1;
				delay(100);
			}
			loopCounter = loopCounter + 1;
			delay(3);
		}
	}
	strafeSpeed = 0;
	strafeMode = false;
	return foundLine;
}

// =(

void driveForward(int distanceCM, int targetSpeed, bool brake, int lineFollower){

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	// Enter Strafe Mode, set target speed

	strafeMode = true;

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
			lineFollow(40, true);
			firstLoop = false;
		}
		else if(lineFollower == 2){
			lineFollowWall(40);
		}
		delay(2);
	}

	//brake, then coast

	strafeSpeed = 0;

	if(brake == true) {

		leftDriveSpeed = -10 * sgn(distanceCM);
		rightDriveSpeed = -10 * sgn(distanceCM);

		delay(100);

	}

	leftDriveSpeed = 0;
	rightDriveSpeed = 0;

	strafeMode = false;
	lineFollower = false;

}

void armPosition(int mArmPosition, int mThrowerSpeed, int timeOut) {

	clearTimer(T1);

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

	throwerSpeed = 0;

}

/*int calculateSpinDegrees(int desiredHeading) {
	int calculatedSpinUnits = (desiredHeading * 10) - SensorValue[in1];
	return (calculatedSpinUnits / 10);
} */

void spin(int degrees, int spinPower, bool brake) {

	strafeMode = false;

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

	strafeMode = false;
	bool turnRight = true;

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	int deltaRotation = desiredheading - SensorValue[in1];

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

void strafeAuto(int nStrafeSpeed, int strafeDistance){
	/*SensorValue[LeftDriver]  = 0;
	SensorValue[RightDriver] = 0; */
	SensorValue[StrafeDrive] = 0;

	strafeMode = true;

	int loopCounter = 0;

	while((abs(strafeDistance) > abs(SensorValue[StrafeDrive])) &&
		((SensorValue[bumperLeftFront] == 0) || (SensorValue[bumperLeftBack] == 0)) &&
		((SensorValue[bumperRightFront] == 0) || (SensorValue[bumperLeftBack] == 0)) &&
		(loopCounter < 5000)){

		strafeSpeed = nStrafeSpeed * sgn(strafeDistance);

		loopCounter = loopCounter + 1;
		delay(2);

	}

	if((SensorValue[bumperLeftFront] == 1) && (SensorValue[bumperLeftBack] == 1)){
		delay(500);
	}
	else if((SensorValue[bumperRightFront] == 1) && (SensorValue[bumperRightBack] == 1)){
		delay(500);
	}

	strafeSpeed = 0;
	strafeMode = false;
}

/*void liftAuto(int mLiftSpeed, int nLoopCounter){
	int loopCounter = 0;

	while(loopCounter < nLoopCounter) {
		liftSpeed = mLiftSpeed;
		loopCounter = loopCounter + 1;
		delay(2);
	}
}
*/
task armDeploy() {
	armPosition(-78, 127, 250);
	armPosition(182, 50, 2000); // Claw Deployed
}

task starThrow() {
	armPosition(676, 127, 3000); // Star Thrown
}

task strafeLeftStartToWall() {
	strafeAuto(50, 160);
}

task strafeRight() {
	strafeAuto(70, -400);
}

task wallSweep {
	startTask(strafeLeftStartToWall);
	startTask(armDeploy);
	driveForward(-190, 127, true, 0);
	startTask(starThrow);
	driveForward(-25, 127, true, 0); // Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(400, 40, 4000);
	delay(500);
	spin(250, 90, true);
	driveForward(-210, 80, true, 2);
	armPosition(340, 60, 4000);
	driveForward(-200, 80, true, 2);
	armPosition(400, 40, 4000);
	driveForward(-110, 80, true, 2);
	spin(500, 90, true);
	driveForward(-50, 80, true, 2);
	armPosition(510, 127, 4000);
}

task simpleThrow{
	startTask(strafeLeftStartToWall);
	startTask(armDeploy);
	driveForward(-190, 127, true, 0);
	startTask(starThrow);
	driveForward(-25, 127, true, 0); // Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(440, 40, 3000);
}

task shortSweep{
	startTask(strafeLeftStartToWall);
	startTask(armDeploy);
	driveForward(-190, 127, true, 0);
	startTask(starThrow);
	driveForward(-25, 127, true, 0); // Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(440, 40, 4000);
	delay(500);
	spin(250, 90, true);
	driveForward(-210, 80, true, 2);
	armPosition(360, 60, 4000);
	driveForward(-200, 80, true, 2);
}

task longBlock{
	startTask(strafeLeftStartToWall);
	startTask(armDeploy);
	driveForward(-190, 127, true, 0);
	startTask(starThrow);
	driveForward(-25, 127, true, 0); // Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(440, 40, 4000);
	delay(500);
	spin(250, 90, true);
	driveForward(-210, 80, true, 2);
	armPosition(360, 60, 4000);
	driveForward(-100, 80, true, 2);
	spin(-250, 90, true);
	armPosition(650, 50, 4000);
}

task quickBlock{
	startTask(armDeploy);
	driveForward(-100, 127, true, 0);
	startTask(strafeRight);
	startTask(starThrow);
	driveForward(-115, 127, true, 0); //Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(650, 40, 4000);
	delay(500);
}

task doubleThrow{
	startTask(strafeLeftStartToWall);
	startTask(armDeploy);
	driveForward(-190, 127, true, 0);
	startTask(starThrow);
	driveForward(-25, 127, true, 0); // Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(440, 40, 3000);
	startTask(strafeRight);
	driveForward(80, 127, true, 0);
	armPosition(20, 40, 3000);
	driveForward(70, 127, true, 0);
	armPosition(120, 40, 3000);
	driveForward(-120, 127, true, 0);
	startTask(starThrow);
	driveForward(-30, 127, true, 0);
}

task autoRobotGo {
	int preLoadLoop = 0;

	startTask(armDeploy);
	driveForward(-190, 127, false, 0);
	startTask(starThrow);
	driveForward(-25, 127, false, 0); // Drive To Wall
	strafeMode = false;
	delay(1000); // Catch our breath at wall
	while(preLoadLoop < 4){
		armPosition(320, 40, 3000);
		driveForward(230, 127, false, 0);
		strafeMode = false;
		delay(1500);
		driveForward(-220, 127, false, 0);
		startTask(starThrow);
		driveForward(-30, 127, false, 0);
		preLoadLoop = preLoadLoop + 1;
		strafeMode = false;
		delay(1000);
	}
	driveForward(80, 127, true, 0);
	strafeAuto(80, 130);
	armPosition(20, 60, 3000);
	driveForward(70, 127, true, 0);
	armPosition(120, 60, 3000);
	driveForward(-120, 127, true, 0);
	startTask(starThrow);
	driveForward(-30, 127, true, 0);
	delay(1000);
	armPosition(300, 40, 3000);
	driveForward(70, 127, true, 0);
}

/*task autoRobotCubeThrowGo{
	startTask(armDeploy);
	driveForward(-190, 127, true, 0);
	startTask(starThrow);
	driveForward(-25, 127, true, 0); // Drive To Wall
	delay(1000); // Catch our breath at wall
	armPosition(440, 40, 3000);
	delay(500);
	driveForward(20, 127, true, 0);
	delay(250);
	strafeAuto(80, 350); // Strafe To Cube
	delay(250);
	driveForward(150, 127, true, 0); // Push Cube To Wall
	driveForward(-80, 127, true, 0);
	delay(250);
	armPosition(20, 60, 3000); // Arm At Cube Position
	delay(250);
	driveForward(80, 127, true, 0); // Cube Grabbed
	delay(250);
	armPosition(200, 60, 3000); // Lift Cube
	driveForward(-75, 127, true, 0); // Start Driving To Wall
	startTask(starThrow); // Throw Cube
	driveForward(-75, 127, true, 0); // At Wall
}*/

task armPositionLow() {
	armPosition(442, 80, 3000);
}

task armPositionHigh() {
	armPosition(468, 80, 3000);
}
