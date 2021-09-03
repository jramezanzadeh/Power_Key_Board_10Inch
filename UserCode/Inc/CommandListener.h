/*
 * CommandListener.h
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef COMMANDLISTENER_H_
#define COMMANDLISTENER_H_

#include "Serial.hpp"

#define TX_BUFF_LEN		50
#define MAX_PAYLOAD_LEN	10


class Header{
public:
	uint8_t cmd; // command
	uint8_t len; //payload len
};

class Command{
public:
	uint8_t 	stx;
	Header 		header;
	uint8_t 	paylaod[MAX_PAYLOAD_LEN];
	uint8_t		crc;
	uint8_t		etx;
	Command();
	bool isValid();
	void reset();
	void updateCRC();
	int toArray(uint8_t *buff);
private:
	uint8_t calcCRC();
	bool checkCRC();
};

namespace CmdListenerNS{
class State;
}
class VariableContrastLed;
class CommandListener {
public:

	CommandListener(VariableContrastLed *bgLedCtrl);
	virtual ~CommandListener();

	void init();
	void run();
	void setState(CmdListenerNS::State *state);
	void writeByte(uint8_t byte);
	void setBgLedBrightness(uint8_t brightnessPercentage);

	Command& getCurrentCmd(){
		return mCmd;
	}

private:
	Serial mPort;
	uint8_t mTxBuff[TX_BUFF_LEN];
	int mTxRdIndex;
	int mTxWrIndex;
	uint8_t mByte;
	Command mCmd;
	CmdListenerNS::State *mCurrentState;

	VariableContrastLed *mBgLedCtrl;

};

#endif /* COMMANDLISTENER_H_ */
