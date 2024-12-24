#include "diskmap.h"
#include <iostream>

void DiskMap::readDenseFormat(){
    bool isFile = true;
    int id = 0;
    std::string val;
    for (char c: denseOriginal){
        if (isFile){ 
            val = std::to_string(id);
            fileInfo[id] = std::make_pair(original.size(), c-'0');
            id++;
        }
        else{ val = ".";
            freeInfo.push_back(std::make_pair(original.size(), c-'0'));
        }
        for (int i=0; i<c-'0'; i++){ // Subtract ASCII code from char to turn to int
            original.push_back(val);
        }
        isFile = !isFile; // Toggle isFile
    }
    maxID = id-1;
}

void DiskMap::moveFilesLeft(){
    size_t left = 0;
    size_t right = original.size()-1;
    while (left<=right){
        if (original[left]!="."){
            compact.push_back(original[left]);
            left++;
        } else{
            while(original[right]=="."){
                right--;
            }
            compact.push_back(original[right]);
            left++;
            right--;
        }
        if (left!=compact.size()){
            std::cout << "Something is wrong!";
        }
    }
}

size_t DiskMap::calculateChecksum(const std::vector<std::string> blocks){
    size_t result = 0;
    size_t position = 0;
    char* p;
    for (const auto& id: blocks){
        long converted = std::strtol(id.c_str(), &p, 10);
        if (*p) {
            char* p;
            position++;
            continue;
        } 
        result += converted * position;
        position++;
    }
    return result;
}

void DiskMap::moveFilesPart2(){
    // Recreate filesystem from file info, starting with completely empty
    compact2 = std::vector<std::string>(original.size(), ".");
    // I need two pieces of information: 
    // 1. location of free space and amount of free space
    // 2. Space required per ID and its current location

    // For the pairs: .first stores location and .second stores size
    for (size_t id = maxID; id>0; id--){
        auto& file = fileInfo[id];
        for (auto& free: freeInfo){
            if (file.first < free.first){ break;}
            if (file.second <= free.second){
                file.first = free.first;
                free.first += file.second;
                free.second -= file.second;
            }
        }
        for (int i=0; i<file.second; i++){
            compact2[file.first+i] = std::to_string(id);
        }
    }
}
