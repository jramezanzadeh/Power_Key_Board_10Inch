/*
 * AisPowerController.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "AisPowerController.h"
#include "Debug.h"

AisPowerController::AisPowerController(GpioHandler* inputPwrCtrlPin,
		GpioHandler* ais3V8PwrCtrlPin) {
	mInputPwrCtrlPin = inputPwrCtrlPin;
	mAis3V8PwrCtrlPin = ais3V8PwrCtrlPin;
}

AisPowerController::~AisPowerController() {
	// TODO Auto-generated destructor stub
}

void AisPowerController::stateChanged(PowerState state) {
	//TODO: implement when battery is in action
}

