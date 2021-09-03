/*
 * GetPayload.h
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef GETPAYLOAD_H_
#define GETPAYLOAD_H_

#include <State.h>

namespace CmdListenerNS {

class GetPayload: public State {
public:
	GetPayload(CommandListener *ctx);
	virtual ~GetPayload();

	void handleReceivedByte(uint8_t byte);
private:
	int paylodLen;
	uint8_t *buff;
	int readIndex;
};

} /* namespace CmdListenerNS */

#endif /* GETPAYLOAD_H_ */
