#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <QString>

constexpr int STEP_TIMER = 10;
constexpr int DRAW_TIMER = 100;

const QString RIGHT_KEY_NAME[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "-", "*", "/", "."};
const int RIGHT_KEY_CODE[] =     {48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  107, 109, 106, 111, 110};

const QString DOWN_KEY_NAME[] = {"  Space", "  Enter", "   Tab", "BackSpace"};
const int DOWN_KEY_CODE[] =     {32,      13,      9,     8};

const QString UP_KEY_NAME[] = {",<", ".>", "/?", ";:", "\'\"", "[{", "]}", "\\|"};
const int UP_KEY_CODE[] =     {188,  190,  191,  186,  222,    219,  221,  220};

#endif // GLOBALCONFIG_H
