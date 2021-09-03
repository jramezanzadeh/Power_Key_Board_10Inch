/*
 * CommandListenerState.h
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef STATE_H_
#define STATE_H_
#include "CommandListener.h"

namespace CmdListenerNS{

#include "stdint.h"
#define STX				0x03
#define ETX				0x02


class State {
public:
	State(CommandListener *ctx);
	virtual ~State();

	virtual void handleReceivedByte(uint8_t byte) = 0;

protected:
	CommandListener *mCtx;
};

}
#endif /* STATE_H_ */
