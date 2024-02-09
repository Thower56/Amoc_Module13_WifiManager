#pragma once

#include <Arduino.h>

class Joystick{
public:
    Joystick(int p_pinX, int p_pinY);
    int getAxisX();
    int getAxisY();

private:
    int m_AxisX;
    int m_AxisY;
};

