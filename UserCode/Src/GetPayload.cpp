/*
 * GetPayload.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "GetPayload.h"
#include "GetFooter.h"
#include "Debug.h"

namespace CmdListenerNS {

GetPayload::GetPayload(CommandListener *ctx):State(ctx) {
	// TODO Auto-generated constructor stub
	paylodLen = mCtx->getCurrentCmd().header.len;
	buff = mCtx->getCurrentCmd().paylaod;
	readIndex = 0;
	debuger << "GetPayload" << endl;
}

GetPayload::~GetPayload() {
	// TODO Auto-generated destructor stub
}

void GetPayload::handleReceivedByte(uint8_t byte) {
	buff[readIndex++] = byte;
	if(readIndex == paylodLen){
		mCtx->setState(new GetFooter(mCtx));
	}
}

} /* namespace CmdListenerNS */
