/*
 * LedManager.h
 *
 *  Created on: Aug 13, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef LEDMANAGER_LEDMANAGER_H_
#define LEDMANAGER_LEDMANAGER_H_

#include "GpioHandler.h"

#define ledManager LedAndBuzzerManager::instance()
#define buzzerManager LedAndBuzzerManager::instance()

class LedAndBuzzerManager {
public:
	enum LED{
		STATUS = 0,
		BUZZER,
		LED_CNT
	};
	static LedAndBuzzerManager& instance();
	virtual ~LedAndBuzzerManager();
	void on(LED led);
	void off(LED led);
	void pulse(LED led, int time);
	void blink(LED led, int time);
	void clearAll();
	void run();

private:

	class Led{
	public:
		Led(GPIO_TypeDef* port, uint16_t pin);
		virtual ~Led();
		void on();
		void off();
		void pulse(int time);
		void blink(int time);
		void run();
	private:
		enum State{
			ON = 0,
			OFF,
			PULSE,
			BLINK,
		};
		GpioHandler mGpioPin;
		State mState;
		uint32_t mStartTime;
		int mTime;

		bool isTimeElapsed();
	};

	Led ledList[LED_CNT];
	LedAndBuzzerManager();

};

#endif /* LEDMANAGER_LEDMANAGER_H_ */
