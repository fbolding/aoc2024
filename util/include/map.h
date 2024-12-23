#ifndef MAP_H
#define MAP_H
#include <cstddef>
#include <iostream>
#include <vector>
#include "point.h"
namespace aoc{
class Map{
public:
    Map(const std::vector<std::vector<char>>& input): arr(input){
        height = input.size();
        width = input[0].size();
    }
    char at(const Point& point) const { return arr[point.y][point.x];}
    char operator [](const Point& point) const { return arr[point.y][point.x];}
    char& operator [](const Point& point) { return arr[point.y][point.x];}
    friend std::ostream& operator<<(std::ostream& os, const Map& arr);

    void printMap() const;
    bool isInside(const Point& point) const { return (point.x<width && point.y<height);}
    size_t getHeight() const { return height;}
    size_t getWidth() const { return width;}

    
private:
    std::vector<std::vector<char>> arr;
    size_t height;
    size_t width;
};

};
#endif