#pragma once

class KeySignal
{
  private:
    unsigned char key;
    double acceleration;
    bool count;
    bool isPressing;
    bool isPressed;
    double signal;

  public:
    KeySignal(unsigned char key, double acceleration);
    unsigned char getKey() const;
    double getIsPressed() const;
    double getSignal() const;
    void setState(bool state);
    void updateState();
};
