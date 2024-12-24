#include <iostream>
#include "input.h"
#include "functions.h"
#include "diskmap.h"

using namespace aoc;

int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    std::string input = readAsString();
    DiskMap map(input);
    map.readDenseFormat();

    // Part 1
    map.moveFilesLeft();
    printSolution(map.calculateChecksum(map.compact), false);

    // Part 2
    map.moveFilesPart2();
    printSolution(map.calculateChecksum(map.compact2), true);
    return 0;
}
