#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <cstddef>
#include <iostream>
#include <vector>
namespace aoc{
template <typename T> 
void printSolution(const T& solution= 0, bool isPart2= false){
    std::cout << "Part "<< (isPart2? 2:1) << ": " << solution << std::endl;
}

template <typename T> 
void printVector(const std::vector<T>& vec){
    for (const T& val: vec){
        std::cout << val;
    }
    std::cout << "\n";
}
}
#endif