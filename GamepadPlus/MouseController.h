#pragma once
#include "GlobalConfig.h"

#include <Windows.h>
#include <conio.h>

class MouseController {
private:
	IntVector2 CursorPos;
	int Window_x, Window_y;
	bool MbLeft, MbRight, MbMiddle;
public:
	MouseController() {
		Window_x = GetSystemMetrics(SM_CXSCREEN);
		Window_y = GetSystemMetrics(SM_CYSCREEN);
		MbLeft = false;
		MbRight = false;
		MbMiddle = false;
	}
	void systemMouseSet() {
		POINT point;
		GetCursorPos(&point);
		mouseGoto(point.x, point.y);
	}
	void mouseGoto(int aim_x, int aim_y) {
		CursorPos.vx = aim_x < Window_x&&aim_x>0 ? aim_x : CursorPos.vx;
		CursorPos.vy = aim_y < Window_y&&aim_y>0 ? aim_y : CursorPos.vy;
		SetCursorPos(CursorPos.vx, CursorPos.vy);
	}
	void mouseMove(int aim_x, int aim_y, int speed) {
		mouseGoto(CursorPos.vx + aim_x * speed, CursorPos.vy + aim_y * speed);
	}
	void mouseClick(bool mb_left = false, bool mb_right = false, bool mb_middle = false, int mb_middleUpDown = 0) {
		if (mb_left != MbLeft) {
			mouse_event(mb_left ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			MbLeft = mb_left;
		}
		if (mb_right != MbRight) {
			mouse_event(mb_right ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			MbRight = mb_right;
		}
		if (mb_middle != MbMiddle) {
			mouse_event(mb_middle ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
			MbMiddle = mb_middle;
		}
		if (mb_middleUpDown != 0) {
			INPUT input;
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_WHEEL;
			input.mi.mouseData = mb_middleUpDown;
			input.mi.dwExtraInfo = 0;
			SendInput(1, &input, sizeof(INPUT));
		}
	}
};