#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "gamepadmapper.h"
#include "gamepadmapperex.h"
#include "mousecontroller.h"
#include "keyboardcontroller.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent*);

private:
    GamepadMapperEX Gamepad;
    MouseController Mouse;
    KeyboardController Keyboard;

    QTimer *timer, *drawTimer;

    bool isOn;
    int width, height;
    bool pressed_ctrl, pressed_shift, pressed_alt;
    int state, keyDirection;

    int mouseStep();
    int keyboardStep();

    int xyToDirection(int x, int y);
    int xyToDistance(int x, int y);

public slots:
    void onTimeOut();
};
#endif // WIDGET_H
