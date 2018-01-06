task armHolder()
{
	// variables for hold control
	bool isHolding = false;
	int prevArmPosition = 0;
	int curArmPosition = 0;
	int holdPower = 0;

	while(true)
	{
		// If we want to move the thrower, use the desired speed
		if (throwerSpeed != 0){
			motor[armLeft] = armLeftSpeed;
			motor[armRight] = armRightSpeed;
			isHolding = false;
		}
		// Else, hold
		else{
			// First time in here, we are just starting to hold
			if (isHolding == false){
				isHolding = true;
				holdPower=0;
				curArmPosition = SensorValue[ArmEncoderRight];
			}
			else{  //After the first time, do hold logic
				prevArmPosition = curArmPosition;
				curArmPosition = SensorValue[ArmEncoderRight];

				// OK need to test values here to see
				// Assuming higher values on sensor means arm is up, lower means down
				if (curArmPosition < prevArmPosition){
					holdPower = holdPower + 2;
				}
				else if (curArmPosition > prevArmPosition){
					holdPower = holdPower - 2;
				}
			}
			// now apply the hold pwer
			motor[armLeft] = holdPower;
			motor[armRight] = holdPower;
		}
		delay(10);
	}
}
