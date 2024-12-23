#include "functions.h"
#include <iostream>
void aoc::printSolution(const size_t &solution, bool isPart2){
        std::cout << "Part "<< (isPart2? 2:1) << ": " << solution << std::endl;
}