/*
 * GetFooter.h
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef GETFOOTER_H_
#define GETFOOTER_H_

#include <State.h>

namespace CmdListenerNS {

class GetFooter: public State {
public:
	GetFooter(CommandListener *ctx);
	virtual ~GetFooter();

	void handleReceivedByte(uint8_t byte);
private:
	enum Commands{
		ACK = 1,
		NACK,
		BUZZER_ON,
		BUZZER_OFF,
		BUZZER_PULSE,
		BUZZER_BLINK,
		BG_BRIGHTNESS,
		AIS_PWR_CTRL,
		GET_AIS_PWR_STATE,
		GET_AIS_PWR_STATE_RESP,

	};
	int readIndex;
	uint8_t buff[2];

	void sendAck();
	void sendNack();
	void sendCommand(Command &cmd);
	void processCommand();
	void cmdBuzzerOn();
	void cmdBuzzerOff();
	void cmdBuzzerPulse();
	void cmdBuzzerBlink();
	void cmdBgLedBrightness();
	void cmdAisPowerControl();
	void cmdGetAisPowerState();
};

} /* namespace CmdListenerNS */

#endif /* GETFOOTER_H_ */
