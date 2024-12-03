#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

// forward declarations
std::string read_input(const std::string& filename);
std::vector<size_t> find_mul(const std::string& input);
int check_mul(const std::string& check, bool enabled=true);
bool is_enabled(const std::string& prior_string);

int part1(const std::string& input){
    int result = 0;
    auto start_idx = find_mul(input);
    for (const auto& start: start_idx){
        size_t end = input.find(')', start); // Return the location of the first closing bracket after start_idx. Return string::npos if not found;
        if (end == std::string::npos){ break;}
        std::string check = input.substr(start, end+1-start);
        result += check_mul(check);
    }
    return result;
}

int part2(const std::string& input){
    int result = 0;
    auto start_idx = find_mul(input);
    for (const auto& start: start_idx){
        size_t end = input.find(')', start); // Return the location of the first closing bracket after start_idx. Return string::npos if not found;
        if (end == std::string::npos){ break;}
        std::string check = input.substr(start, end+1-start);
        result += check_mul(check, is_enabled(input.substr(0,start)));
    }
    return result;
}

int main(){
    auto input = read_input("input.txt");
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}

/* Notes for solution:
Part 1:
1. Read all into single string -> beware of few existing linebreaks
2. Find all substrings with mul         \
3. Find all closing brackets after mul  -> I should probably learn regex in C++ for this
4. Check if substring mul...) is valid  /
5. Perform and add up valid instructions
Part 2:
1. Same as part 1, but check if do or don't was found last
*/

// Read all the lines in the file
std::string read_input(const std::string& filename){
    std::ifstream file(filename); 

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

std::vector<size_t> find_mul(const std::string& input){
    std::vector<size_t> start_idx;
    size_t idx=0;
    std::string match = "mul";
    while (idx < input.size()-match.size()){
        if (!match.compare(input.substr(idx, match.size()))){ // Compare returns 0 if string is equal
            start_idx.push_back(idx);
        }
        idx++;
    }
    return start_idx;
}

int check_mul(const std::string& check, bool enabled){
    // Return 0 if invalid, return multiplication if valid
     // See https://regex101.com/ for regex explanations
    if (!enabled){
        return 0;
    }
    std::regex pattern(R"(^mul\(\d{1,3},\d{1,3}\)$)"); // R for raw string literal to write regex patterns
    if (!std::regex_match(check, pattern)){
        return 0;
    }
    // Extract first and second value and return multiplication. Follow example: https://stackoverflow.com/questions/59066457/extracting-numbers-from-mixed-string-using-stringstream
    std::regex digit_pattern(R"(\d{1,3})");
    std::smatch match;
    std::string s = check;
    int mul = 1;
    while(std::regex_search(s, match, digit_pattern)){
        mul *= std::stoi(match.str());
        s = match.suffix();
    }
    return mul;
}

bool is_enabled(const std::string& prior_string){
    size_t do_idx = 0;
    size_t donot_idx = 0;
    std::regex do_pattern(R"(do\(\))");
    // Example: https://stackoverflow.com/questions/76041087/c-finding-the-positions-of-regex-matches-in-a-string
    auto begin_do = std::sregex_iterator {prior_string.begin(), prior_string.end(), do_pattern};
    auto end_do = std::sregex_iterator();
    for (std::sregex_iterator i = begin_do; i != end_do; ++i){
        //std::cout << "Found match at position: " << i->position() << "\n";
        do_idx = i->position();
    }

    std::regex donot_pattern(R"(don't\(\))");
    auto begin_donot = std::sregex_iterator {prior_string.begin(), prior_string.end(), donot_pattern};
    auto end_donot = std::sregex_iterator();
    for (std::sregex_iterator i = begin_donot; i != end_donot; ++i){
        //std::cout << "Found match at position: " << i->position() << "\n";
        donot_idx = i->position();
    }
    //std::cout << prior_string << std::endl;
    //std::cout << "Do idx: " << do_idx << "; Donot idx: " << donot_idx << "; Enabled: " << (do_idx>=donot_idx) << std::endl;
    return do_idx >= donot_idx;
}