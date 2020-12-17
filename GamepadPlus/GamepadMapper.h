#pragma once
#include "GlobalConfig.h"

enum class GamepadButton {
	A, B, X, Y, LB, RB, Back, Start, L, R
};

class GamepadMapper {
private:
	int XPos, YPos, ZPos, RPos, UPos, VPos;
	int res1, res2;
	unsigned int BtnInfo;
	unsigned int DPadInfo;
	bool padState;
public:
	GamepadMapper();
	void updateAllKey();

	bool getPadState() { return padState; }
	bool getButtonState(GamepadButton gb);
	
	int getDPad() { return DPadInfo; }

	int getXPos() { return XPos; }
	int getYPos() { return YPos; }
	int getZPos() { return ZPos; }

	int getRPos() { return RPos; }
	int getUPos() { return UPos; }
	int getVPos() { return VPos; }

	int getRes1() { return res1; }
	int getRes2() { return res2; }
};
