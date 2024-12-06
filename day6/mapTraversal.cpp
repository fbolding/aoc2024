#include <iostream>
#include "mapTraversal.hpp"

std::pair<size_t, size_t> operator +(const std::pair<size_t, size_t>& position, const std::pair<int, int>& direction) {
    return std::make_pair(position.first + direction.first, position.second + direction.second);
}
std::pair<size_t, size_t> operator -(const std::pair<size_t, size_t>& position, const std::pair<int, int>& direction) {
    return std::make_pair(position.first - direction.first, position.second - direction.second);
}

void mapTraversal::readFile(const std::string& filename) {
    std::ifstream file(filename); 
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        std::vector<char> line_vector;
        for (char c: line){
            line_vector.push_back(c);
        }
        // Add the line into the vector
        original_map.push_back(line_vector); 
    }
    height = original_map.size();
    width = original_map[0].size();
}

void mapTraversal::findStart() {
    for(size_t row=0; row<height; row++){
        for(size_t col=0; col<height; col++){
            if (original_map[row][col] == cStart){
                start.first = row;
                start.second = col;
                return;
            }
        }
    }
    // Error handling for not having found start...
}

void mapTraversal::traverseMap() {
    marked_map = original_map;
    position = start;
    directionIdx = 0;
    auto new_position = position;
    marked_map[position.first][position.second] = cVisited;
    pathLength++; // Increment for start position
    while (!atEdge()){
        new_position = position+directions[directionIdx];
        while(original_map[new_position.first][new_position.second] == cObstacle){
            directionIdx = (directionIdx+1)==directions.size()? 0 : directionIdx+1; // Wrap index to size of directions array
            new_position = position+directions[directionIdx];
        }
        position = new_position;
        if (marked_map[position.first][position.second] != cVisited){
            marked_map[position.first][position.second] = cVisited;
            pathLength++; // Increment for new position
        }
    }
}

void mapTraversal::tryObstacles() {
    loopOptions = 0;
    for(size_t row=0; row<height; row++){
        for(size_t col=0; col<height; col++){
            marked_map = original_map;
            if (marked_map[row][col] == cEmpty){
                marked_map[row][col] = cObstacle;
            }
            loopOptions += traverseMapLoop();
        }
    }
}

bool mapTraversal::atEdge() {
    return (position.first == 0 || position.second == 0 || position.first == height-1 || position.second == width-1);
}

bool mapTraversal::traverseMapLoop() {
    size_t maxSteps = width * height;
    size_t currentStep = 0;
    position = start;
    directionIdx = 0;
    auto new_position = position;
    marked_map[position.first][position.second] = cVisited;
    while (!atEdge()){
        if (currentStep > maxSteps){
            return true;
        }
        new_position = position+directions[directionIdx];
        while(marked_map[new_position.first][new_position.second] == cObstacle){
            directionIdx = (directionIdx+1)==directions.size()? 0 : directionIdx+1; // Wrap index to size of directions array
            new_position = position+directions[directionIdx];
        }
        position = new_position;
        if (marked_map[position.first][position.second] != cVisited){
            marked_map[position.first][position.second] = cVisited;
        }
        currentStep++;
    }
    return false; // Succesfully exited map
}

void mapTraversal::printMarkedMap() {
    std::cout << std::endl;
    for(size_t row=0; row<height; row++){
        for(size_t col=0; col<height; col++){
            std::cout << marked_map[row][col];
        }
        std::cout << std::endl;
    }
}