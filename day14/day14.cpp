#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <regex>
#include "robot.h"

//#define TEST
#ifdef TEST
#define INPUT "sample.txt"
#define WIDTH 11
#define HEIGHT 7
#else
#define INPUT "input.txt"
#define WIDTH 101
#define HEIGHT 103
#endif

// forward declarations
std::vector<std::string> read_all_lines(const std::string& filename);
std::vector<robot> initialize_robots(const std::vector<std::string>& input);
std::vector<int> extract_values(const std::string& input);
void print_map(const std::vector<robot>& robot_list);

int part1(const std::vector<std::string>& input){
    auto robot_list = initialize_robots(input);
    int sim_time = 100;
    int time = 0;
    while (time < sim_time){
        for (auto& r: robot_list){
            r.simulate();
        }
        time++;
    }
    std::array<int, 4> quadrant_score = {0, 0, 0, 0};
    int quadrant;
    for (auto& r: robot_list){
        quadrant = r.getQuadrant();
        if (quadrant == -1){ continue;}
        quadrant_score[quadrant]++;
    }
    //print_map(robot_list);
    return quadrant_score[0]*quadrant_score[1]*quadrant_score[2]*quadrant_score[3];
}

int part2(const std::vector<std::string>& input){
    auto robot_list = initialize_robots(input);
    int time = 0;
    bool stop = false;
    while (!stop){
        time++;
        for (auto& r: robot_list){
            r.simulate();
        }
        std::cout << "Time: " << time << " seconds." << std::endl;
        //print_map(robot_list);
        std::cout << "Continue? (y/n): ";
        //char user_input;
        //std::cin >> user_input;
        //stop = (user_input=='n');
        stop = time==7055;
    }
    print_map(robot_list);
    return time;
}

int main(){
    auto lines = read_all_lines(INPUT);
    std::cout << "Part 1: " << part1(lines) << std::endl;
    std::cout << "Part 2: " << part2(lines) << std::endl;
    return 0;
}

/* Notes for solution:
Part 1:
1. 
Part 2:
*/

// Read all the lines in the file
std::vector<std::string> read_all_lines(const std::string& filename){
    std::ifstream file(filename); 

    std::vector<std::string> lines;
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        // Add the line into the vector
        lines.push_back(std::move(line)); 
    }
    return lines; 
}

std::vector<robot> initialize_robots(const std::vector<std::string>& input){
    std::vector<robot> robot_list;
    std::vector<int> line_values;
    int id = 1;
    for (const auto& line: input){
        line_values = extract_values(line);
        robot_list.push_back(robot(id, line_values[0], line_values[1], line_values[2], line_values[3], WIDTH, HEIGHT));
        id++;
    }
    return robot_list;
}

std::vector<int> extract_values(const std::string& input) {
    std::vector<int> numbers;
    std::regex regex(R"(-?\d+)");
    std::sregex_iterator it(input.begin(), input.end(), regex);
    std::sregex_iterator end;

    while (it != end) {
        numbers.push_back(std::stoi(it->str()));
        ++it;
    }

    return numbers;
}

void print_map(const std::vector<robot>& robot_list){
    std::array<std::array<int, WIDTH>, HEIGHT> map;
    for (auto& ar: map){ ar.fill(0);};
    for (const auto& r: robot_list){
        map[r.y][r.x]++;
    }
    // Print map
    std::cout << std::endl;
    for (size_t row=0; row<HEIGHT; row++){
        for (size_t col=0; col<WIDTH; col++){
            if (!map[row][col]){ std::cout << '.';}
            else{ std::cout << map[row][col];}
        }
        std::cout << std::endl;
    }
}