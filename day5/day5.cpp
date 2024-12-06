#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
#include <chrono>

// forward declarations
void read_input(const std::string& filename, std::vector<std::pair<int,int>>& rules, std::vector<std::vector<int>>& updates);
std::array<std::vector<int>, 100> get_rule_array(const std::vector<std::pair<int,int>>& rules); // Array where index is value which should be placed before all values in vector at location 
bool check_update(const std::vector<int>& update, const std::array<std::vector<int>, 100>& rule_array);
inline int get_middle_value(const std::vector<int>& update);
std::vector<int> order_update(const std::vector<int>& incorrect_update, const std::array<std::vector<int>, 100>& rule_array, const std::vector<std::pair<int,int>>& rules);


int part1(const std::array<std::vector<int>, 100>& rule_array, const std::vector<std::vector<int>>& updates, std::vector<std::vector<int>>& incorrect_updates){
    int result = 0;
    for (const auto& update: updates){
        if (check_update(update, rule_array)){
            result += get_middle_value(update);
        } else {
            incorrect_updates.push_back(update);
        }
    }
    return result;
}

int part2(const std::array<std::vector<int>, 100>& rule_array, const std::vector<std::pair<int,int>>& rules, const std::vector<std::vector<int>>& incorrect_updates){
    int result = 0;
    for (const auto& update: incorrect_updates){
        result+=get_middle_value(order_update(update, rule_array, rules));
    }
    return result;
}

int main(){
    std::vector<std::pair<int,int>> rules; 
    std::vector<std::vector<int>> updates;
    std::vector<std::vector<int>> incorrect_updates;
    read_input("input.txt", rules, updates);
    std::array<std::vector<int>, 100> rule_array = get_rule_array(rules);
    std::cout << "Part 1: " << part1(rule_array, updates, incorrect_updates) << std::endl;
    std::cout << "Part 2: " << part2(rule_array, rules, incorrect_updates) << std::endl;
    return 0;
}

/* Notes for solution:
Part 1:
1. Read input, split into rules and updates
2. Loop through all updates
3. Loop through values, check if correct
Part 2:
1. See order_update() function for thoughts
*/

// Read all the lines in the file
void read_input(const std::string& filename, std::vector<std::pair<int,int>>& rules, std::vector<std::vector<int>>& updates){
    std::ifstream file(filename); 

    bool areRules = true;
    while(not file.eof() && not file.fail()) {
        // Get the line
        std::string line;
        std::getline(file, line);
        char delim_update = ',';
        if (areRules){
            // Check if empty line to signify change to updates
            if (line.size() <=1){
                areRules= false;
                continue;
            }
            rules.push_back({std::stoi(line.substr(0,2)), std::stoi(line.substr(3,2))}); // First is value that must be printed before second value
        } else{
            // Spilt string for all commas, push back integers
            std::stringstream ss (line);
            std::string item;
            std::vector<int> update;
            while (std::getline (ss, item, delim_update)) {
                update.push_back(std::stoi(item));
            }
            updates.push_back(update);
        }
    }
}
std::array<std::vector<int>, 100> get_rule_array(const std::vector<std::pair<int,int>>& rules){
    std::array<std::vector<int>, 100> rule_array;
    for (const auto& rule: rules){
        rule_array[rule.first].push_back(rule.second);
    }
    return rule_array;
} 
inline int get_middle_value(const std::vector<int>& update){
    return update.at(update.size()/2); // Uneven division by 2 will truncate 
}
bool check_update(const std::vector<int>& update, const std::array<std::vector<int>, 100>& rule_array){
    std::vector<int> values_before;
    for (int value: update){
        for (int value_before: values_before){
            auto it = std::find(rule_array[value].begin(), rule_array[value].end(), value_before);
            if (it!=rule_array[value].end()){ 
                return false;
            }
        }
        values_before.push_back(value);
    }
    return true;
}

std::vector<int> order_update(const std::vector<int>& incorrect_update, const std::array<std::vector<int>, 100>& rule_array, const std::vector<std::pair<int,int>>& rules){
    std::vector<int> correct_update = incorrect_update;
    // Third try (inspiration internet): loop through rules and swap values if not correct. Do this until update is correct
    while(!check_update(correct_update, rule_array)){
    for (const auto& rule: rules){
        // Check if first value in vector
        // Check if second value in vector
        // Check if current order matches rule
        // If not, swap values
        auto it_first = std::find(correct_update.begin(), correct_update.end(), rule.first);
        if (it_first==correct_update.end()){ continue;}
        auto it_second = std::find(correct_update.begin(), correct_update.end(), rule.second);
        if (it_second==correct_update.end()){ continue;}
        if (it_second<it_first){
            std::iter_swap(it_first, it_second);
        }
    }
    }
    /* Second try: bogo sort. Does not scale well to the 20+ value updates
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    while(!check_update(correct_update, rule_array)){
        std::shuffle(std::begin(correct_update), std::end(correct_update), rng);
    }
    */
    /* First try: try inserting value and moving index up if not correct. Does not work.
    for (int new_value: incorrect_update){
        bool inserted = false;
        auto idx = correct_update.begin();
        while(!inserted){
            correct_update.insert(idx, new_value);
            if (check_update(correct_update, rule_array)){
                inserted = true;
            } else {
                correct_update.erase(idx);
                idx++;
            }
        }
    }
    */
    return correct_update;
}