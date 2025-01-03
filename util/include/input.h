#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "map.h"
namespace aoc{
    static bool useExample;
    void parseArguments(int argc, char *argv[]);
    std::string readAsString(std::string filename= "");
    std::vector<std::string> readAsMultiString(std::string filename= "");
    std::vector<std::vector<char>> readAsChar2D(std::string filename= "");
    Map readAsMap(std::string filename= "");
    std::vector<Map> readAsMultiMap(std::string filename= "");
}

#endif