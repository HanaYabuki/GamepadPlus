#include "MouseController.h"

#include <Windows.h>
#include <conio.h>

#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define SQR(x) ((x) * (x))

MouseController::MouseController() {
	Window_x = (float)GetSystemMetrics(SM_CXSCREEN);
	Window_y = (float)GetSystemMetrics(SM_CYSCREEN);
	MbLeft = false;
	MbRight = false;
	MbMiddle = false;
	CursorPos_x = CursorPos_y = 0;
}

void MouseController::systemMouseSet()
{
	POINT point;
	GetCursorPos(&point);

	if (ABS((float)point.x - CursorPos_x) + ABS((float)point.y - CursorPos_y) >= 2.0F) {
		CursorPos_x = (float)point.x;
		CursorPos_y = (float)point.y;
		SetCursorPos((int)CursorPos_x, (int)CursorPos_y);
	}
}

void MouseController::mouseMove(float aim_x, float aim_y, float speed)
{
	CursorPos_x += aim_x * speed;
	CursorPos_y += aim_y * speed;
	
	if (CursorPos_x > Window_x) {
		CursorPos_x = Window_x;
	}
	if (CursorPos_x < 0) {
		CursorPos_x = 0;
	}
	
	if (CursorPos_y > Window_y) {
		CursorPos_y = Window_y;
	}
	if (CursorPos_y < 0) {
		CursorPos_y = 0;
	}

	SetCursorPos((int)CursorPos_x, (int)CursorPos_y);
}

void MouseController::mouseClick(bool mb_left, bool mb_right, bool mb_middle)
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
}

void MouseController::mouseRoll(int mb_middleUpDown)
{
	if (mb_middleUpDown != 0) {
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = mb_middleUpDown;
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));
	}
}
