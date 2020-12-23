#ifndef GAMEPADMAPPER_H
#define GAMEPADMAPPER_H

enum class GamepadButton {
    A, B, X, Y, LB, RB, Back, Start, L, R
};

class GamepadMapper {
private:
    int XPos, YPos, ZPos;
    unsigned int BtnInfo;
    unsigned int DPadInfo;
    bool padState;
public:
    GamepadMapper();
    void updateAllKey();

    bool getPadState() { return padState; }
    bool getButtonState(GamepadButton gb);

    int getDPad() { return DPadInfo; }

    int getXPos() { return XPos; }
    int getYPos() { return YPos; }
    int getZPos() { return ZPos; }
};


#endif // GAMEPADMAPPER_H
