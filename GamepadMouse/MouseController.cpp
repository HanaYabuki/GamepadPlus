#include "MouseController.h"

MouseController::MouseController() {
	window_x = GetSystemMetrics(SM_CXSCREEN);
	window_y = GetSystemMetrics(SM_CYSCREEN);
	x = window_x / 2;
	y = window_y / 2;
	lastmb_left = false;
	lastmb_right = false;
	lastmb_middle = false;
	mouseGoto(x, y);
}

void MouseController::mouseSet(int x, int y) {
	this->x = x;
	this->y = y;
}

void MouseController::mouseMove(IntVector2 vspd) {
	mouseGoto(x + vspd.vx, y + vspd.vy);
}

void MouseController::mouseMove(int aim_x, int aim_y) {
	mouseGoto(x + aim_x, y + aim_y);
}

void MouseController::mouseGoto(int aim_x, int aim_y){
	x = aim_x < window_x&&aim_x>0 ? aim_x : x;
	y = aim_y < window_y&&aim_y>0 ? aim_y : y;
	SetCursorPos(x, y);
}

void MouseController::mouseClick(int speed, bool mb_left, bool mb_right, bool mb_middle, bool mb_middleUp, bool mb_middleDown) {
	if (mb_left != lastmb_left) {
		mouse_event(mb_left ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		lastmb_left = mb_left;
	}
	if (mb_right != lastmb_right) {
		mouse_event(mb_right ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		lastmb_right = mb_right;
	}
	if (mb_middle != lastmb_middle) {
		mouse_event(mb_middle ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
		lastmb_middle = mb_middle;
	}
	if (mb_middleDown) {
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = -speed * 10;
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));
	}
	if (mb_middleUp) {
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = speed * 10;
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));
	}
}
