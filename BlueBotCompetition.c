#pragma config(Sensor, in2,    lineFollowerInner, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerCenter, sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerOuter, sensorLineFollower)
#pragma config(Sensor, in5,    ElbowPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in6,    MobileGoalLiftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in7,    LineFollowerRightMiddle, sensorLineFollower)
#pragma config(Sensor, in8,    LineFollowerLeftMiddle, sensorLineFollower)
#pragma config(Sensor, dgtl1,  autoMode,       sensorDigitalIn)
#pragma config(Sensor, dgtl2,  LifterLimitUp,  sensorDigitalIn)
#pragma config(Sensor, dgtl3,  LifterLimitDown, sensorDigitalIn)
#pragma config(Sensor, dgtl4,  ArmEncoderLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  ArmEncoderRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  LeftDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl10, RightDriveEncoder, sensorQuadEncoder)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           ArmLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LifterLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           intakeElbow,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LifterRight,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           ConeIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ArmRight,      tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "LCDDisplay2016.c" // LCD Display Control
#include "GlobalVariables.c" // Variables for all
#include "ArmHolder.c" // Controls the thrower
#include "ArmControl.c" // CONTROLS FOR THE ARM RARARARARAREA
#include "MobileGoalLiftController.c" // gay
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Pid.c" // PID controller program its self explanatory idiot, and not really idiot becAUSE IT NO LONGER IS JUST PID BUT A BUNCH OF FUNCTIONS AND TASEKS AND ALL THE AUTONOMOUS ROUTINES SO GUESS WAHT IDIOT YOUR WRONG. AND SORRY FOR ALL THE CAPS i ACCIDENTLY HIT THE CAPS LOCK KEE. i'M SORRY.
#include "BlueDriverJoyStickControls.c" // User Controls For User Controlled Period
//#include "LEDLightTimers.c" // Led Light Timer for User Control Part
//#include "LCDDisplay2016.c"
// =(
// =(
// =(
// =(
// =(
// =(

// \ ( ^ , ^ ) /

int autoRoutineID = 1;

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	  bStopTasksBetweenModes = true;
	  SensorType[in1] = sensorNone;
	  wait1Msec(1000);
	  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	  SensorType[in1] = sensorGyro;
	  wait1Msec(2000);
		SensorValue[in1] = 0;
	  if (SensorValue[autoMode] == 1){
	  	autoRoutineID = getAutoOption();
	  }

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}
task autonomous()
{
	startTask(armControl);
	startTask(armPID);
	startTask(driving);
	startTask(armHolder);
	if(autoRoutineID == 0){
		//startTask(mobileGoalScore);
	}
	while(true){
		delay(500);
	}
}

task usercontrol()
{
		startTask(armHolder);
		startTask(armPID);
		startTask(armControl);
	  startTask(controllerPolling);
	  startTask(driving);
	  while(true){
	  	delay(500);
	  }
}
