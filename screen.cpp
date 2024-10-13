#include "screen.h"
#include "Arduino.h"
#include <LiquidCrystal.h>

// externs than defines it, no #define
int MS = 1000;

// constructor class because it doesnt have default constructor
first::first(int rs, int rw, int enable, int d7, int d6, int d5, int d4)
{
  // 16 columns, 2 rows
  _lcd(rs, rw, enable, d7, d6, d5, d4);
  _lcd.begin(16, 2);
}

void first::print_out(char* input)
{
  /*
  clear board then print string
  */
  int str_length = strlen(input);

  _lcd.clear();
  _lcd.setCursor(0, 0);

  // safe guard if string is over 32 chars
  if (str_length > 32)
  {
    _lcd.print("uh oh");
    return;
  }

  _lcd.print(input);

  // prints to 2nd row if input is bigger than > 32
  if (str_length > 16)
  {
    // already has null terminator
    strncpy(_buffer, input + 16, str_length);
    // double check
    _buffer[16] = '\0';

    _lcd.setCursor(0, 1);
    _lcd.print(_buffer);
  }
}

void first::print_out_int(int input)
{
  char buffer[32];
  snprintf(buffer, "%d", input);
  first::print_out(buffer);
}