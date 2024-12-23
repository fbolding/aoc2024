#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>
#include "input.h"
#include "functions.h"

int main(int argc, char *argv[]){
    aoc::parseArguments(argc, argv);

    aoc::printSolution(0, false);
    aoc::printSolution(0, true);
    return 0;
}