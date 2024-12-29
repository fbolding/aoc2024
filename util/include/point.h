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

    Point operator * (const long long& scalar) const {
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

    bool isNeighbour(const Point& point, bool includeDiagonal = false) const{
        if (!includeDiagonal){
            return (point==north() || point==east() || point==south() || point==west());
        } else {
            return (isNeighbour(point, false) || point==northeast() || point==southeast() || point==southwest() || point==northwest());
        }
    }

    Point north() const { return Point(x,y-1);}
    Point east() const { return Point(x+1,y);}
    Point south() const { return Point(x,y+1);}
    Point west() const { return Point(x-1,y);}
    // Not the fastest, but is robust to direction definition changes
    Point northeast() const { return north().east();}
    Point southeast() const { return south().east();}
    Point southwest() const { return south().west();}
    Point northwest() const { return north().west();}

    std::vector<Point> neighbours(bool includeDiagonal = false) const {
        std::vector<Point> list;
        list.push_back(north());
        if (includeDiagonal){ list.push_back(northeast());}
        list.push_back(east());
        if (includeDiagonal){ list.push_back(southeast());}
        list.push_back(south());
        if (includeDiagonal){ list.push_back(southwest());}
        list.push_back(west());
        if (includeDiagonal){ list.push_back(northwest());}
        return list;
    }

    long long x;
    long long y;
};
inline std::ostream& operator<<(std::ostream& os, const Point& p){
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}
};
#endif