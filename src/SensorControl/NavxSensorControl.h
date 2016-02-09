/*
 * NavxSensorControl.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#ifndef SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_
#define SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_
#include <Xbox/IXbox.h>
#include <Profile/IProfile.h>
#include <AHRS.h>

#include <SensorControl/ISensorControl.h>

class NavxSensorControl: public ISensorControl, public PIDOutput {
public:
	NavxSensorControl(IXbox *xbox, IProfile *profileInstance);
	virtual ~NavxSensorControl();

	IXbox *xbox;
	IProfile *profile;
	AHRS *ahrs;                         // navX-MXP
	PIDController *turnController;      // PID Controller

	enum TargetingState{
		waitForButtonPress,
		waitForStopped,
		waitForPicResult,
		driveToAngle,
	};

	MotorCommand *UpdateMotorSpeeds(float leftMotorSpeed, float rightMotorSpeed);
	DriveSystemState DriveSystemControlUpdate(DriveSystemState currentState, DriveSystemState requestedState);

	void TeleopInit();
	void TeleopPeriodic();

protected:
	TargetingState targetState;
	DriveSystemState currentDriveState, commandDriveState;
	double visionTargetAngle;
	double visionAngleTolerance;
	float turnSpeed;

	void PIDWrite(float output);
	void TargetingStateMachine();
	void InitializeVisionAlignment(double commandedAngle);
	bool ExecuteVisionAlignment();

};

#endif /* SRC_SENSORCONTROL_NAVXSENSORCONTROL_H_ */
