/*
 * LedManager.cpp
 *
 *  Created on: Aug 13, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <LedAndBuzzerManager.h>

LedAndBuzzerManager& LedAndBuzzerManager::instance() {
	static LedAndBuzzerManager instance;
	return instance;
}

void LedAndBuzzerManager::on(LED led) {
	if(led < LED_CNT)
		ledList[led].on();
}

void LedAndBuzzerManager::off(LED led) {
	if(led < LED_CNT)
		ledList[led].off();
}

void LedAndBuzzerManager::pulse(LED led, int time) {
	if(led < LED_CNT)
		ledList[led].pulse(time);
}

void LedAndBuzzerManager::blink(LED led, int time) {
	if(led < LED_CNT)
		ledList[led].blink(time);
}

void LedAndBuzzerManager::run() {
	for(int i = 0; i < LED_CNT; i++)
		ledList[i].run();
}

void LedAndBuzzerManager::clearAll() {
	for(int i = 0; i < LED_CNT; i++)
		ledList[i].off();
}

LedAndBuzzerManager::LedAndBuzzerManager():
		ledList({{STATUS_LED_GPIO_Port, STATUS_LED_Pin}, {BUZZER_GPIO_Port, BUZZER_Pin}}) {
	// TODO Auto-generated constructor stub
	clearAll();
}

LedAndBuzzerManager::~LedAndBuzzerManager() {
	// TODO Auto-generated destructor stub
}

LedAndBuzzerManager::Led::Led(GPIO_TypeDef* port, uint16_t pin):mGpioPin(port, pin) {
	mState = OFF;
	mGpioPin.setLow();
	mStartTime = 0;
	mTime = 0;
}

LedAndBuzzerManager::Led::~Led() {
}

void LedAndBuzzerManager::Led::on() {
	mState = ON;
	mGpioPin.setHigh();
}

void LedAndBuzzerManager::Led::off() {
	mState = OFF;
	mGpioPin.setLow();
}

void LedAndBuzzerManager::Led::pulse(int time) {
	mState = PULSE;
	mGpioPin.setHigh();
	mStartTime = HAL_GetTick();
	mTime = time;
}

void LedAndBuzzerManager::Led::blink(int time) {
	mState = BLINK;
	mGpioPin.setHigh();
	mStartTime = HAL_GetTick();
	mTime = time;
}

void LedAndBuzzerManager::Led::run() {
	switch (mState) {
	case PULSE:
		if(isTimeElapsed())
			off();
		break;
	case BLINK:
		if(isTimeElapsed()){
			mStartTime = HAL_GetTick();
			mGpioPin.toggle();
		}
		break;
	default:
		break;
	}
}

bool LedAndBuzzerManager::Led::isTimeElapsed() {
	return (HAL_GetTick() - mStartTime > (uint32_t)mTime);
}
