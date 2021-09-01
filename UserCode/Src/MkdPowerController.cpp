/*
 * MkdPowerController.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "MkdPowerController.h"

MkdPowerController::MkdPowerController(GpioHandler* pwrCtrl, GpioHandler* resetPin,
		GpioHandler* onOffPin,VariableContrastLed* ledPower)
		{
	// TODO Auto-generated constructor stub
	mPwrCtrlPin = pwrCtrl;
	mResetPin = resetPin;
	mOnOffPin = onOffPin;
	mLedPower = ledPower;
	mPowerState = OFF;
	isInputPwrPresent = false;
	isPowerKeyPressed = false;
	keyPressedTime = 0;
	lastIncreasingContrastTime = 0;
	ledContrastPercentage = 0;
	mkdPowerOff();
}

MkdPowerController::~MkdPowerController() {
	// TODO Auto-generated destructor stub
}

void MkdPowerController::stateChanged(PowerState state) {
	switch (state) {
	case POWER_DOWN:
	case POWER_ON_BATT:
		isPowerKeyPressed = false;
		isInputPwrPresent = false;
		mkdPowerOff();
		break;
	case POWER_ON_INPUT:
	case POWER_ON_BOTH:
		ledContrastPercentage = 0;
		lastIncreasingContrastTime = HAL_GetTick();
		isInputPwrPresent = true;
		break;
	}
}

void MkdPowerController::keyEvent(uint8_t keyID, KeyEventType eventType) {
	if(isInputPwrPresent){
		if(keyID == Key_Disp){
			if(eventType == KEY_PRESSED){
				keyPressedTime = HAL_GetTick(); // capture event time
				isPowerKeyPressed = true;
			}else{
				isPowerKeyPressed = false;
			}
		}
	}
}

void MkdPowerController::run() {
	// handle power key press
	if(isPowerKeyPressed){
		if(mPowerState == ON){
			if(HAL_GetTick() - keyPressedTime > 3000){ // check whether press time is more than 3 seconds or not
				isPowerKeyPressed = false;
				mkdPowerOff();
			}
		}else{
			// power on MKD immediately
			isPowerKeyPressed = false;
			mkdPowerOn();
		}
	}
	//handle periodically increasing power led's contrast
	//TODO write it in a clear way
	if(isInputPwrPresent && (mPowerState == OFF)){
		if(HAL_GetTick() - lastIncreasingContrastTime > 500){
			lastIncreasingContrastTime = HAL_GetTick();
			ledContrastPercentage += 10;
			ledContrastPercentage %= 101;
			mLedPower->setContrastPercentage(ledContrastPercentage);
		}
	}
}

void MkdPowerController::mkdPowerOn() {
	mPowerState = ON;
	mPwrCtrlPin->setHigh();
	mOnOffPin->setHigh();
	mResetPin->setHigh();
	ledContrastPercentage = 100;
	mLedPower->setContrastPercentage(ledContrastPercentage);
	//HAL_Delay(100); //TODO when the mkd is turned on, 5V power will oscillate(why???)

}

void MkdPowerController::mkdPowerOff() {
	mPowerState = OFF;
	mResetPin->setLow();
	mOnOffPin->setLow();
	mPwrCtrlPin->setLow();
	ledContrastPercentage = 0;
	mLedPower->setContrastPercentage(ledContrastPercentage);
	lastIncreasingContrastTime = HAL_GetTick();

}
