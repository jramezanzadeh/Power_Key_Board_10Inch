/*
 * GetHeader.h
 *
 *  Created on: Sep 2, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef GETHEADER_H_
#define GETHEADER_H_

#include <State.h>

namespace CmdListenerNS {

class GetHeader: public State {
public:
	GetHeader(CommandListener *ctx);
	virtual ~GetHeader();

	void handleReceivedByte(uint8_t byte);

private:
	int readIndex;
	uint8_t *buff;
};

} /* namespace CmdListenerNS */

#endif /* GETHEADER_H_ */
