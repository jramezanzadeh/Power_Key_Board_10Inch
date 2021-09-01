/*
 * UsbKeyboard.cpp
 *
 *  Created on: May 31, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "UsbKeyboard.h"
#include "Debug.h"

UsbKeyboard::UsbKeyboard() {
	// TODO Auto-generated constructor stub
	mUsbDevice = 0;
	mReadIndex = 0;
	mWriteIndex = 0;
	mState = IDLE;
	mPollingInterval = 0;
	mStartPollingTime = 0;


	mKeysMap[Key_AIS] 			= USB_HID_KEY_F1; 		// AIS/F1
	mKeysMap[Key_Num1] 			= USB_HID_KEYPAD_1;		// 1
	mKeysMap[Key_Num2] 			= USB_HID_KEYPAD_2;		// 2
	mKeysMap[Key_Num3] 			= USB_HID_KEY_3;		// 3
	mKeysMap[Key_VHF] 			= USB_HID_KEY_F2; 		// VHF F2
	mKeysMap[Key_Num4] 			= USB_HID_KEYPAD_4;		// 4
	mKeysMap[Key_Num5] 			= USB_HID_KEYPAD_5;		// 5
	mKeysMap[Key_Num6] 			= USB_HID_KEYPAD_6;		// 6
	mKeysMap[Key_SNR] 			= USB_HID_KEY_F3;		// SNR F3
	mKeysMap[Key_Num7] 			= USB_HID_KEYPAD_7;		// 7
	mKeysMap[Key_Num8] 			= USB_HID_KEYPAD_8; 	// 8
	mKeysMap[Key_Num9] 			= USB_HID_KEYPAD_9; 	// 9
	mKeysMap[Key_ESP] 			= USB_HID_KEY_F4;		// ESP
	mKeysMap[Key_NumDot] 		= USB_HID_KEYPAD_PERIOD;// dot(.)
	mKeysMap[Key_Num0] 			= USB_HID_KEYPAD_0;		// 0
	mKeysMap[Key_NumBackSpace] 	= USB_HID_KEY_BACKSPACE;// BackSpace
	mKeysMap[Key_In] 			= USB_HID_KEYPAD_PLUS;	// In +
	mKeysMap[Key_Menu] 			= USB_HID_KEY_F8;		// Menu
	mKeysMap[Key_UP] 			= USB_HID_KEY_UP;		// /\ up
	mKeysMap[Key_Mark] 			= USB_HID_KEY_F9;		// Mark
	mKeysMap[Key_OUT] 			= USB_HID_KEYPAD_MINUS;	// Out -
	mKeysMap[Key_Left] 			= USB_HID_KEY_LEFT;		// < Left
	mKeysMap[Key_Right] 		= USB_HID_KEY_RIGHT;	// > Right
	mKeysMap[Key_Disp] 			= USB_HID_KEY_F7;		// Power/Disp
	mKeysMap[Key_Esp] 			= USB_HID_KEY_ESC;		// Escape
	mKeysMap[Key_Down] 			= USB_HID_KEY_DOWN;		// \/Down
	mKeysMap[Key_Ok] 			= USB_HID_KEY_ENTER;	// Enter
	mKeysMap[Key_Encoder_CW] 	= USB_HID_KEY_PAGE_UP;	// Encoder CW
	mKeysMap[Key_Encoder_CCW] 	= USB_HID_KEY_PAGE_DOWN;// Encoder CCW
	mKeysMap[Key_Encoder_Press] = USB_HID_KEYPAD_ENTER;	// Encoder Press

}


UsbKeyboard::~UsbKeyboard() {
	// TODO Auto-generated destructor stub
}

void UsbKeyboard::sendMediaKey(uint8_t key) {

	mediaReport.id = MEDIA_REPORT_ID;
	mediaReport.keys = key;

	sendBuff((uint8_t*)&mediaReport, sizeof(MediaHID_t));
}

void UsbKeyboard::sendStandardKey(uint8_t modifier, uint8_t key1, uint8_t key2,
		uint8_t key3) {
	keyReport.id = KEYBOARD_REPORT_ID;
	keyReport.modifiers = modifier;
	keyReport.key1 = key1;
	keyReport.key2 = key2;
	keyReport.key3 = key3;

	sendBuff((uint8_t*)&keyReport, sizeof(KeyboardHID_t));
}

void UsbKeyboard::releaseMediaKey() {
	sendMediaKey(0);
}

void UsbKeyboard::releaseStandardKey() {
	sendStandardKey(0,0,0,0);
}

void UsbKeyboard::releaseAllKey() {
	releaseMediaKey();
	HAL_Delay(mPollingInterval);
	releaseStandardKey();
}

UsbKeyboard& UsbKeyboard::instance() {
	static UsbKeyboard _keyboard;
	return _keyboard;
}

void UsbKeyboard::init(USBD_HandleTypeDef* usbDevice) {
	if(!usbDevice)
		return;
	mUsbDevice = usbDevice;
	mPollingInterval = USBD_HID_GetPollingInterval(mUsbDevice);

}

void UsbKeyboard::handleKeyEvent(int keyId, KeyEventType eventType) {
	// save event
	mEventList[mWriteIndex].keyId = keyId;
	mEventList[mWriteIndex].type = eventType;
	mWriteIndex += 1;
	mWriteIndex %= BUFF_SIZE;
}

void UsbKeyboard::run(void) {
	//TODO: return if it isn't initialized correctly
	switch (mState) {
		case IDLE:
			if(isEventExist())
				handleBufferedKey();
			break;
		case WAIT_POLLING_INTERVAL:
			if(isPollingTimeElapsed())
				mState = IDLE;
			break;
		default:
			break;
	}
}

void UsbKeyboard::sendStandardKey(KeyboardHID_t* key) {
	sendBuff((uint8_t*)key, sizeof(KeyboardHID_t));
}

bool UsbKeyboard::isEventExist() {
	return mWriteIndex != mReadIndex;
}

void UsbKeyboard::notify() {
	for(int i = 0; i < (int)mObserverList.size(); i++)
		mObserverList[i]->keyEvent(mEventList[mReadIndex].keyId, mEventList[mReadIndex].type);
}

void UsbKeyboard::sendBuff(uint8_t* buff, int len) {

	//TODO handle Errors
	USBD_HID_SendReport(mUsbDevice, buff, len);
	mState = WAIT_POLLING_INTERVAL;
	mStartPollingTime = HAL_GetTick();
}

void UsbKeyboard::handleBufferedKey() {
	switch (mEventList[mReadIndex].type) {
	case KEY_PRESSED:
		sendStandardKey(0, mKeysMap[mEventList[mReadIndex].keyId]);
		Debug::getInstance().log("press key[%d]\r\n", mEventList[mReadIndex].keyId);
		break;
	case KEY_RELEASED:
		releaseStandardKey();
		Debug::getInstance().log("release key[%d]\r\n", mEventList[mReadIndex].keyId);
		break;
	default:
		Debug::getInstance() << "unhandled\r\n";
		break;
	}
	notify();
	mReadIndex++;
	mReadIndex %= BUFF_SIZE;
}

bool UsbKeyboard::isPollingTimeElapsed() {
	return (HAL_GetTick() - mStartPollingTime > mPollingInterval);
}
