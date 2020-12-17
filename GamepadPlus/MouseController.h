#pragma once
#include "GlobalConfig.h"

class MouseController {
private:
	int CursorPos_x, CursorPos_y;
	int Window_x, Window_y;
	bool MbLeft, MbRight, MbMiddle;
public:
	MouseController();
	void systemMouseSet();
	void mouseGoto(int aim_x, int aim_y);
	void mouseMove(int aim_x, int aim_y, int speed);
	void mouseClick(bool mb_left = false, bool mb_right = false, bool mb_middle = false, int mb_middleUpDown = 0);
};
