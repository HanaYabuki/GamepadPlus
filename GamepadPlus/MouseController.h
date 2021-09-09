#pragma once
#include "GlobalConfig.h"

class MouseController {
private:
	float CursorPos_x, CursorPos_y;
	float Window_x, Window_y;
	bool MbLeft, MbRight, MbMiddle;
public:
	MouseController();
	void systemMouseSet();
	void mouseMove(float aim_x, float aim_y, float speed);
	void mouseClick(bool mb_left = false, bool mb_right = false, bool mb_middle = false, int mb_middleUpDown = 0);
};
