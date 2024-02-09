#include <Joystick.h>


Joystick::Joystick(int p_pinX, int p_pinY) {
    m_AxisX = p_pinX;
    m_AxisY = p_pinY;
    // pinMode(m_AxisX, INPUT);
    // pinMode(m_AxisY, INPUT);
}

int Joystick::getAxisX() {
    int posX =  analogRead(m_AxisX);
    Serial.print("x: "); Serial.println(posX);
    int result = map(posX, 0, 4095, -100, 100);
    return result;
}

int Joystick::getAxisY() {
    int posY = analogRead(m_AxisY);
    Serial.print("y: "); Serial.println(posY);
    int result = map(posY, 0, 4095, -100, 100);
    return result;
}
