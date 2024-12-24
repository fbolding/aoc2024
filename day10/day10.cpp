#include <iostream>
#include <set>
#include "input.h"
#include "functions.h"

using namespace aoc;

bool isConnected(const Map& map, const Point& start, const Point& goal, char previous_level = '0'-1);
long isConnectedUnique(const Map& map, const Point& start, const Point& goal, char previous_level = '0'-1, std::set<Point> path = std::set<Point>());
int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    Map input = readAsMap();

    // Part 1
    std::vector<Point> trailheads;
    std::vector<Point> peaks;
    for(const auto& p: input.getPoints()){
        if (input[p] == '0'){ trailheads.push_back(p); }
        else if (input[p] == '9'){ peaks.push_back(p); }
    }
    long part1 = 0;
    for (const auto& trailhead: trailheads){
        for (const auto& peak: peaks){
            part1 += isConnected(input, trailhead, peak);
        }
    }
    printSolution(part1, false);

    // Part 2
    long part2 = 0;
    for (const auto& trailhead: trailheads){
        for (const auto& peak: peaks){
            part2 += isConnectedUnique(input, trailhead, peak);
        }
    }
    printSolution(part2, true);
    return 0;
}

bool isConnected(const Map &map, const Point &start, const Point &goal, char previous_level){
    if (!map.isInside(start)){ return false;}
    if (map[start]!=previous_level+1){ return false;}
    if (start==goal) {return true;}
    
    previous_level = map[start];
    Point up(0,1);
    Point down(0,-1);
    Point left(-1,0);
    Point right(1,0);

    return isConnected(map, up+=start, goal, previous_level) || isConnected(map, down+=start, goal, previous_level) ||
        isConnected(map, left+=start, goal, previous_level) || isConnected(map, right+=start, goal, previous_level);
}

long isConnectedUnique(const Map &map, const Point &start, const Point &goal, char previous_level, std::set<Point> path){
    if (!map.isInside(start)){ return 0;}
    if (map[start]!=previous_level+1){ return 0;}
    if (!path.insert(start).second){ return 0;}
    if (start==goal) {return 1;}
    
    previous_level = map[start];
    Point up(0,1);
    Point down(0,-1);
    Point left(-1,0);
    Point right(1,0);

    return isConnectedUnique(map, up+=start, goal, previous_level, path) + isConnectedUnique(map, down+=start, goal, previous_level, path) +
        isConnectedUnique(map, left+=start, goal, previous_level, path) + isConnectedUnique(map, right+=start, goal, previous_level, path);
}
