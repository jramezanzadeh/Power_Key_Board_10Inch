/*
 * GetHeader.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "GetHeader.h"
#include "IdleState.h"
#include "GetPayload.h"
#include "GetFooter.h"
#include "Debug.h"

namespace CmdListenerNS {

GetHeader::GetHeader(CommandListener *ctx):State(ctx){
	// TODO Auto-generated constructor stub
	readIndex  = 0;
	buff = (uint8_t*)&mCtx->getCurrentCmd().header;
	debuger << "GetHeader" << endl;
}

GetHeader::~GetHeader() {
	// TODO Auto-generated destructor stub
}

void GetHeader::handleReceivedByte(uint8_t byte) {
	buff[readIndex++] = byte;
	if(readIndex == sizeof(Header)){ // header is received
		if(mCtx->getCurrentCmd().header.len > MAX_PAYLOAD_LEN)
			mCtx->setState(new IdleState(mCtx));
		else if(mCtx->getCurrentCmd().header.len == 0)
			mCtx->setState(new GetFooter(mCtx));
		else
			mCtx->setState(new GetPayload(mCtx));

	}
}

} /* namespace CmdListenerNS */
