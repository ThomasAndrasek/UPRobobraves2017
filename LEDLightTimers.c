
task lightShow(){
		SensorValue[ledGreen] = 0;
		SensorValue[ledRed] = 0;
		SensorValue[ledYellow] = 0;
		SensorValue[ledGreen] = 1;
		delay(90000);
		SensorValue[ledGreen] = 0;
		SensorValue[ledYellow] = 1;
		delay(20000);
		SensorValue[ledYellow] = 0;
		SensorValue[ledRed] = 1;
}
