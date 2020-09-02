#pragma once
#include "GlobalSettings.h"

#include <iostream>
#include <Windows.h>

#include<MMSystem.h>
#pragma comment(lib, "Winmm.lib")

class GamepadController {
	IntVector2 vspeed;
	int speed;
	bool btn_A, btn_B, btn_X, btn_LB, btn_RB, btn_Start;
public:
	GamepadController();		// 构造函数
	void updateAllKey();			// 更新全按键状态
	void setSpeed(int dwPOV);		// 设置速度
	IntVector2 getVSpeed();
	bool getButton_A();
	bool getButton_B();
	bool getButton_X();
	bool getButton_LB();
	bool getButton_RB();
	int getSpeed();
};