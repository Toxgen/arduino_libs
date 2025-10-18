#ifndef SCREEN_H
#define SCREEN_H

#include <LiquidCrystal.h>
#include "Arduino.h"

class Screen
{
    public:
        // constructor for Screen & constructions _lcd for initalization for _lcd /n
        // VSS is GND, VCC is 5V, RW is GND, VO is 1k resisetor to GND, A is 1k resistor to 5V, K is GND
        Screen(int rs, int enable, int d4, int d5, int d6, int d7) : _lcd(rs, enable, d4, d5, d6, d7) 
        {  _lcd.begin(16, 2); }

        struct six_seven {
            uint8_t column
            uint8_t row
        }
        
        void print_out(char* input);
        void print_out_int(int input);
        
    private:
        LiquidCrystal _lcd;
        char _buffer[16];
};

extern int MS;

#endif