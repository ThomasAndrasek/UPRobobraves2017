
int throwerSpeed = 0;

task throwerControl()
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
			motor[leftThrow] = throwerSpeed;
			motor[rightThrow] = throwerSpeed;
			motor[rightThrowThree] = throwerSpeed;
			motor[leftThrowThree] = throwerSpeed;
			isHolding = false;
		}
		// Else, hold
		else{
			// First time in here, we are just starting to hold
			if (isHolding == false){
				isHolding = true;
				holdPower=0;
				curArmPosition = SensorValue[ThrowerEncoder];
			}
			else{  //After the first time, do hold logic
				prevArmPosition = curArmPosition;
				curArmPosition = SensorValue[ThrowerEncoder];

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
			motor[leftThrow] = holdPower;
			motor[rightThrow] = holdPower;
			motor[rightThrowThree] = holdPower;
			motor[leftThrowThree] = holdPower;
		}

		delay(10);
	}

}
