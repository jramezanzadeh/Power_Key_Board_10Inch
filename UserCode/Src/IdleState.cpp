/*
 * IdleState.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "IdleState.h"
#include "GetHeader.h"
#include "Debug.h"

namespace CmdListenerNS {

IdleState::IdleState(CommandListener *ctx):State(ctx) {
	// TODO Auto-generated constructor stub
	debuger << "GetHeader" << endl;
}

IdleState::~IdleState() {
	// TODO Auto-generated destructor stub
}

void IdleState::handleReceivedByte(uint8_t byte) {
	if(byte == STX){
		mCtx->getCurrentCmd().reset();
		mCtx->getCurrentCmd().stx = byte;
		mCtx->setState(new GetHeader(mCtx));
	}
}

} /* namespace CmdListenerNS */
