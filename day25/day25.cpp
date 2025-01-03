#include <iostream>
#include "input.h"
#include "functions.h"

using namespace aoc;

int main(int argc, char *argv[]){
    // Read input
    parseArguments(argc, argv);
    std::vector<Map> input = readAsMultiMap();
    std::vector<std::vector<int>> keys;
    std::vector<std::vector<int>> locks;
    // Part 1
    for (const auto& map: input){
        int nPins = 5;
        std::vector<int> heights;
        // Determine if key or lock. Get heights
        if (map[0][0] == '#'){
            for (int pin=0; pin<nPins; pin++){
                int height = 0;
                while (map[1+height][pin]=='#'){
                    height++;
                }
                heights.push_back(height);
            }
            locks.push_back(heights);
        } else {
            for (int pin=0; pin<nPins; pin++){
                int height = 0;
                while (map[map.getHeight()-2-height][pin]=='#'){ // getHeight returns amount of rows. Second-to-lowest row index is getHeight()-2
                    height++;
                }
                heights.push_back(height);
            }
            keys.push_back(heights);
        }
    }

    size_t unique_pairs = 0;
    for (const auto& lock: locks){
        for (const auto& key: keys){
            int column =0;
            bool fit = true;
            for (int col=0; col < lock.size(); col++){
                if (lock[col]+key[col] > input[0].getHeight()-2){ fit = false;}
            }
            unique_pairs += fit;
        }
    }
    printSolution(unique_pairs, false);

    // Part 2
    printSolution("Get all other stars from this year to obtain the second star of day 25!", true);
    return 0;
}
