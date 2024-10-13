#ifndef MINE_H
#define MINE_H

#include <LiquidCrystal.h>
#include "Arduino.h"

class first
{
    public:
        first(void);
        void print_out(char*);
        void print_out_int(int)
    private:
        // variables are constructed than costructor defines them
        LiquidCrystal _lcd;
        char _buffer[16];
        int rs;
        int rw;
        int enable;
        int d7;
        int d6;
        int d5;
        int d4;
        
};

extern int MS;

#endif