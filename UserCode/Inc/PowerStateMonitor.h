/*
 * PowerStateMonitor.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef POWERSTATEMONITOR_H_
#define POWERSTATEMONITOR_H_

#include <Observable.h>
#include "StateObserver.h"
#include "GpioHandler.h"

//#define INPUT_POWER_IS_MONITORED
//#define ENABLE_POWER_STATE_CHANGE_ALARM

class PowerStateMonitor: public Observable<StateObserver> {
public:
	PowerStateMonitor();
	virtual ~PowerStateMonitor();

	void run();

	PowerState getPowerState() const {
		return powerState;
	}


private:
#ifdef INPUT_POWER_IS_MONITORED
	GpioHandler 			mPlugInPin;
	GpioHandler 			mMode0;
	GpioHandler 			mMode1;
	bool 					lastPinValue;
#endif
	PowerState powerState;

	void notify();
	void updatePowerState();
	bool inputPowerStateChanged();
	bool battryStateChanged();

};

#endif /* POWERSTATEMONITOR_H_ */
