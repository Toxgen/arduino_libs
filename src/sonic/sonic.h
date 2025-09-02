#ifndef SONIC_H
#define SONIC_H

#include "Arduino.h"
#include "../screen.h"

class sonic
{
    struct both
    {
        bool a;
        screen b;

        both(bool foo, const screen& bar) : a(foo), b(bar) {} 
    };

    public:
        sonic(int echo, int trig, const screen& lcd);
        void run(bool flag, int* distance = nullptr);

    private:
        long _duration;
        int _distance;
        int _prev;
        int _trig;
        int _echo;
        both _lcd;
};

#endif