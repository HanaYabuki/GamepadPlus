#ifndef GAMEPADMAPPEREX_H
#define GAMEPADMAPPEREX_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGamepad/QGamepad>

enum class GamepadButtonEX {
    A, B, X, Y, LB, RB, Back, Start, L, R
};

enum class GamepadDpadEX {
    up, down, left, right
};

class GamepadMapperEX : public QObject
{
private:
    QGamepad *gamepad;
    int XPos, YPos, ZPosLT, ZPosRT, XRotate, YRotate;
    bool DPadUp, DPadDown, DPadLeft, DPadRight;
    bool BtnA, BtnB, BtnX, BtnY, BtnLB, BtnRB, BtnBack, BtnStart, BtnL, BtnR;
public:
    GamepadMapperEX();
    ~GamepadMapperEX();

    void updateAllKey(){};

    bool getPadState();
    bool getButtonState(GamepadButtonEX gb);
    bool getDPad(GamepadDpadEX gd);

    int getXPos();
    int getYPos();
    int getZPos();

    int getXRotate();
    int getYRotate();
};

#endif // GAMEPADMAPPEREX_H
