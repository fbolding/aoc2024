#ifndef ANTENNA_H
#define ANTENNA_H

#include "point.h"

struct Point{
    size_t x;
    size_t y;
};

class Antenna{
    public:

        Point coordinate;
};

#endif