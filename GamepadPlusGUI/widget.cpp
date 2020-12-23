#include "widget.h"

#include "globalconfig.h"
#include <QPainter>
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent), Gamepad()
{
    // Var Init
    isOn = true;
    width = Mouse.windowGetWidth();
    height = Mouse.windowGetHeight();
    state = 0;

    pressed_alt = pressed_ctrl = pressed_shift = false;

    // Settings
    resize(width, height);
    setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Timer Settings
    timer = new QTimer();
    timer->setInterval(STEP_TIMER);
    timer->setTimerType(Qt::TimerType::CoarseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start();

    drawTimer = new QTimer();
    drawTimer->setInterval(DRAW_TIMER);
    drawTimer->setTimerType(Qt::TimerType::VeryCoarseTimer);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(update()));
    drawTimer->start();
}

Widget::~Widget()
{
    delete timer;
}


void Widget::onTimeOut()
{
    static int closeTimer = 0;
    if(Gamepad.getButtonState(GamepadButtonEX::Start)) {
        if(isOn) {
            if(closeTimer > 120) {
                isOn = false;
                closeTimer = -2147183648;
            }
        }else {
            if(closeTimer==0) {
                isOn = true;
            }
        }
        closeTimer++;
    }else {
        closeTimer = 0;
    }

    Gamepad.updateAllKey();
    if(Gamepad.getPadState() && isOn) {
        mouseStep();
        keyboardStep();
    }
}

void Widget::paintEvent(QPaintEvent *qPaintEvent)
{
    QPainter painter(this);
    QPen penOn(QColor(0, 35, 255)), penOff(QColor(255, 16, 16));
    penOn.setWidth(3); penOff.setWidth(3);
    QBrush brushOn(QColor(255,255,255)), brushOff(QColor(200,200,200));

    int xpos = Mouse.mouseGetX(), ypos = Mouse.mouseGetY();
    if(isOn) {
        painter.setPen(penOn);
        painter.setBrush(brushOn);
    }else {
        painter.setPen(penOff);
        painter.setBrush(brushOff);
    }

    /*
     *  Draw Status
     */
    if(xpos > width / 2) {
        painter.drawRect(32, 32, 128, 32);
        painter.drawText(32, 32 + 23, " GamepadPlus-on");
    }else {
        painter.drawRect(width-128-32, 32, 128, 32);
        painter.drawText(width-128-32, 32 + 23, " GamepadPlus-on");
    }

    /*
     *  Draw HotKey
     */
    if(pressed_ctrl) {
        if(xpos > width / 2) {
            painter.drawRect(32, 96, 64, 32);
            painter.drawText(32, 96 + 24, "  Ctrl");
        }else {
            painter.drawRect(width-64-32, 96, 64, 32);
            painter.drawText(width-64-32, 96 + 24, "  Ctrl");
        }
    }
    if(pressed_shift) {
        if(xpos > width / 2) {
            painter.drawRect(32, 96+64, 64, 32);
            painter.drawText(32, 96+64 + 24, "  Shift");
        }else {
            painter.drawRect(width-64-32, 96+64, 64, 32);
            painter.drawText(width-64-32, 96+64 + 24, "  Shift");
        }
    }
    if(pressed_alt) {
        if(xpos > width / 2) {
            painter.drawRect(32, 96+128, 64, 32);
            painter.drawText(32, 96+128 + 24, "   Alt");
        }else {
            painter.drawRect(width-64-32, 96+128, 64, 32);
            painter.drawText(width-64-32, 96+128 + 24, "   Alt");
        }
    }

    /*
     *  Draw Normal Key
     */
    switch (state) {
    case 4: {
        painter.drawRect(32, height-128, 26 * 32, 32);
        painter.drawRect(32-3 + (keyDirection/40 % 26)*32, height-128 -3, 32+6, 32+6);
        for(int i=0; i<26; ++i) {
            painter.drawText(32 + 32*i + 10, height-128+ 24, (QString)(i+'A'));
        }
        break;
    }
    case 6: {
        painter.drawRect(32, height-128, 15 * 32, 32);
        painter.drawRect(32-3 + (keyDirection/40 % 15)*32, height-128-3, 32+6, 32+6);
        for(int i=0; i<15; ++i) {
            painter.drawText(32 + 32*i + 10, height-128+24, RIGHT_KEY_NAME[i]);
        }
        break;
    }
    case 2: {
        painter.drawRect(32, height-128, 4 * 64, 32);
        painter.drawRect(32-3 + (keyDirection/80 % 4)*64, height-128-3, 64+6, 32+6);
        for(int i=0; i<4; ++i) {
            painter.drawText(32 + 64*i + 5, height-128+24, DOWN_KEY_NAME[i]);
        }
        break;
    }
    case 8: {
        painter.drawRect(32, height-128, 8 * 32, 32);
        painter.drawRect(32-3 + (keyDirection/60 % 8)*32, height-128-3, 32+6, 32+6);
        for(int i=0; i<8; ++i) {
            painter.drawText(32 + 32*i + 8, height-128+24, UP_KEY_NAME[i]);
        }
        break;
    }
    }
}

