/*
 * AisPowerController.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef AISPOWERCONTROLLER_H_
#define AISPOWERCONTROLLER_H_

#include <StateObserver.h>
#include "GpioHandler.h"

class AisPowerController: public StateObserver {
public:
	AisPowerController();
	virtual ~AisPowerController();

	void stateChanged(PowerState state);
	void powerUpAIS();
	void powerDownAIS();
	bool getPowerState();
private:
	GpioHandler mPwrCtrlPin;

};

#endif /* AISPOWERCONTROLLER_H_ */
