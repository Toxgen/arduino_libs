#ifndef SCREEN_H
#define SCREEN_H

#include <LiquidCrystal.h>
#include "Arduino.h"

class screen
{
    public:
        screen(int rs, int enable, int d4, int d5, int d6, int d7) : _lcd(rs, enable, d4, d5, d6, d7) 
        {  _lcd.begin(16, 2); }
        
        void print_out(char* input);
        void print_out_int(int input);
    private:
        // variables are constructed than costructor defines them
        LiquidCrystal _lcd;
        char _buffer[16];
};

extern int MS;

#endif