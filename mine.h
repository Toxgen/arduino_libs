#ifndef MINE_H
#define MINE_H

#include <LiquidCrystal.h>
#include "Arduino.h"

class first
{
    public:
        first(void);
        void print_out(char*);
    private:
        // variables are constructed than costructor defines them
        LiquidCrystal _lcd;
        char _buffer[16];
};

extern int MS;

#endif