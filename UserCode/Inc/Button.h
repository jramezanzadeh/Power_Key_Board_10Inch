/*
 * Button.h
 *
 *  Created on: Sep 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "GpioHandler.h"

class Button {
public:
	enum ButtonEvent {
		NO_CHANGE = 0,
		PRESSED,
		RELEASED
	};
	Button(GPIO_TypeDef* port, uint16_t pin);
	virtual ~Button();
	ButtonEvent getEvent();

private:
	bool mLastState; // HIGH = true, LOW = false
	GpioHandler mGpioPin;
};

#endif /* BUTTON_H_ */
