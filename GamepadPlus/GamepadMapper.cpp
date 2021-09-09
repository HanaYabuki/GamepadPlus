#include "GamepadMapper.h"

#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib, "Winmm.lib")

GamepadMapper::GamepadMapper()
{
	XPos = YPos = ZPos = RPos = UPos = VPos = 0;
	res1 = res2 = 0;
	BtnInfo = 0;
	DPadInfo = 0;
	connected = false;
}

void GamepadMapper::updateAllKey()
{
	JOYINFOEX joyinfo;
	joyinfo.dwSize = sizeof(JOYINFOEX);
	joyinfo.dwFlags = JOY_RETURNALL;
	if (joyGetNumDevs() >= 1) {
		connected = true;
		MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfo);
		if (joyreturn == JOYERR_NOERROR) {
			XPos = (int)joyinfo.dwXpos;
			YPos = (int)joyinfo.dwYpos;
			ZPos = (int)joyinfo.dwZpos;
			RPos = (int)joyinfo.dwRpos;
			UPos = (int)joyinfo.dwUpos;
			VPos = (int)joyinfo.dwVpos;
			BtnInfo = (int)joyinfo.dwButtons;
			DPadInfo = (int)joyinfo.dwPOV;
			res1 = joyinfo.dwReserved1;
			res2 = joyinfo.dwReserved2;
		}
	}
	else {
		connected = false;
	}
}

bool GamepadMapper::isConnected()
{
	return connected;
}

bool GamepadMapper::getButtonState(GamepadButton gb)
{
	int gbCode = (int)gb;
	return (BtnInfo >> gbCode) & 1;
}