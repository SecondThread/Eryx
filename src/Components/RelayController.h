/*
 * RelayController.h
 *
 *  Created on: Feb 20, 2016
 *      Author: lazar
 */

#ifndef SRC_COMPONENTS_RELAYCONTROLLER_H_
#define SRC_COMPONENTS_RELAYCONTROLLER_H_

#include <IControl.h>
#include "WPILib.h"



class RelayController: public IControl {
public:
	RelayController();
	virtual ~RelayController();

	void RobotInit();
	void TeleopInit();
	void TeleopPeriodic();
	void DisabledPeriodic();

protected:
	enum  RelayColor{
		neither,
		red,
		blue,
	};

	bool blink;
	int blinkSpeed = 100; // n * 5ms = ?, EX 100 * 5ms = 500ms  = .5s frequency

	RelayColor currnet = RelayColor::neither;

	Relay* Blue;
	Relay* Red;

	void ToggleColor();	//Swithchs the current color if it is set to neither it does nothing
	void setColor(RelayColor); 	//Sets the selected color to the value
	void relayBlink(int); //Blinks the leds at a certain speed the int describle the number of cycles before it switchs

	void burnUp(); //Speed ups the frequency for 2s // Extra Credit
	void stopBlink(); //Stops Blinking

};

#endif /* SRC_COMPONENTS_RELAYCONTROLLER_H_ */
