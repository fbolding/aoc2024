#include <iostream>
#include "input.h"
#include "functions.h"
#include <set>

using namespace aoc;
std::pair<std::vector<Point>, size_t> walkRegion(const Map& input, const Point& start, std::set<Point>& visited);
void walkHelper(const Map& input, const Point& current, std::set<Point>& visited, std::vector<Point>& region, size_t& perimeter, const char& type);
int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    Map input = readAsMap();

    // Part 1
    std::set<Point> visited;
    std::vector<std::vector<Point>> regions;
    size_t totalPrice = 0;
    for (const auto& p: input.getPoints()){
        if (!visited.insert(p).second){ continue;}
        auto regionInfo = walkRegion(input, p, visited);
        regions.push_back(regionInfo.first);
        totalPrice += regionInfo.second * regionInfo.first.size();
    }
    printSolution(totalPrice, false);

    // Part 2
    printSolution(0, true);
    return 0;
}

std::pair<std::vector<Point>, size_t> walkRegion(const Map &input, const Point &start, std::set<Point> &visited){
    std::vector<Point> region;
    size_t perimeter = 0;
    region.push_back(start);
    char type = input[start];
    walkHelper(input, start.north(), visited, region, perimeter, type);
    walkHelper(input, start.east(), visited, region, perimeter, type);
    walkHelper(input, start.south(), visited, region, perimeter, type);
    walkHelper(input, start.west(), visited, region, perimeter, type);
    return std::make_pair(region, perimeter);
}

void walkHelper(const Map &input, const Point &current, std::set<Point> &visited, std::vector<Point> &region, size_t& perimeter, const char& type){
    if (!input.isInside(current)){ 
        perimeter++; // Outside map means perimeter
        return;
    }
    if (input[current]!=type){
        perimeter++; // Other region type means perimeter
        return; 
    }
    if (!visited.insert(current).second){ 
        return; // Already visited and same type means already processed
    }
    region.push_back(current);
    walkHelper(input, current.north(), visited, region, perimeter, type);
    walkHelper(input, current.east(), visited, region, perimeter, type);
    walkHelper(input, current.south(), visited, region, perimeter, type);
    walkHelper(input, current.west(), visited, region, perimeter, type);
}
