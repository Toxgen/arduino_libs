#include "screen.h"
#include "Arduino.h"
#include <LiquidCrystal.h>

// externs than defines it, no #define
int MS = 1000;
#define byte uint8_t

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

// screen is 2 by 16
// each pixel is 5 by 8
// do 10 fps animation
// each fram is 100 ms, take account for how long to display
/*
[1] [2] [3] [4] [5] [6] [7] [hand left 8] [face 9] [hand right 10] 
[1] [2] [3] [4] [5] [6] [7] [8] [lower body 9]
*/
byte feet[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000};

byte head_0_to_2_and_7[8] = {
  0b11111,
  0b10001,
  0b11011,
  0b10001,
  0b11111,
  0b00100,
  0b11111,
  0b00000};

byte head_3_to_4[8] = {
  0b11111,
  0b10001,
  0b10101,
  0b10001,
  0b11111,
  0b00100,
  0b01110,
  0b10101};

byte head_5[8] = {
  0b11111,
  0b10001,
  0b10101,
  0b10001,
  0b11111,
  0b00100,
  0b01110,
  0b10111};

byte head_6[8] = {
  0b11111,
  0b10001,
  0b10101,
  0b10001,
  0b11111,
  0b00100,
  0b01110,
  0b10111};

// [0] both, [1] right
btye hand_start[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b11100,
  0b00000};

// [1] left, [2] right, **[6] left**
byte hand_next0[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b10101,
  0b01110,
  0b00111,
  0b00000};

// [2] left, [3] right
byte hand_next1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00101,
  0b11110,
  0b00011};

// [3] left
byte hand_next2_left[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b00011};

// [4] left
byte hand_next3_left[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00101,
  0b11110,
  0b00111};

// [4] right
byte hand_next3_right[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b10000};

// [5] left
byte hand_next4_left[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10101,
  0b01111,
  0b00001};

// [5] right
byte hand_next4_right[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01111,
  0b11100};

// [6] right
byte hand_next5_right[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10101,
  0b01110,
  0b11000};

// [7] left
byte hand_next6_left[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b10101,
  0b01110,
  0b00100,
  0b00111,
  0b00000};

// [7] right
byte hand_next6_right[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10101,
  0b01110,
  0b11000,
  0b00000};


void Screen::print_out_six_seven(uint8_t frame) 
{
  lcd.createChar(0, feet);

  lcd.createChar(1, head_0_to_2_and_7);
  lcd.createChar(2, head_3_to_4);
  lcd.createChar(3, head_5);
  lcd.createChar(4, head_6);

  lcd.createChar(5, hand_start);
  lcd.createChar(6, hand_next0);
  lcd.createChar(7, hand_next1);
  lcd.createChar(8, hand_next2_left);
  lcd.createChar(9, hand_next3_left);
  lcd.createChar(10, hand_next3_right);
  lcd.createChar(11, hand_next4_left);
  lcd.createChar(12, hand_next4_right);
  lcd.createChar(13, hand_next5_right);
  lcd.createChar(14, hand_next6_left);
  lcd.createChar(15, hand_next6_right);

  // (0, 0) is top left, (0 column, 0 row)
  switch (frame) {
    case 0:
      lcd.setCursor(7, 0);
      lcd.write(byte(5)); // both hands
      lcd.setCursor(8, 0);
      lcd.write(byte(1)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(5)); // both hands
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 1:
      lcd.setCursor(7, 0);
      lcd.write(byte(6)); // left hand
      lcd.setCursor(8, 0);
      lcd.write(byte(2)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(7)); // right hand
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 2:
      lcd.setCursor(7, 0);
      lcd.write(byte(6)); // left hand
      lcd.setCursor(8, 0);
      lcd.write(byte(3)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(8)); // right hand
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 3:
      lcd.setCursor(7, 0);
      lcd.write(byte(9)); // left hand
      lcd.setCursor(8, 0);
      lcd.write(byte(4)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(10)); // right hand
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 4:
      lcd.setCursor(7, 0);
      lcd.write(byte(11)); // left hand
      lcd.setCursor(8, 0);
      lcd.write(byte(5)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(12)); // right hand
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 5:
      lcd.setCursor(7, 0);
      lcd.write(byte(14)); // left hand
      lcd.setCursor(8, 0);
      lcd.write(byte(4)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(13)); // right hand
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 6:
      lcd.setCursor(7, 0);
      lcd.write(byte(15)); // left hand
      lcd.setCursor(8, 0);
      lcd.write(byte(2)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(13)); // right hand
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
    case 7:
      lcd.setCursor(7, 0);
      lcd.write(byte(5)); // both hands
      lcd.setCursor(8, 0);
      lcd.write(byte(1)); // face
      lcd.setCursor(9, 0);
      lcd.write(byte(5)); // both hands
      lcd.setCursor(8, 1);
      lcd.write(byte(0)); // feet
      break;
      
  }
} 