int Widget::mouseStep()
{
    static int speed = 1;
    Mouse.systemMouseSet();
    Mouse.mouseClick(
        Gamepad.getButtonState(GamepadButtonEX::A),
        Gamepad.getButtonState(GamepadButtonEX::B),
        Gamepad.getButtonState(GamepadButtonEX::X),
        (Gamepad.getZPos() - 32767) >> 11
    );
    Mouse.mouseMove(
        (Gamepad.getXPos()-32767) >> 13,
        (Gamepad.getYPos()-32767) >> 13,
        2 + (Gamepad.getButtonState(GamepadButtonEX::LB) ? -1 : 0) + (Gamepad.getButtonState(GamepadButtonEX::RB) ? 3 : 0)
    );
    return 0;
}

int Widget::keyboardStep()
{
    /*
     *  HotKey
     */
    static bool tmp_ctrl, tmp_alt = false, tmp_shift = false;
    if(Gamepad.getButtonState(GamepadButtonEX::L) == true) {
        if(tmp_ctrl==false) {
            pressed_ctrl = !pressed_ctrl;
            Keyboard.keyboardPress(KeyCode::ctrl, pressed_ctrl);
        }
    }
    if(Gamepad.getButtonState(GamepadButtonEX::R) == true) {
        if(tmp_shift==false) {
            pressed_shift = !pressed_shift;
            Keyboard.keyboardPress(KeyCode::shift, pressed_shift);
        }
    }
    if(Gamepad.getButtonState(GamepadButtonEX::Back) == true) {
        if(tmp_alt==false) {
            pressed_alt = !pressed_alt;
            Keyboard.keyboardPress(KeyCode::alt, pressed_alt);
        }
    }
    tmp_ctrl = Gamepad.getButtonState(GamepadButtonEX::L);
    tmp_shift = Gamepad.getButtonState(GamepadButtonEX::R);
    tmp_alt = Gamepad.getButtonState(GamepadButtonEX::Back);


    /*
     *  Normal Key
     */
    static int last_direction = -65536;

    int gx = Gamepad.getXRotate()-32767, gy = Gamepad.getYRotate()-32767;
    int delta_direction = 0;

    if (xyToDistance(gx, gy) > 16384) {
        delta_direction = last_direction==-65536 ? 0 : (xyToDirection(gx,gy) - last_direction);
        if (delta_direction < -180) delta_direction += 360;
        if (delta_direction > +180) delta_direction -= 360;
        last_direction = xyToDirection(gx, gy);
    } else {
        last_direction = -65536;
    }

    // Left => normal letter key
    if(Gamepad.getDPad(GamepadDpadEX::left)) {
        if(state == 0) {
            state = 4;
            keyDirection = 0;
        } else if(state==4){
            keyDirection = (keyDirection + delta_direction + 1040) % 1040;
        }
    }
    // Right => number key
    if(Gamepad.getDPad(GamepadDpadEX::right)) {
        if(state == 0) {
            state = 6;
            keyDirection = 0;
        } else if(state==6){
            keyDirection = (keyDirection + delta_direction + 40 * 15) % 600;
        }
    }
    // Down => function key
    if(Gamepad.getDPad(GamepadDpadEX::down)) {
        if(state == 0) {
            state = 2;
            keyDirection = 0;
        } else if(state==2){
            keyDirection = (keyDirection + delta_direction + 80 * 4) % 320;
        }
    }
    // UP => Punctuation
    if(Gamepad.getDPad(GamepadDpadEX::up)) {
        if(state == 0) {
            state = 8;
            keyDirection = 0;
        } else if(state==8){
            keyDirection = (keyDirection + delta_direction + 60 * 8) % 480;
        }
    }

    // Reset
    if(state != 0) {
        switch (state) {
        case 4:{
            if(!Gamepad.getDPad(GamepadDpadEX::left)) {
                Keyboard.keyboardPress(keyDirection/40 % 26 + 'A');
                state = 0;
            }
            break;
        }
        case 2:{
            if(!Gamepad.getDPad(GamepadDpadEX::down)) {
                Keyboard.keyboardPress(DOWN_KEY_CODE[keyDirection/80 % 4]);
                state = 0;
            }
            break;
        }
        case 6:{
            if(!Gamepad.getDPad(GamepadDpadEX::right)) {
                Keyboard.keyboardPress(RIGHT_KEY_CODE[keyDirection/40 % 15]);
                state = 0;
            }
            break;
        }
        case 8:{
            if(!Gamepad.getDPad(GamepadDpadEX::up)) {
                Keyboard.keyboardPress(UP_KEY_CODE[keyDirection/60 % 8]);
                state = 0;
            }
            break;
        }
        }
    }

    return 0;
}

int Widget::xyToDirection(int x, int y)
{
    double rad = atan2(y, x);
    return ((int)(rad * 180 / 3.141592653589793) + 360) % 360;
}

int Widget::xyToDistance(int x, int y)
{
    return sqrt( x*x+y*y );
}
