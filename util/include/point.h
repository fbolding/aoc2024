#ifndef POINT_H
#define POINT_H
#include <cstddef>
namespace aoc{
struct Point{
public:
    Point(){};
    Point(size_t x, size_t y): x(x), y(y) {};

    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    bool operator == (const Point& rhs) const {
        return x==rhs.x && y==rhs.y;
    }

    bool operator != (const Point& rhs) const {
        return !operator==(rhs);
    }

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

    Point& operator += (const Point& rhs) {
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }

    Point& operator -= (const Point& rhs) {
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }

    Point north() const { return Point(x,y-1);}
    Point east() const { return Point(x+1,y);}
    Point south() const { return Point(x,y+1);}
    Point west() const { return Point(x-1,y);}
    size_t x;
    size_t y;
};
inline std::ostream& operator<<(std::ostream& os, const Point& p){
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}
};
#endif