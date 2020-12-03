#pragma once
#include "GlobalConfig.h"

#include <iostream>
#include <Windows.h>

#include<MMSystem.h>
#pragma comment(lib, "Winmm.lib")


class GamepadMapper {
private:
	IntVector3 PosInfo;
	unsigned int BtnInfo;
	unsigned DPadInfo;
public:
	GamepadMapper() {
		PosInfo = { 0,0,0 };
		BtnInfo = 0;
	}
	void updateAllKey() {
		JOYINFOEX joyinfo;
		joyinfo.dwSize = sizeof(JOYINFOEX);
		joyinfo.dwFlags = JOY_RETURNALL;
		if (joyGetNumDevs() >= 1) {
			MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfo);
			if (joyreturn == JOYERR_NOERROR) {
				PosInfo = { (int)joyinfo.dwXpos, (int)joyinfo.dwYpos, (int)joyinfo.dwZpos };
				BtnInfo = (int)joyinfo.dwButtons;
				DPadInfo = (int)joyinfo.dwPOV;
			}
		}
	}
	bool getButtonState(GamepadButton gb) {
		switch (gb)
		{
		case A:
			return BtnInfo & 1;
		case B:
			return (BtnInfo >> 1) & 1;
		case X:
			return (BtnInfo >> 2) & 1;
		case Y:
			return (BtnInfo >> 3) & 1;
		case L:
			return (BtnInfo >> 8) & 1;
		case R:
			return (BtnInfo >> 9) & 1;
		case LB:
			return (BtnInfo >> 4) & 1;
		case RB:
			return (BtnInfo >> 5) & 1;
		case Start:
			return (BtnInfo >> 7) & 1;
		case Back:
			return (BtnInfo >> 6) & 1;
		default:
			return 0;
		}
		return 0;
	}
	int getDPad() { return DPadInfo; }
	int getXPos() { return PosInfo.vx; }
	int getYPos() { return PosInfo.vy; }
	int getZPos() { return PosInfo.vz; }
};