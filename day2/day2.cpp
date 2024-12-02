#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

// forward declarations
std::vector<std::string> read_all_lines(std::string const& filename);
bool isSafe(const std::string& report);
bool isSafe(std::vector<int> nums);
std::vector<int> splitString(const std::string&, char delim);
bool isSafeDampener(const std::string original_report);

int part1(const std::vector<std::string>& input){
    int n_safe = 0;
    for (auto report: input){
        if (isSafe(report)){
            n_safe++;
        }
    }
    return n_safe;
}

int part2(const std::vector<std::string>& input){
    int n_safe = 0;
    for (auto report: input){
        if (isSafe(report)){
            n_safe++;
        } else{
            //Try the Problem dampener
            if(isSafeDampener(report)){
                n_safe++;
            }
        }
    }
    return n_safe;
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

/* Notes for solution:
Part 1:
1. read reports
2. loop through reports, count if safe
Part 2:
1. Same as part1, with problem dampener
*/

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

bool isSafe(const std::string& report){
    return isSafe(splitString(report, ' '));
}

bool isSafe(std::vector<int> nums){
    bool isValid = true;
    bool isIncreasing;
    for (int i=0; i<nums.size()-1; i++){
        int diff = nums[i+1]-nums[i];
        if (i==0){ isIncreasing = (diff>0);}

        // Check unsafe criteria:
        // 1. Not all increasing or decreasing
        if ((diff>0)!=isIncreasing){ isValid = false;}
        // 2. Adjacent levels differ only by 1,2, 3
        if (std::abs(diff)<1){ isValid = false;}
        else if (std::abs(diff)>3) {isValid = false;}

        // Early return
        if (!isValid){ return isValid;}
    }
    return isValid;
}
std::vector<int> splitString(const std::string& input, char delim){
    // Find split points, push back substrings turned into int
    std::vector<int> result;

    std::istringstream stream(input);
    std::string temp; // temp buffer to store substrings
    while (std::getline(stream, temp, delim)){
        result.push_back(stoi(temp));
    }
    return result;
}

bool isSafeDampener(const std::string original_report){
    std::vector<int> nums = splitString(original_report, ' ');

    // Remove option
    // Check if safe
    // If so, return true
    // If not, try next number
    // If all numbers are not valid, return false
    for (int i=0; i<nums.size(); i++){
        std::vector<int> test = nums;
        test.erase(test.begin()+i);
        if (isSafe(test)){return true;}
    }
    return false;
}