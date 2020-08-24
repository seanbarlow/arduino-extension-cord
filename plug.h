#ifndef MY_PLUG_H
#define MY_PLUG_H
#include <Arduino.h>
class Plug
{

private:
    byte plug;

public:
    Plug(byte pin);
    void init();
    void on();
    void off();
    bool status();
};
#endif