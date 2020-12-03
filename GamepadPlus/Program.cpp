#include "GlobalConfig.h"
#include "GamepadMapper.h"
#include "MouseController.h"

#include <iostream>
#include <future>

GamepadMapper gamepad;
MouseController mouse;
int speed;

int step() {
	gamepad.updateAllKey();
	mouse.systemMouseSet();
	mouse.mouseClick(
		gamepad.getButtonState(A),
		gamepad.getButtonState(B),
		gamepad.getButtonState(X),
		(gamepad.getZPos() - 32767) / 4096 * speed
	);
	mouse.mouseMove(
		(gamepad.getXPos()-32767)/4096, 
		(gamepad.getYPos()-32767)/4096, 
		speed
	);
	speed = gamepad.getDPad() == 65535 ? speed : (gamepad.getDPad() / 9000 + 1);
	return 0;
}

int main(int argc, char* argv[]) {
	std::future<int> th;
	int timer = 1000 / FPS;
	long tFirst, tNow;
	tNow = tFirst = GetTickCount();
	while (true) {
		tFirst = tNow;
		tNow = GetTickCount();
		if (tNow - tFirst > 1000 / FPS) {
			timer > 0 ? timer-- : false;
		}
		if (tNow - tFirst < 1000 / FPS) {
			timer < 2000 / FPS ? timer++ : false;
		}
		th = std::async(step);
		th.get();
		Sleep(timer);
	}
}