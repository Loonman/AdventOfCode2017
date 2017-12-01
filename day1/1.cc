#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

int main() 
{
    std::fstream inputfile;
    inputfile.open("./input.txt");
    std::string input;
    std::vector<int> matches = std::vector<int>(50);
    inputfile >> input;
    std::string::iterator inputIterator;

    for(inputIterator = input.begin(); inputIterator != input.end(); inputIterator++)
    {
        if(*inputIterator == *(inputIterator + 1)) 
        {
            matches.push_back(*inputIterator - '0');
        }
    }
    if(*(input.begin()) == *(input.end() - 1)) 
    {
        matches.push_back(*(input.begin()) - '0');
    }
    std::cout << std::accumulate(matches.begin(), matches.end(), 0) << std::endl;
}