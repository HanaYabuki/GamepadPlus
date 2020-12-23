#include "gamepadmapper.h"


#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

GamepadMapper::GamepadMapper()
{
    XPos = YPos = ZPos = 0;
    BtnInfo = 0;
    DPadInfo = 0;
    padState = false;
}

void GamepadMapper::updateAllKey()
{
    JOYINFOEX joyinfo;
    joyinfo.dwSize = sizeof(JOYINFOEX);
    joyinfo.dwFlags = JOY_RETURNALL;
    if (joyGetNumDevs() >= 1) {
        MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfo);
        padState = joyreturn == JOYERR_NOERROR;
        if (padState) {
            XPos = (int)joyinfo.dwXpos;
            YPos = (int)joyinfo.dwYpos;
            ZPos = (int)joyinfo.dwZpos;
            BtnInfo = (int)joyinfo.dwButtons;
            DPadInfo = (int)joyinfo.dwPOV;
        }
    }
}

bool GamepadMapper::getButtonState(GamepadButton gb)
{
    int gbCode = (int)gb;
    return (BtnInfo >> gbCode) & 1;
}
