#ifndef DISKMAP_H
#define DISKMAP_H
#include <string>
#include <vector>
#include <map>
#include <utility>

class DiskMap{
public:
    DiskMap(std::string input): denseOriginal(input){}
    void readDenseFormat();
    void moveFilesLeft();
    size_t calculateChecksum(const std::vector<std::string> blocks);
    void moveFilesPart2();

    std::string denseOriginal;
    std::vector<std::string> original;
    std::vector<std::string> compact;
    std::vector<std::string> compact2;

    // Part 2
    size_t maxID;
    std::map<size_t, std::pair<size_t, size_t>> fileInfo;// Key is ID, pair.first is current location of first element and pair.second is required space
    std::vector<std::pair<size_t, size_t>> freeInfo; // Ordered in order of appearance. Pair.first is location of free space and pair.second is amount of free space
};
#endif