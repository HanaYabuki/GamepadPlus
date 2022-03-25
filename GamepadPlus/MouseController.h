#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

#include "GlobalConfig.h"

class MouseController {
private:
	float CursorPos_x, CursorPos_y;
	float Window_x, Window_y;
	bool MbLeft, MbRight, MbMiddle;
public:
	MouseController();
	void systemMouseSet();
	void mouseMove(
		float aim_x,
		float aim_y, 
		float speed
	);
	void mouseClick(
		bool mb_left, 
		bool mb_right, 
		bool mb_middle
	);
	void mouseRoll(
		int mb_middleUpDown
	);
};

#endif // !MOUSE_CONTROLLER_H
