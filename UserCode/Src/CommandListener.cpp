/*
 * CommandListener.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "CommandListener.h"
#include "IdleState.h"
#include "State.h"
#include "string.h"
#include "Helper.h"

using namespace CmdListenerNS;

CommandListener::CommandListener():mPort(&huart2), mBgLedCtrl(&htim4, TIM_CHANNEL_3) {
	// TODO Auto-generated constructor stub
	mTxRdIndex = 0;
	mTxWrIndex = 0;
	mCurrentState = new IdleState(this);
	mByte = 0;

}

CommandListener::~CommandListener() {
	// TODO Auto-generated destructor stub
}

void CommandListener::init() {
	mPort.init(USART2, 115200, UART_MODE_TX_RX);
	mPort.open();
}

void CommandListener::run() {
	// handle receive
	if(mPort.read(&mByte, 1, 0) > 0){
		mCurrentState->handleReceivedByte(mByte);
	}
	//handle Transmit
	if(mTxRdIndex != mTxWrIndex){ //TX buff isn't empty
		if(mPort.isReadyToSend()){
			mPort.send(mTxBuff+mTxRdIndex, 1, 0);
			mTxRdIndex++;
			mTxRdIndex %= TX_BUFF_LEN;
		}
	}
}

void CommandListener::setState(CmdListenerNS::State* state) {
	delete mCurrentState;
	mCurrentState = state;
}

void CommandListener::writeByte(uint8_t byte) {
	mTxBuff[mTxWrIndex] = byte;
	mTxWrIndex++;
	mTxWrIndex %= TX_BUFF_LEN;
}

void CommandListener::setBgLedBrightness(uint8_t brightnessPercentage) {
	mBgLedCtrl.setContrastPercentage(brightnessPercentage);
}

void CommandListener::powerDownAIS() {
	mAisPwrCtrl.powerDownAIS();
}

void CommandListener::powerUpAIS() {
	mAisPwrCtrl.powerUpAIS();
}

bool CommandListener::getAisPowerState() {
	return mAisPwrCtrl.getPowerState();
}

/******************************* Command Implementation *****************************/
void Command::reset() {
	stx = 0;
	memset(&header, 0, sizeof(Header));
	memset(paylaod, 0, MAX_PAYLOAD_LEN);
	crc = 0;
	etx = 0;
}

int Command::toArray(uint8_t* buff) {
	int offset = 0;
	memcpy(buff+offset, &header, sizeof(Header)); offset += sizeof(Header);
	memcpy(buff+offset, paylaod, header.len); offset += header.len;
	return offset;
}

void Command::updateCRC() {
	crc = calcCRC();
}

uint8_t Command::calcCRC() {
	uint8_t buff[50];
	int len = toArray(buff);
	return Helper::calcCRC(buff, len);
}

Command::Command() {
	stx = STX;
	etx = ETX;
	crc = 0;
}

bool Command::checkCRC() {
	return crc == calcCRC();
}

bool Command::isValid() {
	if(stx != STX)
		return false;
	if(etx != ETX)
		return false;
	if(header.len > MAX_PAYLOAD_LEN)
		return false;
	if(!checkCRC())
		return false;
	return true;
}

