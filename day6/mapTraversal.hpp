#include <string>
#include <array>
#include <vector>
#include <fstream>

class mapTraversal{
    public:
        void readFile(const std::string& filename);
        void findStart();
        void traverseMap();
        void tryObstacles();
        size_t getPathLength(){ return pathLength;}
        size_t getLoopOptions(){ return loopOptions;}
    private:
        bool atEdge();
        bool traverseMapLoop();
        void printMarkedMap();

        size_t pathLength = 0; // Part 1 answer
        size_t loopOptions = 0; // Part 2 answer

        std::vector<std::vector<char>> original_map;
        std::vector<std::vector<char>> marked_map;
        size_t height;
        size_t width;
        std::pair<size_t, size_t> start;
        std::pair<size_t, size_t> position;
        size_t directionIdx = 0;
        std::array<std::pair<int, int>, 4> directions = {{{-1,0}, {0,1}, {1,0}, {0,-1}}};

        // Map markers
        char cStart = '^';
        char cEmpty = '.';
        char cVisited = 'X';
        char cObstacle = '#';
};