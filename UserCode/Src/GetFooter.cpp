/*
 * GetFooter.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "GetFooter.h"
#include "Debug.h"
#include "IdleState.h"
#include "LedAndBuzzerManager.h"

namespace CmdListenerNS {

GetFooter::GetFooter(CommandListener *ctx):State(ctx) {
	// TODO Auto-generated constructor stub
	readIndex = 0;
	debuger << "GetFooter" << endl;
}

GetFooter::~GetFooter() {
	// TODO Auto-generated destructor stub
}

void GetFooter::handleReceivedByte(uint8_t byte) {
	buff[readIndex++] = byte;
	if(readIndex == 2){
		mCtx->getCurrentCmd().crc = buff[0];
		mCtx->getCurrentCmd().etx = buff[1];
		if(mCtx->getCurrentCmd().isValid()){
			processCommand();
			debuger << "Valid Command" << endl;
		}else{
			debuger << "inValid Command" << endl;
			sendNack();
		}
		mCtx->setState(new IdleState(mCtx));
	}
}

void GetFooter::sendAck() {
	Command ackCmd;
	ackCmd.header.cmd = ACK;
	ackCmd.header.len = 0;
	ackCmd.updateCRC();
	sendCommand(ackCmd);

}

void GetFooter::sendNack() {
	Command ackCmd;
	ackCmd.header.cmd = NACK;
	ackCmd.header.len = 0;
	ackCmd.updateCRC();
	sendCommand(ackCmd);
}

void GetFooter::sendCommand(Command& cmd) {
	uint8_t buff[50];
	mCtx->writeByte(cmd.stx);
	int len = cmd.toArray(buff);
	for(int i = 0; i < len; i++)
		mCtx->writeByte(buff[i]);
	mCtx->writeByte(cmd.crc);
	mCtx->writeByte(cmd.etx);
}

void GetFooter::processCommand() {
	switch (mCtx->getCurrentCmd().header.cmd) {
	case BUZZER_ON:
		cmdBuzzerOn();
		break;
	case BUZZER_OFF:
		cmdBuzzerOff();
		break;
	case BUZZER_PULSE:
		cmdBuzzerPulse();
		break;
	case BUZZER_BLINK:
		cmdBuzzerBlink();
		break;
	case BG_BRIGHTNESS:
		cmdBgLedBrightness();
		break;
	case AIS_PWR_CTRL:
		cmdAisPowerControl();
		break;
	case GET_AIS_PWR_STATE:
		cmdGetAisPowerState();
		break;
	default:
		sendNack();
		break;
	}
}

void GetFooter::cmdBuzzerOn() {
	buzzerManager.on(LedAndBuzzerManager::BUZZER);
	sendNack();
}

void GetFooter::cmdBuzzerOff() {
	buzzerManager.off(LedAndBuzzerManager::BUZZER);
	sendAck();
}

void GetFooter::cmdBuzzerPulse() {
	if(mCtx->getCurrentCmd().header.len != 4){
		sendNack();
		return;
	}
	uint32_t time = *((uint32_t*)mCtx->getCurrentCmd().paylaod);
	buzzerManager.pulse(LedAndBuzzerManager::BUZZER, time);
	sendAck();
}
// TODO: this function's name is so weird :)
void GetFooter::cmdBuzzerBlink() {
	if(mCtx->getCurrentCmd().header.len != 4){
		sendNack();
		return;
	}
	uint32_t time = *((uint32_t*)mCtx->getCurrentCmd().paylaod);
	buzzerManager.blink(LedAndBuzzerManager::BUZZER, time);
	sendAck();
}

void GetFooter::cmdBgLedBrightness() {
	if(mCtx->getCurrentCmd().header.len != 1){
		sendNack();
		return;
	}
	uint8_t brightness = mCtx->getCurrentCmd().paylaod[0];
	mCtx->setBgLedBrightness(brightness);
	sendAck();
}

void GetFooter::cmdAisPowerControl() {
	if(mCtx->getCurrentCmd().header.len != 1){
		sendNack();
		return;
	}
	bool UpOrDown = mCtx->getCurrentCmd().paylaod[0];
	if(UpOrDown)
		mCtx->powerUpAIS();
	else
		mCtx->powerDownAIS();
	sendAck();
}

void GetFooter::cmdGetAisPowerState() {
	Command resp;
	resp.header.cmd = GET_AIS_PWR_STATE_RESP;
	resp.header.len = 1;
	resp.paylaod[0] = mCtx->getAisPowerState();
	resp.updateCRC();
	sendCommand(resp);
}

} /* namespace CmdListenerNS */
