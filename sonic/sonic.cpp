#include "sonic.h"

#include "Arduino.h"

sonic::sonic(int echo, int trig)
{
    pinMode(echo, HIGH);
    pinMode(trig, LOW);

    duration = 0;
    distance = 0;
}

sonic::run(bool debug)
{
    digitalWrite(trig, LOW);
    delay(2);

    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;

    if (debug)
    {
        delay(100);
        lcd.print_out_int(distance);
        Serial.println(distance);
    }
}