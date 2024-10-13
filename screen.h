#ifndef SCREEN_H
#define SCREEN_H

#include <LiquidCrystal.h>
#include "Arduino.h"

class first
{
    public:
        first(int, int, int, int, int, int);
        void print_out(char*);
        void print_out_int(int);
    private:
        // variables are constructed than costructor defines them
        LiquidCrystal _lcd;
        char _buffer[16];
        
};

extern int MS;

#endif