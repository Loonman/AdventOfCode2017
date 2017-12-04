#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

int diff_max_min(std::vector<int> input);

int sum_diff(std::fstream& inputFile);

int sum_divisible_nums(std::fstream& inputFile);

int well_do_it_in_nsquared(std::vector<int> input);

int main() 
{
    
    std::fstream inputfile;
    inputfile.open("./input.txt");

    //int part1 =  sum_diff(inputfile);
    //std::cout << part1 << std::endl;
    int part2 = sum_divisible_nums(inputfile);
    std::cout << part2 << std::endl;
}

int sum_diff(std::fstream& inputFile)
{
    std::string input;
    std::vector<int> inputs;
    int sum = 0;
    //Get Line
    while(std::getline(inputFile, input))
    {
        std::string num;
        std::stringstream s(input);
        while(std::getline(s, num, '\t'))
        {
            inputs.push_back(stoi(num));
        }
        sum += diff_max_min(inputs);
        inputs.clear();
    }
    return sum;
}

int sum_divisible_nums(std::fstream& inputFile)
{
    std::string input;
    std::vector<int> inputs;
    int sum = 0;
    //Get Line
    while(std::getline(inputFile, input))
    {
        std::string num;
        std::stringstream s(input);
        while(std::getline(s, num, '\t'))
        {
            inputs.push_back(stoi(num));
        }
        sum += well_do_it_in_nsquared(inputs);
        inputs.clear();
    }
    return sum;
}

int well_do_it_in_nsquared(std::vector<int> input)
{
    std::vector<int>::iterator it;
    std::vector<int>::iterator it2;
    for(it = input.begin(); it != input.end(); it++)
    {
        for(it2 = input.begin(); it2 != input.end(); it2++)
        {
            if(it2 != it)
            {
                if(*it2 % *it == 0)
                {
                    return *it2 / *it;
                } 
                else if (*it % *it2 == 0)
                {
                    return *it / *it2;
                }
            }
        }
    }
}

int diff_max_min(std::vector<int> input)
{
    return *std::max_element(input.begin(), input.end()) - *std::min_element(input.begin(),input.end());
}