#include "GlobalConfig.h"
#include "GamepadMapper.h"
#include "MouseController.h"
#include "KeyboardController.h"

#include <iostream>
#include <Windows.h>

GamepadMapper gamepad;
MouseController mouse;
KeyboardController keyboard;
int speed;
int dpad;

int xyToDir(int x, int y) {
	double rad = atan2(y, x);
	return ((int)(rad * 180 / 3.141592653589793) + 360) % 360;
}

int mouseStep() {
	mouse.systemMouseSet();
	mouse.mouseClick(
		gamepad.getButtonState(GamepadButton::A),
		gamepad.getButtonState(GamepadButton::B),
		gamepad.getButtonState(GamepadButton::X),
		(gamepad.getZPos() - 32767) >> 11
	);
	mouse.mouseMove(
		(gamepad.getXPos()-32767) >> 14, 
		(gamepad.getYPos()-32767) >> 14, 
		speed
	);
	speed = 2 + (gamepad.getButtonState(GamepadButton::LB) ? -1 : 0) + (gamepad.getButtonState(GamepadButton::RB) ? 3 : 0);
	return 0;
}
int keyboardStep() {
	// int dirCode = xyToDir(gamepad.getRes1(), gamepad.getRes2());
	// std::cout << gamepad.getRes1() << std::endl;

	return 0;
}

int main(int argc, char* argv[]) {
	int timer = 1000 / FPS;
	int tFirst, tNow;
	tNow = tFirst = (int)GetTickCount64();
	speed = 1;
	dpad = 65535;
	while (true) {
		tFirst = tNow;
		tNow = (int)GetTickCount64();
		if (tNow - tFirst > 1000 / FPS) {
			timer > 0 ? timer-- : false;
		}
		if (tNow - tFirst < 1000 / FPS) {
			timer < 2000 / FPS ? timer++ : false;
		}
		gamepad.updateAllKey();
		if (gamepad.getPadState()) {
			mouseStep();
			keyboardStep();
		}
		Sleep(timer);
	}
}