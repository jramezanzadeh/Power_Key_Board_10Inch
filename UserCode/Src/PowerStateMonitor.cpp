/*
 * PowerStateMonitor.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "PowerStateMonitor.h"
#include "Debug.h"

PowerStateMonitor::PowerStateMonitor() {
	// TODO Auto-generated constructor stub
#ifdef	INPUT_POWER_IS_MONITORED
	lastPinValue = mPlugInPin.read();
#endif
	updatePowerState();
}

PowerStateMonitor::~PowerStateMonitor() {
	// TODO Auto-generated destructor stub
}

void PowerStateMonitor::run() {
	if(inputPowerStateChanged() || battryStateChanged()){
		updatePowerState();
		notify();
	}
}

void PowerStateMonitor::notify() {
	for(int i = 0; i < (int)mObserverList.size(); i++)
		mObserverList[i]->stateChanged(powerState);
}

void PowerStateMonitor::updatePowerState() {
#ifdef	INPUT_POWER_IS_MONITORED
	//TODO add Battery state too, it is supposed that battery always is present
	powerState = lastPinValue? POWER_ON_BOTH:POWER_ON_BATT;
#else
	powerState = POWER_ON_BOTH;
#endif
	Debug::getInstance().log("PowerState changed --> %d\r\n", powerState);
#ifdef ENABLE_POWER_STATE_CHANGE_ALARM
	switch(powerState){
	case POWER_DOWN:
		mMode0->setLow();
		mMode1->setLow();
		break;
	case POWER_ON_BATT:
		mMode0->setHigh();
		mMode1->setLow();
		break;
	case POWER_ON_INPUT:
		mMode0->setLow();
		mMode1->setHigh();
		break;
	case POWER_ON_BOTH:
		mMode0->setHigh();
		mMode1->setHigh();
		break;
	}
#endif
}

bool PowerStateMonitor::inputPowerStateChanged() {
#ifdef INPUT_POWER_IS_MONITORED
	if(mPlugInPin->read() != lastPinValue){
		lastPinValue = mPlugInPin->read();
		return true;
	}
#endif
	return false;
}

bool PowerStateMonitor::battryStateChanged() {
	//TODO: add battery monitor
	return false;
}
