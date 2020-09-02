#include <iostream>
#include <future>

#include "GamepadController.h"
#include "MouseController.h"

GamepadController joy;
MouseController mouse;

void mainThread() {
	joy.updateAllKey();
	POINT point;
	GetCursorPos(&point);
	mouse.mouseSet(point.x, point.y);
	mouse.mouseClick(
		joy.getSpeed(),
		joy.getButton_A(),
		joy.getButton_B(),
		joy.getButton_X(),
		joy.getButton_LB(),
		joy.getButton_RB()
	);
	mouse.mouseMove(joy.getVSpeed());
}

int main(int argc, char* argv[]) {
	std::future<void> th;
	int iTimer = 1000 / FPS;
	long tNow, tFirst;
	tFirst = GetTickCount();
	tNow = tFirst;

	std::cout << "手柄成功连接" << std::endl << "按住Start更新控制台信息" << std::endl;

	while (1) {
		tFirst = tNow;
		tNow = GetTickCount();
		if (tNow - tFirst > 1000 / FPS) {
			iTimer > 0 ? iTimer-- : false;
		}
		if (tNow - tFirst < 1000 / FPS) {
			iTimer < 2000 / FPS ? iTimer++ : false;
		}
		th = std::async(mainThread);
		th.get();
		mainThread();
		Sleep(iTimer);
	}
}