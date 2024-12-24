#include <iostream>
#include "input.h"
#include "functions.h"

using namespace aoc;

int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    std::vector<std::string> input = splitString(readAsString());
    
    // Part 1
    int nBlinks = 25;
    /* Unfortunately brute force does not seem to work
    std::vector<std::string> current = input;
    //printVector(current, " ");
    for (int i=0; i<nBlinks; i++){
        std::vector<std::string> temp;
        for (const auto& stone: current){
            if (stone=="0"){
                temp.push_back("1");
            } else if (stone.size()%2==0){
                temp.push_back(stone.substr(0, stone.size()/2));
                temp.push_back(std::to_string(std::stol(stone.substr(stone.size()/2))));
                temp.back().erase(0,temp.back().find_first_not_of('0')); // Remove leading zeros
            } else {
                temp.push_back(std::to_string(std::stol(stone)*2024));
            }
        }
        current = temp;
        //printVector(current, " ");
    }
    printSolution(current.size(), false);
    */
    // Part 2
    printSolution(0, true);
    return 0;
}
