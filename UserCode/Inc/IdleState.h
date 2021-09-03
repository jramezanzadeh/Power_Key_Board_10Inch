/*
 * IdleState.h
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef IDLESTATE_H_
#define IDLESTATE_H_

#include <CommandListener.h>
#include "State.h"

namespace CmdListenerNS {

class IdleState: public State {
public:
	IdleState(CommandListener *ctx);
	virtual ~IdleState();

	void handleReceivedByte(uint8_t byte);
};

} /* namespace CmdListenerNS */

#endif /* IDLESTATE_H_ */
