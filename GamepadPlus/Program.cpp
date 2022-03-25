#include <Windows.h>
#include <cmath>

#include "GlobalConfig.h"
#include "GamepadMapper.h"
#include "MouseController.h"
#include "Log.h"

GamepadMapper* gamepad;
MouseController* mouse;

float deltaTime;

int xyToDir(int x, int y) {
	double rad = atan2(y, x);
	return ((int)(rad * 180 / Pi) + 360) % 360;
}

void Update() 
{
	float speed = 0.00002F
		/ (gamepad->getButtonState(GamepadButton::LB) ? 3.0F : 1.0F)
		* (gamepad->getButtonState(GamepadButton::RB) ? 3.0F : 1.0F)
		* deltaTime;

	mouse->systemMouseSet();

	float aim_x = (float)gamepad->getXPos() - 32767.0F;
	float aim_y = (float)gamepad->getYPos() - 32767.0F;
	if (SQR(ABS(aim_x)) + SQR(ABS(aim_y)) > SQR(8192.0F)) {
		mouse->mouseMove(aim_x, aim_y, speed);
	}

	mouse->mouseClick(
		gamepad->getButtonState(GamepadButton::A),
		gamepad->getButtonState(GamepadButton::B),
		gamepad->getButtonState(GamepadButton::X)
	);
}

void FixedUpdate()
{
	mouse->mouseRoll(
		(float) FIXED_DELTA_TIME * 0.00005F * ((gamepad->getZPos() - 32767))
	);
}


int main(int argc, char* argv[]) {
	hello();
	
	gamepad = new GamepadMapper();
	mouse = new MouseController();

	int tFirst, tNow;
	tNow = tFirst = (int)GetTickCount64();

	int fixTimer = 0;

	bool remain = true;

	while (remain) {
		gamepad->updateAllKey();

		if (!gamepad->isConnected()) {
			Sleep(RECONNECT_STEP);
			break;
		}


		deltaTime = float(tNow - tFirst);

		Update();
		fixTimer += deltaTime;
		while (fixTimer >= FIXED_DELTA_TIME) {
			fixTimer -= FIXED_DELTA_TIME;
			FixedUpdate();
		}

		remain = ! gamepad->getButtonState(GamepadButton::Start);

		// Sleep(STEP);
		while ((int)GetTickCount64() - tFirst < STEP) {
			Sleep(5);
		}

		tFirst = tNow;
		tNow = (int)GetTickCount64();
	}

	delete gamepad, mouse;
	return 0;
}
