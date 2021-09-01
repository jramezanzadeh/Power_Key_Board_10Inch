/*
 * KeyObserver.h
 *
 *  Created on: Jun 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef KEYOBSERVER_H_
#define KEYOBSERVER_H_

#include "stdint.h"
enum Keys{
	Key_AIS		= 1,		/*S1*/
	Key_Num1,				/*S2*/
	Key_Num2,				/*S3*/
	Key_Num3,           	/*S4*/
	Key_VHF,          		/*S5*/
	Key_Num4,          		/*S6*/
	Key_Num5,             	/*S7*/
	Key_Num6,             	/*S8*/
	Key_SNR,           		/*S9*/
	Key_Num7,           	/*S10*/
	Key_Num8,            	/*S11*/
	Key_Num9,           	/*S12*/
	Key_ESP,            	/*S13*/
	Key_NumDot,            	/*S14*/
	Key_Num0,           	/*S15*/
	Key_NumBackSpace,		/*S16*/
	Key_In,					/*S17*/
	Key_Menu,				/*S18*/
	Key_UP,					/*S19*/
	Key_Mark,				/*S20*/
	Key_OUT,				/*S21*/
	Key_Left,				/*S22*/
	Key_Right,				/*S23*/
	Key_Disp,				/*S24*/
	Key_Esp,				/*S25*/
	Key_Down,				/*S26*/
	Key_Ok,					/*S27*/
	Key_Encoder_CW,			/*Encoder Clockwise*/
	Key_Encoder_CCW,		/*Encoder Counter Clockwise*/
	Key_Encoder_Press		/*Encoder Click*/
};
enum KeyEventType{
	KEY_PRESSED = 0,
	KEY_RELEASED = 1,
};

class KeyObserver {
public:
	KeyObserver();
	virtual ~KeyObserver();

	virtual void keyEvent(uint8_t keyID, KeyEventType eventType) = 0;
};

#endif /* KEYOBSERVER_H_ */
