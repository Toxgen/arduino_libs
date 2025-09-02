#include "Arduino.h"

#include "sonic.h"
#include "../screen.h"

sonic::sonic(int echo, int trig, const screen& lcd = screen(0, 0, 0, 0, 0, 0)) : _echo(echo), _trig(trig), _lcd{false, lcd} 
{
    pinMode(_echo, INPUT);
    pinMode(_trig, OUTPUT);
}

void sonic::run(bool flag, int* distance = nullptr)
{
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);

    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);

    _duration = pulseIn(_echo, HIGH);
    _distance = _duration * 0.034 / 2;

    if (_distance > 790) // to check if the sensor lowkey buggin
    {
        _distance = _prev;
        Serial.println("buggin");
    }
    else
    {
        _prev = _distance;
    }

    if (flag && !_lcd.a) // checks if flag is true and if there's a screen
    {
        delay(150);
        _lcd.b.print_out_int(_distance);
        Serial.println(_distance);
    }

    if (distance != nullptr) // checks if a ptr was used
    {
        distance = _distance;
    }
}