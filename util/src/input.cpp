#include "input.h"
#include <iostream>
#include <fstream>
#include <unistd.h>



/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 */
void aoc::parseArguments(int argc, char *argv[]){
    int opt;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "ht")) != -1) {
        switch (opt) {
            case '?':
            case 'h':
            default:
                std::cout << "Usage: " << argv[0] << " [-t]\n";
                break;
            case 't':
                useExample = true;
                break;
        }
    }
}

/**
 * @brief Read input as string
 * 
 * @param filename 
 * @return std::string 
 */
std::string aoc::readAsString(std::string filename){
    filename = (filename.empty() ? (useExample ? "sample.txt" : "input.txt") : filename);
    std::ifstream file(filename);
    if (!file.is_open()) { throw std::runtime_error("Failed to open file: " + filename);}
    std::string input;
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        // Add the line into the string
        input.append(line);
    }
    return input; 
}

std::vector<std::string> aoc::readAsMultiString(std::string filename){
    filename = (filename.empty() ? (useExample ? "sample.txt" : "input.txt") : filename);
    std::ifstream file(filename);
    if (!file.is_open()) { throw std::runtime_error("Failed to open file: " + filename);}
    std::vector<std::string> input;
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        // Add the line into the string
        input.push_back(line);
    }
    return input; 
}

std::vector<std::vector<char>> aoc::readAsChar2D(std::string filename){
    filename = (filename.empty() ? (useExample ? "sample.txt" : "input.txt") : filename);
    std::ifstream file(filename); 
    if (!file.is_open()) { throw std::runtime_error("Failed to open file: " + filename);}
    
    std::vector<std::vector<char>> array;
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        std::vector<char> line_vector;
        for (char c: line){
            line_vector.push_back(c);
        }
        // Add the line into the vector
        array.push_back(line_vector); 
    }
    return array; 
}

aoc::Map aoc::readAsMap(std::string filename){
    return aoc::Map(readAsChar2D(filename));
}

std::vector<aoc::Map> aoc::readAsMultiMap(std::string filename){
    filename = (filename.empty() ? (useExample ? "sample.txt" : "input.txt") : filename);
    std::ifstream file(filename); 
    if (!file.is_open()) { throw std::runtime_error("Failed to open file: " + filename);}
    std::vector<aoc::Map> multiMap;
    std::vector<std::vector<char>> array;
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        std::vector<char> line_vector;
        if (line.empty()){ // Getline drops "\n", therefore it will be empty
            multiMap.push_back(aoc::Map(array));
            array.clear();
            continue;
        }
        for (char c: line){
            line_vector.push_back(c);
        }
        // Add the line into the vector
        array.push_back(line_vector); 
    }
    if (!array.empty()){
        multiMap.push_back(aoc::Map(array));
    }
    return multiMap; 
}
