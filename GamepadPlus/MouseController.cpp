#include "MouseController.h"

#include <Windows.h>
#include <conio.h>

MouseController::MouseController() {
	Window_x = GetSystemMetrics(SM_CXSCREEN);
	Window_y = GetSystemMetrics(SM_CYSCREEN);
	MbLeft = false;
	MbRight = false;
	MbMiddle = false;
	CursorPos_x = CursorPos_y = 0;
}

void MouseController::systemMouseSet()
{
	POINT point;
	GetCursorPos(&point);
	mouseGoto(point.x, point.y);
}

void MouseController::mouseGoto(int aim_x, int aim_y)
{
	CursorPos_x = aim_x < Window_x&& aim_x>0 ? aim_x : CursorPos_x;
	CursorPos_y = aim_y < Window_y&& aim_y>0 ? aim_y : CursorPos_y;
	SetCursorPos(CursorPos_x, CursorPos_y);
}

void MouseController::mouseMove(int aim_x, int aim_y, int speed)
{
	mouseGoto(CursorPos_x + aim_x * speed, CursorPos_y + aim_y * speed);
}

void MouseController::mouseClick(bool mb_left, bool mb_right, bool mb_middle, int mb_middleUpDown)
{
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
