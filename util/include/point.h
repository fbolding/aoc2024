#ifndef POINT_H
#define POINT_H
#include <cstddef>
namespace aoc{
struct Point{
public:
    Point(size_t x, size_t y): x(x), y(y) {};

    bool operator < (const Point& rhs) const {
        if (x == rhs.x){ 
            return y<rhs.y;
        } else { 
            return x<rhs.x;
        }
    }

    Point operator + (const Point& rhs) const {
        return Point(x+rhs.x, y+rhs.y);
    }

    Point operator - (const Point& rhs) const {
        return Point(x-rhs.x, y-rhs.y);
    }

    Point operator * (const size_t& scalar) const {
        return Point(scalar*x, scalar*y);
    }

    size_t x;
    size_t y;
};

};
#endif