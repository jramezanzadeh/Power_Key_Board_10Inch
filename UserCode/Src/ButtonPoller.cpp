/*
 * pollingButtonMonitor.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <ButtonPoller.h>
#include "iterator"
#include "UsbKeyboard.h"

ButtonPoller::ButtonPoller():
mKeyButtonMap(
		{{Key_AIS, Button(KEY1_GPIO_Port, KEY1_Pin)},
	{Key_Num1, Button(KEY2_GPIO_Port, KEY2_Pin)},
	{Key_Num2, Button(KEY3_GPIO_Port, KEY3_Pin)},
	{Key_Num3, Button(KEY4_GPIO_Port, KEY4_Pin)},
	{Key_VHF, Button(KEY5_GPIO_Port, KEY5_Pin)},
	{Key_Num4, Button(KEY6_GPIO_Port, KEY6_Pin)},
	{Key_Num5, Button(KEY7_GPIO_Port, KEY7_Pin)},
	{Key_Num6, Button(KEY8_GPIO_Port, KEY8_Pin)},
	{Key_SNR, Button(KEY9_GPIO_Port, KEY9_Pin)},
	{Key_Num7, Button(KEY10_GPIO_Port, KEY10_Pin)},
	{Key_Num8, Button(KEY11_GPIO_Port, KEY11_Pin)},
	{Key_Num9, Button(KEY12_GPIO_Port, KEY12_Pin)},
	{Key_ESP, Button(KEY13_GPIO_Port, KEY13_Pin)},
	{Key_NumDot, Button(KEY14_GPIO_Port, KEY14_Pin)},
	{Key_Num0, Button(KEY15_GPIO_Port, KEY15_Pin)},
	{Key_NumBackSpace, Button(KEY16_GPIO_Port, KEY16_Pin)},
	{Key_In, Button(KEY17_GPIO_Port, KEY17_Pin)},
	{Key_Menu, Button(KEY18_GPIO_Port, KEY18_Pin)},
	{Key_UP, Button(KEY19_GPIO_Port, KEY19_Pin)},
	{Key_Mark, Button(KEY20_GPIO_Port, KEY20_Pin)},
	{Key_OUT, Button(KEY21_GPIO_Port, KEY21_Pin)},
	{Key_Left, Button(KEY22_GPIO_Port, KEY22_Pin)},
	{Key_Right, Button(KEY23_GPIO_Port, KEY23_Pin)},
	{Key_Disp, Button(KEY24_GPIO_Port, KEY24_Pin)},
	{Key_Esp, Button(KEY25_GPIO_Port, KEY25_Pin)},
	{Key_Down, Button(KEY26_GPIO_Port, KEY26_Pin)},
	{Key_Ok, Button(KEY27_GPIO_Port, KEY27_Pin)}}) {
	// TODO Auto-generated constructor stub					/*S27*/

}

ButtonPoller::~ButtonPoller() {
	// TODO Auto-generated destructor stub
}

void ButtonPoller::run() {
	std::map<Keys, Button>::iterator it;
	for(it = mKeyButtonMap.begin(); it != mKeyButtonMap.end(); it++){
		Button::ButtonEvent event = it->second.getEvent();
		if(event == Button::PRESSED){
			keyboard.handleKeyEvent(it->first, KEY_PRESSED);
		}else if(event == Button::RELEASED){
			keyboard.handleKeyEvent(it->first, KEY_RELEASED);
		}
	}
}
