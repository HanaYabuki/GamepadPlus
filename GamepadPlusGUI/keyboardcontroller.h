#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

enum class KeyCode {
    shift = 16,
    ctrl = 17,
    alt = 18,
};

class KeyboardController
{

private:

public:
    KeyboardController();
    void keyboardPress(char keycode);
    void keyboardPress(KeyCode keycode, bool press);

    bool getKeyState(char keycode);
    bool getKeyState(KeyCode keycode);
};

#endif // KEYBOARDCONTROLLER_H
