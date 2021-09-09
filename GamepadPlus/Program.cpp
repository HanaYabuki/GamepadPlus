#include "GlobalConfig.h"
#include "GamepadMapper.h"
#include "MouseController.h"

#include <iostream>
#include <Windows.h>

GamepadMapper* gamepad;
MouseController* mouse;

float deltaTime;

int xyToDir(int x, int y) {
	double rad = atan2(y, x);
	return ((int)(rad * 180 / Pi) + 360) % 360;
}

int mouseStep(float delta) {
	float speed = 0.00002F
			/ (gamepad->getButtonState(GamepadButton::LB) ? 3.0F : 1.0F)
			* (gamepad->getButtonState(GamepadButton::RB) ? 3.0F : 1.0F)
			* delta;

	mouse->systemMouseSet();

	mouse->mouseClick(
		gamepad->getButtonState(GamepadButton::A),
		gamepad->getButtonState(GamepadButton::B),
		gamepad->getButtonState(GamepadButton::X),
		(gamepad->getZPos() - 32767) >> 11
	);

	float aim_x = (float)gamepad->getXPos() - 32767.0F;
	float aim_y = (float)gamepad->getYPos() - 32767.0F;
	if (SQR(ABS(aim_x)) + SQR(ABS(aim_y)) > SQR(8192.0F)) {
		mouse->mouseMove(aim_x, aim_y, speed);
	}
	
	return 0;
}


int main(int argc, char* argv[]) {
	gamepad = new GamepadMapper();
	mouse = new MouseController();

	int tFirst, tNow;
	tNow = tFirst = (int)GetTickCount64();

	bool remain = true;

	while (remain) {
		gamepad->updateAllKey();

		if (!gamepad->isConnected()) {
			Sleep(RECONNECT_STEP);
			break;
		}

		tFirst = tNow;
		tNow = (int)GetTickCount64();

		deltaTime = float(tNow - tFirst);
		mouseStep(deltaTime);

		remain = ! gamepad->getButtonState(GamepadButton::Start);

		Sleep(STEP);
	}

	delete gamepad, mouse;
	return 0;
}
