#ifndef SONIC_H
#define SONIC_H

#include "Arduino.h"
#include "../screen.h"

class Sonic
{
    public:
        Sonic(int echo_p, int trig_p, const screen& lcd) : _echo(echo_p), _trig(trig_p), _lcd(lcd) {};
        void run(bool flag);

    private:
        long _duration;
        int _distance;
        int _prev;
        int _trig;
        int _echo;
        both _lcd;
};

#endif