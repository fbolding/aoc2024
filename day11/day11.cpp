#include <iostream>
#include "input.h"
#include "functions.h"
#include <map>
#include <sstream>

using namespace aoc;

size_t simulate(const std::map<std::string, size_t>& original, int nBlinks);
void insertStone(std::map<std::string, size_t>& dict, std::string inscription, size_t count = 1);
size_t countStones(const std::map<std::string, size_t>& dict);

int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    std::vector<std::string> input = splitString(readAsString());
    std::map<std::string, size_t> original;
    for (const auto& stone: input){
        insertStone(original, stone);
    }    

    // Part 1
    printSolution(simulate(original, 25), false);

    // Part 2
    printSolution(simulate(original, 75), false);
    return 0;
}

size_t simulate(const std::map<std::string, size_t> &original, int nBlinks){
    auto current = original;
    for (int i=0; i<nBlinks; i++){
        std::map<std::string, size_t> temp;
        for (const auto& pair: current){
            // First is incsription on stone, second is count of stones with that inscription
            std::string stone = pair.first;
            size_t count = pair.second;
            if (stone.size() == 0){
                std::cout << count << "\n";
            }
            if (stone=="0"){
                insertStone(temp, "1", count);
            } else if (stone.size()%2==0){
                if (stone.size() == 0){ continue;}
                std::string stone1 = stone.substr(0, stone.size()/2);
                std::string stone2 = stone.substr(stone.size()/2);
                stone2.erase(0,stone2.find_first_not_of('0')); // Remove leading zeros
                if (stone2.size() ==0){ stone2 = "0";}
                insertStone(temp, stone1, count);
                insertStone(temp, stone2, count);
            } else{
                size_t res;
                std::stringstream sstream(stone);
                sstream >> res; // Use sstream to turn string to size_t. Numbers were too big to use stol which resulted in negative values.
                res*=2024;
                insertStone(temp, std::to_string(res), count);
            }
        }
        current = temp;
    }
    return countStones(current);
}

void insertStone(std::map<std::string, size_t> &dict, std::string inscription, size_t count)
{
    if (dict.count(inscription)){
        dict[inscription]+= count;
    } else {
        dict[inscription] = count;
    }
}

size_t countStones(const std::map<std::string, size_t> &dict){
    size_t count = 0;
    for (const auto& pair: dict){
        count += pair.second;
    }
    return count;
}
