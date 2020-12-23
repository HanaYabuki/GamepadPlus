    #include "gamepadmapperex.h"

#include <QDebug>
#include <QtGamepad/QGamepadManager>

GamepadMapperEX::GamepadMapperEX()
{
    gamepad = new QGamepad();
    XPos = YPos = XRotate = YRotate = 32768;
    ZPosLT = ZPosRT = 0;
    DPadUp = DPadDown = DPadLeft = DPadRight = false;
    BtnA = BtnB = BtnX = BtnY = BtnL = BtnR = BtnBack = BtnStart = BtnLB = BtnRB = false;

    // JoyCon
    connect(gamepad, &QGamepad::axisLeftXChanged, this, [=](double value){
        this->XPos = value * 32768 + 32767;
    });
    connect(gamepad, &QGamepad::axisLeftYChanged, this, [=](double value){
        this->YPos = value * 32768 + 32767;
    });
    connect(gamepad, &QGamepad::axisRightXChanged, this, [=](double value){
        this->XRotate = value * 32768 + 32767;
    });
    connect(gamepad, &QGamepad::axisRightYChanged, this, [=](double value){
        this->YRotate = value * 32768 + 32767;
    });

    // Right Button
    connect(gamepad, &QGamepad::buttonAChanged, this, [=](bool pressed){
        this->BtnA = pressed;
    });
    connect(gamepad, &QGamepad::buttonBChanged, this, [=](bool pressed){
        this->BtnB = pressed;
    });
    connect(gamepad, &QGamepad::buttonXChanged, this, [=](bool pressed){
        this->BtnX = pressed;
    });
    connect(gamepad, &QGamepad::buttonYChanged, this, [=](bool pressed){
        this->BtnY = pressed;
    });

    // Back Button
    connect(gamepad, &QGamepad::buttonL1Changed, this, [=](bool pressed){
        this->BtnLB = pressed;
    });
    connect(gamepad, &QGamepad::buttonR1Changed, this, [=](bool pressed){
        this->BtnRB = pressed;
    });
    connect(gamepad, &QGamepad::buttonL2Changed, this, [=](double value){
        this->ZPosLT = value * 32768;
    });
    connect(gamepad, &QGamepad::buttonR2Changed, this, [=](double value){
        this->ZPosRT = value * 32768;
    });

    // DPad
    connect(gamepad, &QGamepad::buttonUpChanged, this, [=](bool pressed){
        this->DPadUp = pressed;
    });
    connect(gamepad, &QGamepad::buttonDownChanged, this, [=](bool pressed){
        this->DPadDown = pressed;
    });
    connect(gamepad, &QGamepad::buttonLeftChanged, this, [=](bool pressed){
        this->DPadLeft = pressed;
    });
    connect(gamepad, &QGamepad::buttonRightChanged, this, [=](bool pressed){
        this->DPadRight = pressed;
    });

    // Function Button
    connect(gamepad, &QGamepad::buttonSelectChanged, this, [=](bool pressed){
        this->BtnBack = pressed;
    });
    connect(gamepad, &QGamepad::buttonStartChanged, this, [=](bool pressed){
        this->BtnStart = pressed;
    });
    connect(gamepad, &QGamepad::buttonL3Changed, this, [=](bool pressed){
        this->BtnL = pressed;
    });
    connect(gamepad, &QGamepad::buttonR3Changed, this, [=](bool pressed){
        this->BtnR = pressed;
    });
}

GamepadMapperEX::~GamepadMapperEX()
{
    delete gamepad;
}

bool GamepadMapperEX::getPadState()
{
    return gamepad->isConnected();
}

bool GamepadMapperEX::getButtonState(GamepadButtonEX gb)
{
    switch (gb) {
    case GamepadButtonEX::A :
        return BtnA;
    case GamepadButtonEX::B :
        return BtnB;
    case GamepadButtonEX::X :
        return BtnX;
    case GamepadButtonEX::Y :
        return BtnY;
    case GamepadButtonEX::LB :
        return BtnLB;
    case GamepadButtonEX::RB :
        return BtnRB;
    case GamepadButtonEX::Back :
        return BtnBack;
    case GamepadButtonEX::Start :
        return BtnStart;
    case GamepadButtonEX::L :
        return BtnL;
    case GamepadButtonEX::R :
        return BtnR;
    default:
        return false;
    }
}

bool GamepadMapperEX::getDPad(GamepadDpadEX gd)
{
    switch(gd) {
    case GamepadDpadEX::up :
        return DPadUp;
    case GamepadDpadEX::down :
        return DPadDown;
    case GamepadDpadEX::left :
        return DPadLeft;
    case GamepadDpadEX::right :
        return DPadRight;
    default:
        return 0;
    }
}

int GamepadMapperEX::getXPos()
{
    return XPos;
}

int GamepadMapperEX::getYPos()
{
    return YPos;
}

int GamepadMapperEX::getZPos()
{
    return ZPosLT - ZPosRT + 32767;
}

int GamepadMapperEX::getXRotate()
{
    return XRotate;
}

int GamepadMapperEX::getYRotate()
{
    return YRotate;
}
