#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "mapTraversal.hpp"

int main(){
    mapTraversal map;
    map.readFile("input.txt");
    map.findStart();
    map.traverseMap();
    std::cout << "Part 1: " << map.getPathLength() << std::endl;
    map.tryObstacles();
    std::cout << "Part 2: " << map.getLoopOptions() << std::endl;
    return 0;
}
