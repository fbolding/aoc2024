#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <cmath>

// forward declarations
std::vector<std::string> read_all_lines(std::string const& filename);
void split_vector(std::vector<std::string>const& string_vector, std::vector<int>& left, std::vector<int>& right);
void sort_vector(std::vector<int>& vector);
int count_occurences(const std::vector<int> vector, int value);

int part1(const std::vector<std::string>& input){
    std::vector<int> left, right;
    split_vector(input, left, right);
    sort_vector(left);
    sort_vector(right);
    int res = 0;
    for (int i=0; i<left.size(); i++){
        res+= std::abs(right[i] - left[i]);
    }
    return res;
}

int part2(const std::vector<std::string>& input){
    int sim_score =0;
    std::vector<int> left, right;
    split_vector(input, left, right);
    for (int num: left){
        sim_score+= num * count_occurences(right, num);
    }
    return sim_score;
}

int main(){
    auto lines = read_all_lines("input.txt");
    bool test = false;
    // Print output for test
    if (test){
    for (auto& line: lines){
        std::cout<< line << std::endl;}
    }
    std::cout << "Part 1: " << part1(lines) << std::endl;
    std::cout << "Part 2: " << part2(lines) << std::endl;
    return 0;
}

// Notes for solution:
// Part 1:
// 1. read input in vector with strings
// 2. split vector into two vectors
// 3. turn vector with strings into vector with integers
// 4. sort vectors
// 5. match sorted vectors and sum distances
// Part 2:
// 1. part 1 1-3

// Read all the lines in the file
std::vector<std::string> read_all_lines(std::string const& filename){
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

void split_vector(std::vector<std::string>const& string_vector, std::vector<int>& left, std::vector<int>& right){
    std::string delim = "   ";
    for (const std::string& line: string_vector){
        std::string lstr =  line.substr(0, line.find(delim));
        std::string rstr = line.substr(line.find(delim), std::string::npos);
        //std::cout << lstr << "---" << rstr << std::endl; // Test split strings

        // Turn split string to int and place back
        left.push_back(std::stoi(lstr));
        right.push_back(std::stoi(rstr));
    }
}

void sort_vector(std::vector<int>& vector){
    stable_sort(vector.begin(), vector.end());
}

int count_occurences(const std::vector<int> vector, int value){
    int occurences = 0;
    for (int num: vector){
        if (num==value){
            occurences++;
        }
    }
    return occurences;
}