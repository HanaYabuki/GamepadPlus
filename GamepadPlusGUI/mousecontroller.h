#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

class MouseController
{

private:
    int CursorPos_x, CursorPos_y;
    int Window_x, Window_y;
    bool MbLeft, MbRight, MbMiddle;

public:
    MouseController();
    void systemMouseSet();
    void mouseGoto(int aim_x, int aim_y);
    void mouseMove(int aim_x, int aim_y, int speed);
    void mouseClick(bool mb_left = false, bool mb_right = false, bool mb_middle = false, int mb_middleUpDown = 0);
    int mouseGetX() { return CursorPos_x; }
    int mouseGetY() { return CursorPos_y; }
    int windowGetWidth() { return Window_x; }
    int windowGetHeight() { return Window_y; }

};


#endif // MOUSECONTROLLER_H
