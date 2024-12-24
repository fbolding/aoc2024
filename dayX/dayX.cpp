#include <iostream>
#include "input.h"
#include "functions.h"

using namespace aoc;

int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    Map input = readAsMap();

    // Part 1
    printSolution(0, false);

    // Part 2
    printSolution(0, true);
    return 0;
}
