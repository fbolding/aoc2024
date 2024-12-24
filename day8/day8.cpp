#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unistd.h>
#include <fstream>
#include "input.h"
#include "map.h"
#include "functions.h"
using namespace aoc;

int main(int argc, char *argv[]){
    parseArguments(argc, argv);
    Map input = readAsMap();

    // Part 1
    std::map<char, std::vector<Point>> antennas;
    for (const auto p: input.getPoints()){
        if (input[p]!='.'){
            antennas[input[p]].push_back(p);
        }
    }
    std::set<Point> antinodesP1;
    for (const auto& [frequency, vec]: antennas){
        Point antinode;
        for (const auto& a1: vec){
            for (const auto& a2: vec){
                if (a1==a2){ continue;}
                antinode = a1 + a1-a2;
                if (input.isInside(antinode)){
                    antinodesP1.insert(antinode);
                }                
            }
        }
    }
    printSolution(antinodesP1.size(), false);

    // Part 2
    std::set<Point> antinodesP2;
    for (const auto& [frequency, vec]: antennas){
        Point diff;
        Point antinode;
        for (const auto& a1: vec){
            for (const auto& a2: vec){
                if (a1==a2){ continue;}
                diff = a1-a2;
                antinode = a1;
                while (input.isInside(antinode)){
                    antinodesP2.insert(antinode);
                    antinode -= diff;
                }
                antinode = a2;
                while (input.isInside(antinode)){
                    antinodesP2.insert(antinode);
                    antinode += diff;
                }
            }
        }
    }
    printSolution(antinodesP2.size(), true);
    return 0;
}
