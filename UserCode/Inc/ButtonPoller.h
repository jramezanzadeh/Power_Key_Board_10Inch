/*
 * pollingButtonMonitor.h
 *
 *  Created on: Sep 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef POLLINGBUTTONMONITOR_H_
#define POLLINGBUTTONMONITOR_H_

#include "map"
#include "Button.h"
#include "KeyObserver.h"

class ButtonPoller {
public:
	ButtonPoller();
	virtual ~ButtonPoller();

	void run();
private:
	std::map<Keys, Button> mKeyButtonMap;
};

#endif /* POLLINGBUTTONMONITOR_H_ */
