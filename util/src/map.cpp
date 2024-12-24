#include "map.h"

#include <iostream>

namespace aoc{
void Map::printMap() const{
    std::cout << (*this);
}

std::vector<Point> Map::getPoints() const{
    std::vector<Point> pointVector;
    for (size_t y=0; y<height; y++){
        for (size_t x=0; x<width; x++){
            pointVector.push_back(Point(x,y));
        }
    }
    return pointVector;
}

std::ostream& operator<<(std::ostream& os, const aoc::Map& map){
    for (const auto& row: map.arr){
        for (const char& element: row){
            os << element;
        }
        os << "\n";
    }
    return os;
}
}