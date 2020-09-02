#include "GamepadController.h"

GamepadController::GamepadController() {
	vspeed.vx = 0; vspeed.vy = 0;
	speed = 3 * SPEED_LEVEL;
	btn_A = false;
	btn_B = false;
	btn_X = false;
	btn_LB = false;
	btn_RB = false;
	btn_Start = false;
}

void GamepadController::updateAllKey() {
	JOYINFOEX joyinfoex;
	joyinfoex.dwSize = sizeof(JOYINFOEX);
	joyinfoex.dwFlags = JOY_RETURNALL;
	//读取手柄信息
	if (joyGetNumDevs() >= 1) {
		MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfoex);
		if (joyreturn == JOYERR_NOERROR) {

			vspeed.vx = ((double)(joyinfoex.dwXpos) - 32767) / (double)(32767 / speed);
			vspeed.vy = ((double)(joyinfoex.dwYpos) - 32767) / (double)(32767 / speed);
			btn_A = (joyinfoex.dwButtons & 1) == 1;
			btn_B = ((joyinfoex.dwButtons >> 1) & 1) == 1;
			btn_X = ((joyinfoex.dwButtons >> 2) & 1) == 1;
			btn_LB = ((joyinfoex.dwButtons >> 4) & 1) == 1;
			btn_RB = ((joyinfoex.dwButtons >> 5) & 1) == 1;
			btn_Start = ((joyinfoex.dwButtons >> 7) & 1) == 1;
			setSpeed(joyinfoex.dwPOV);

			if (btn_Start) {
				system("cls");

				std::cout << "--手柄操作信息--" << std::endl;

				std::cout << "L-Con" << std::endl;
				std::cout << "X坐标 : " << joyinfoex.dwXpos << std::endl;
				std::cout << "Y坐标 : " << joyinfoex.dwYpos << std::endl;

				std::cout << "R-Con" << std::endl;
				std::cout << "X坐标: " << joyinfoex.dwUpos << std::endl;
				std::cout << "Y坐标 : " << joyinfoex.dwRpos << std::endl;

				std::cout << "LT - RT : " << joyinfoex.dwZpos << std::endl;
				std::cout << "D-pad 信息 : " << joyinfoex.dwPOV << std::endl;
				std::cout << "按键信息 : " << joyinfoex.dwButtons << std::endl;
				std::cout << "按键数量 : " << joyinfoex.dwButtonNumber << std::endl;
				std::cout << std::endl;

				std::cout << "--鼠标模拟信息--" << std::endl;
				std::cout << "\033[33m横向位移：" << vspeed.vx << "   纵向位移: " << vspeed.vy << std::endl;
				std::cout << "速度: " << speed << std::endl;
				std::cout << "\033[32mA键-左键: " << btn_A << std::endl;
				std::cout << "\033[31mB键-右键: " << btn_B << std::endl;
				std::cout << "\033[1m\033[34mX键-中键: " << btn_X << std::endl;
				std::cout << "\033[37mLB键-滚轮上滚: " << btn_LB << std::endl;
				std::cout << "RB键-滚轮下滚: " << btn_RB << std::endl;
				std::cout << "Start键-更新控制台: " << btn_Start << std::endl;
			}
		}
		else {
			switch (joyreturn) {
			case JOYERR_PARMS:
				std::cout << "错误参数" << std::endl; break;
			case JOYERR_NOCANDO:
				std::cout << "请求未完成" << std::endl; break;
			case JOYERR_UNPLUGGED:
				std::cout << "未找到手柄" << std::endl; break;
			default:
				std::cout << "未知错误" << std::endl; break;;
			}
		}
	}
}

void GamepadController::setSpeed(int dwPOV) {
	if (dwPOV != 65535) {
		speed = dwPOV * SPEED_LEVEL / 9000 + SPEED_LEVEL;
	}
}

// I NEED LOMBOK

IntVector2 GamepadController::getVSpeed() {
	return vspeed;
}

bool GamepadController::getButton_A() {
	return btn_A;
}

bool GamepadController::getButton_B() {
	return btn_B;
}

bool GamepadController::getButton_X() {
	return btn_X;
}

bool GamepadController::getButton_LB() {
	return btn_LB;
}

bool GamepadController::getButton_RB() {
	return btn_RB;
}

int GamepadController::getSpeed() {
	return speed;
}