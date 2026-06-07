#include "Classes/KeySignal.hpp"

KeySignal::KeySignal(unsigned char key, double acceleration)
{
    this->key = key;
    this->acceleration = acceleration;
}

unsigned char KeySignal::getKey() const
{
    return key;
}

double KeySignal::getIsPressed() const
{
    return isPressed;
}

double KeySignal::getSignal() const
{
    return signal;
}

void KeySignal::setState(bool state)
{
    isPressing = state;
}

void KeySignal::updateState()
{
    isPressed = isPressing && count == 0;
    count = isPressing ? count + 1 : 0;

    if (isPressing && signal == 1.0 || !isPressing && signal == 0.0)
        return;

    signal += isPressing ? acceleration : -acceleration;

    if (signal < 0.0)
        signal = 0.0;

    if (signal > 1.0)
        signal = 1.0;
}
