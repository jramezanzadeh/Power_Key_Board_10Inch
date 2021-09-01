/*
 * MkdPowerController.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef MKDPOWERCONTROLLER_H_
#define MKDPOWERCONTROLLER_H_

#include <KeyObserver.h>
#include <StateObserver.h>
#include "GpioHandler.h"
#include "VariableContrastLed.h"

enum MkdPowerState{
	ON		= 0,
	OFF	= 1,
};

class MkdPowerController: public StateObserver, public KeyObserver {
public:
	MkdPowerController(GpioHandler* pwrCtrl, GpioHandler* resetPin,
			GpioHandler* onOffPin, VariableContrastLed* ledPower);
	virtual ~MkdPowerController();

	void run();
	void stateChanged(PowerState state);
	void keyEvent(uint8_t keyID, KeyEventType eventType);

	MkdPowerState getPowerState() const {
		return mPowerState;
	}

private:

	MkdPowerState 			mPowerState;
	GpioHandler* 			mPwrCtrlPin;
	GpioHandler* 			mResetPin;
	GpioHandler* 			mOnOffPin;
	VariableContrastLed* 	mLedPower;
	bool					isInputPwrPresent;
	bool					isPowerKeyPressed;
	uint32_t				keyPressedTime;
	uint32_t				lastIncreasingContrastTime;
	uint8_t					ledContrastPercentage;

	void mkdPowerOn();
	void mkdPowerOff();
};

#endif /* MKDPOWERCONTROLLER_H_ */
