#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <cstddef>

namespace aoc{
template <typename T> 
void printSolution(const T& solution= 0, bool isPart2= false){
    std::cout << "Part "<< (isPart2? 2:1) << ": " << solution << std::endl;
}
}
#endif