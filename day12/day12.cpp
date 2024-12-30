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
    // Tip from the subreddit: count corners instead of sides, they are actually equal
    size_t price = 0;
    size_t area;
    size_t sides;
    char type;
    for (const auto& region: regions){
        area = region.size();
        sides = 0;
        type = input[region[0]];
        for (const auto& point: region){
            bool north; bool east; bool south; bool west; // Bools store which points are different
            north = (!input.isInside(point.north()) || type!=input[point.north()]);
            east = (!input.isInside(point.east()) || type!=input[point.east()]);
            south = (!input.isInside(point.south()) || type!=input[point.south()]);
            west = (!input.isInside(point.west()) || type!=input[point.west()]);
            if (north+east+south+west == 4){ sides=4;} // Single element region
            else if (north+east+south+west == 3){ sides+=2;} // Two corners at one region
            else if (north&&east || east&&south || south&&west || west&&north) { sides++;}

            // Check inside corners
            bool northeast; bool southeast; bool southwest; bool northwest; // Bools store which points are different
            northeast = (!input.isInside(point.northeast()) || type!=input[point.northeast()]);
            southeast = (!input.isInside(point.southeast()) || type!=input[point.southeast()]);
            southwest = (!input.isInside(point.southwest()) || type!=input[point.southwest()]);
            northwest = (!input.isInside(point.northwest()) || type!=input[point.northwest()]);
            if (northeast && !north && !east) {sides++;}
            if (southeast && !south && !east) {sides++;}
            if (southwest && !south && !west) {sides++;}
            if (northwest && !north && !west) {sides++;}
        }
        price+= area*sides;
    }
    printSolution(price, true);
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
