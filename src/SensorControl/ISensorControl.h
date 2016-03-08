/*
 * ISensorControl.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Beasty
 */

#ifndef SRC_SENSORCONTROL_ISENSORCONTROL_H_
#define SRC_SENSORCONTROL_ISENSORCONTROL_H_

#include <IControl.h>

class MotorCommand {
public:
	float leftMotorSpeed;
	float rightMotorSpeed;
};

class ISensorControl: public IControl {
public:
	ISensorControl(){}
	virtual ~ISensorControl(){}
	enum DriveSystemState{
			running,
			stopping,
			stopped
		};
	MotorCommand updateMotorSpeedResponse;
	// Bottom loop, right before actual motor command
	virtual MotorCommand *UpdateMotorSpeeds(float leftMotorSpeed, float rightMotorSpeed){

		updateMotorSpeedResponse.leftMotorSpeed = leftMotorSpeed;
		updateMotorSpeedResponse.rightMotorSpeed = rightMotorSpeed;

		return &updateMotorSpeedResponse;
	}
};

#endif /* SRC_SENSORCONTROL_ISENSORCONTROL_H_ */
