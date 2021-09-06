/*
 * AisPowerController.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "AisPowerController.h"
#include "Debug.h"

AisPowerController::AisPowerController():
mPwrCtrlPin(PU_DEV2_PWR_CTRL_GPIO_Port, PU_DEV2_PWR_CTRL_Pin) {
	powerDownAIS();
}

AisPowerController::~AisPowerController() {
	// TODO Auto-generated destructor stub
}

void AisPowerController::stateChanged(PowerState state) {
	//TODO: implement when battery is in action
}

void AisPowerController::powerUpAIS() {
	mPwrCtrlPin.setHigh();
}

void AisPowerController::powerDownAIS() {
	mPwrCtrlPin.setLow();
}

bool AisPowerController::getPowerState() {
	return mPwrCtrlPin.read();
}
