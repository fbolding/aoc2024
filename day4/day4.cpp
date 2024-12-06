#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>

// forward declarations
std::vector<std::vector<char>> read_all_lines(const std::string& filename);
bool found_word(const std::vector<std::vector<char>>& input, std::string word, const size_t& height, const size_t& width, size_t row, size_t col, const std::pair<int,int>& direction);



int part1(const std::vector<std::vector<char>>& input){
    int nWords = 0;
    size_t height = input.size();
    size_t width = input[0].size();
    // Directions: {N,NE,E,SE,S,SW,W,NW}
    std::array<std::pair<int, int>, 8> directions = {{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};
    std::string word = "XMAS";
    for (size_t row=0; row<height; row++){
        for (size_t col=0; col<width; col++){
            if (input[row][col]!=word[0]){ continue;}
            for (const std::pair<int,int>& dir: directions){
                nWords+=found_word(input, word, height, width, row, col, dir);
            }
        }
    }
    return nWords;
}

int part2(const std::vector<std::vector<char>>& input){
    int nWords = 0;
    size_t height = input.size();
    size_t width = input[0].size();
    for (size_t row=1; row<height-1; row++){ // A can never be on edge of word search
        for (size_t col=1; col<width-1; col++){
            if (input[row][col]!='A'){ continue;}
            char TL = input[row-1][col-1];
            if (TL!='M'&&TL!='S'){ continue;}
            char TR = input[row-1][col+1];
            if (TR!='M'&&TR!='S'){ continue;}
            char BL = input[row+1][col-1];
            if (BL!='M'&&BL!='S'){ continue;}
            char BR = input[row+1][col+1];
            if (BR!='M'&&BR!='S'){ continue;}
            if (TL==BR){ continue;}
            if (BL==TR){ continue;}
            nWords++;
        }
    }
    return nWords;
}

int main(){
    auto input = read_all_lines("input.txt");
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}

/* Notes for solution:
Part 1:
1. Create array
2. Loop through array, finding all 'X'
3. When at 'X', move in all directions to find correct words
Part 2:
1. Similar, but now find all 'A'
2. Check if all corners are M 
*/

// Read all the lines in the file
std::vector<std::vector<char>> read_all_lines(const std::string& filename){
    std::ifstream file(filename); 

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

bool found_word(const std::vector<std::vector<char>>& input, std::string word, const size_t& height, const size_t& width, size_t row, size_t col, const std::pair<int,int>& direction){
    for (char letter: word){
        if(row<0 || row>=height){ return false;}
        if(col<0 || col>=width){ return false;}
        if(input[row][col]!=letter){ return false;}
        row+= direction.first;
        col+= direction.second;
    }
    return true;
}