/*
 * Button.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "Button.h"

Button::Button(GPIO_TypeDef* port, uint16_t pin):mGpioPin(port, pin) {
	// TODO Auto-generated constructor stub
	mLastState = mGpioPin.read();

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

Button::ButtonEvent Button::getEvent() {

	bool currentState = mGpioPin.read();
	if(currentState == mLastState)
		return NO_CHANGE;
	else{ // state has changed
		mLastState = currentState; //save state
		if(currentState)
			return RELEASED;
		else
			return PRESSED;
	}

}

