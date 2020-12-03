#pragma once
const int FPS = 60;
const int SPEED_LEVEL = 3;

struct IntVector2 {
	int vx, vy;
	void operator=(int tmp[2]) {
		vx = tmp[0]; vy = tmp[1];
	}
};

struct IntVector3 {
	int vx, vy, vz;
	void operator=(int tmp[3]) {
		vx = tmp[0]; vy = tmp[1]; vz = tmp[2];
	}
};

struct DoubleVector2 {
	double vx, vy;
	void operator=(double tmp[2]) {
		vx = tmp[0]; vy = tmp[1];
	}
};

enum GamepadButton {
	A, B, X, Y, L, R, LB, RB, Start, Back
};
