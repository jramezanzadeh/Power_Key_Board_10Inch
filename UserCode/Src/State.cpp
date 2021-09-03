/*
 * CommandListenerState.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "State.h"
#include "IdleState.h"

namespace CmdListenerNS{


State::State(CommandListener *ctx) {
	// TODO Auto-generated constructor stub
	mCtx = ctx;
}

State::~State() {
	// TODO Auto-generated destructor stub
}

}

