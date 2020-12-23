#include "keyboardcontroller.h"

#pragma comment(lib, "user32.lib")
#include <Windows.h>

KeyboardController::KeyboardController()
{

}

void KeyboardController::keyboardPress(char keycode)
{
    keybd_event(keycode, 0, 0, 0);
    keybd_event(keycode, 0, 0x0002, 0);
}

void KeyboardController::keyboardPress(KeyCode keycode, bool press)
{
    keybd_event((int)(keycode), 0, (press ? 0 : 0x0002) , 0);
}

bool KeyboardController::getKeyState(char keycode)
{
    int state = GetAsyncKeyState(keycode);
    return state & 0x8000 ? true : false;
}

bool KeyboardController::getKeyState(KeyCode keycode)
{
    return getKeyState((int)keycode);
}
