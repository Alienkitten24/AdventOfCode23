#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <regex>
#include <map>

int main () {

    std::string line;
    std::ifstream input ("day1input.txt");
    int p1_sum = 0;
    int p2_sum = 0;

    while (getline(input, line)) { 

        // part 1: use 2 pointers to find numbers 

        char* l_ptr = &line[0]; 
        char* r_ptr = &line[line.size() - 1];

        while(!isdigit(*l_ptr) && l_ptr < &line[line.size() - 1]) {
            l_ptr++;
        }

        while(!isdigit(*r_ptr) && r_ptr > &line[0]) {
            r_ptr--;
        }

        p1_sum += 10*(*l_ptr - '0') + (*r_ptr - '0');



        // part 2
        // still have two pointers, but check for regex match in whatever is 
        // in front of pointer ie if input is "one4" look for one

        std::map<std::string, int> word_to_int = {
            {"zero", 0},
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9}
        };


        // split string into before and after first and last digits
        std::size_t l_position = l_ptr - line.c_str();
        std::size_t r_position = r_ptr - line.c_str();
        
        std::string l_slice = line.substr(0, l_position);
        std::string r_slice = line.substr(r_position + 1, line.size() - 1);

        // regex match in front of first digit
        std::regex l_pattern("(zero|one|two|three|four|five|six|seven|eight|nine)");
        std::smatch l_match;
        if (std::regex_search(l_slice, l_match, l_pattern)) {
            p2_sum += 10*(word_to_int[l_match[0].str()]);
        }
        else {
            p2_sum += 10*(*l_ptr - '0');
        }
        
        //regex match behind last digit
        // reverse strings so that "3twone" finds one and not two

        // reverse r_slice
        for (size_t i = 0; i < r_slice.length() / 2; ++i) {
            std::swap(r_slice[i], r_slice[r_slice.length() - 1 - i]);
        }

        std::regex r_pattern("(orez|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin)");
        std::smatch r_match;
        if (std::regex_search(r_slice, r_match, r_pattern)) {
            std::string output = r_match[0];
        
            // reverse r_match
            for (size_t i = 0; i < output.length() / 2; ++i) {
                std::swap(output[i], output[output.length() - 1 - i]);
            }

            p2_sum += word_to_int[output];
        }
        else {
            p2_sum += (*r_ptr - '0');
        }
    }

    std::cout << p1_sum << "\n";
    std::cout << p2_sum;

    return 0;
}
