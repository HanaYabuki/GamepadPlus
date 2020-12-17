#include "KeyboardController.h"

#include <Windows.h>
#include <conio.h>

void KeyboardController::keyPress(char keycode)
{
	keybd_event(keycode, 0, 0, 0);
	keybd_event(keycode, 0, KEYEVENTF_KEYUP, 0);
}