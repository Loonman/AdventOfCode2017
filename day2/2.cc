#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

#include "ringbuffer.hh"
int diff_max_min(std::vector<int> input);

int sum_diff(std::fstream inputFile);

int main() 
{
    std::fstream inputfile;
    inputfile.open("./input.txt");
    std::string input;
    
    inputfile >> input;
    int part1 = diff_max_min(input);
    std::cout << part1 << std::endl;
}

int diff_max_min(std::vector<int> input)
{
    return *std::find_max(input.start(), input.end()) - *std::find_min(input.start(), input.end());
}