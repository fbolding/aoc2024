#include "map.h"

#include <iostream>

namespace aoc{
void Map::printMap() const{
    std::cout << (*this);
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