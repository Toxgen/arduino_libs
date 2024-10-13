#ifndef SONIC
#define SONIC

#include "Arduino.h"

class sonic
{
    public:
        void sonic(int, int);
        void run(bool);
    private:
        long duration;
        int distance;
};

#endif