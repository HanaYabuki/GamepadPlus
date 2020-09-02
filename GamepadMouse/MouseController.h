#pragma once
#include "GlobalSettings.h"

#include <Windows.h>
#include <conio.h>

class MouseController {
	int x, y, window_x, window_y;
	bool lastmb_left, lastmb_right, lastmb_middle;
public:
	MouseController();
	void mouseSet(
		int x,
		int y
	);
	void mouseMove(
		IntVector2 vspd
	);
	void mouseMove(
		int aim_x,
		int aim_y
	);
	void mouseGoto(
		int aim_x,
		int aim_y
	);
	void mouseClick(
		int speed,
		bool mb_left,
		bool mb_right,
		bool mb_middle,
		bool mb_middleUp,
		bool mb_middleDown
	);
};