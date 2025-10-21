#include "screen.h"
#include "Arduino.h"
#include <LiquidCrystal.h>

// externs than defines it, no #define
int MS = 1000;

void Screen::print_out(char* input)
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

  // prints to 2nd row if input is bigger than 32
  if (str_length > 16)
  {
    // already has null terminator
    strncpy(_buffer, input + 16, str_length);
    _buffer[16] = "\0";

    _lcd.setCursor(0, 1);
    _lcd.print(_buffer);
  }
}

void Screen::print_out_int(int input)
{
  char buffer[32];
  sprintf(buffer, "%d", input);
  Screen::print_out(buffer);
}

void Screen::create_char(uint8_t a, uint8_t b[])
{
  _lcd.createChar(a, b);
}

void Screen::print_out_six_seven(uint8_t frame) 
{
  // (0, 0) is top left, (0 column, 0 row)
  _lcd.clear();
  // display the feet first
  _lcd.setCursor(8, 1);
  _lcd.write(byte(0));
  // figure out where to where and comment it on the arduino
  // don't forget to pull from the cloud

  switch (frame % 8) {
    case 0:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(5)); 
      _lcd.setCursor(9, 0);
      _lcd.write(byte(5)); // both hands

      _lcd.setCursor(8, 0);
      _lcd.write(byte(1)); // face
      break;
    case 1:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(6)); // left hand
      _lcd.setCursor(9, 0);
      _lcd.write(byte(7)); // right hand

      _lcd.setCursor(8, 0);
      _lcd.write(byte(1)); // face
      break;
    case 2:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(6)); // left hand
      _lcd.setCursor(8, 0);
      _lcd.write(byte(3)); // face
      _lcd.setCursor(9, 0);
      _lcd.write(byte(8)); // right hand
      break;
    case 3:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(9)); // left hand
      _lcd.setCursor(8, 0);
      _lcd.write(byte(4)); // face
      _lcd.setCursor(9, 0);
      _lcd.write(byte(10)); // right hand
      break;
    case 4:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(11)); // left hand
      _lcd.setCursor(8, 0);
      _lcd.write(byte(5)); // face
      _lcd.setCursor(9, 0);
      _lcd.write(byte(12)); // right hand
      break;
    case 5:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(14)); // left hand
      _lcd.setCursor(8, 0);
      _lcd.write(byte(4)); // face
      _lcd.setCursor(9, 0);
      _lcd.write(byte(13)); // right hand
      break;
    case 6:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(15)); // left hand
      _lcd.setCursor(8, 0);
      _lcd.write(byte(2)); // face
      _lcd.setCursor(9, 0);
      _lcd.write(byte(13)); // right hand
      break;
    case 7:
      _lcd.setCursor(7, 0);
      _lcd.write(byte(5)); // both hands
      _lcd.setCursor(8, 0);
      _lcd.write(byte(1)); // face
      _lcd.setCursor(9, 0);
      _lcd.write(byte(5)); // both hands
      break;

  }
} 

// screen is 2 by 16
// each pixel is 5 by 8
// do 10 fps animation
// each fram is 100 ms, take account for how long to display
/*
[1] [2] [3] [4] [5] [6] [7] [hand left 8(7*)] [face 9(8*)] [hand right 10(9*)] 
[1] [2] [3] [4] [5] [6] [7] [8] [lower body 9(8*)]
*/