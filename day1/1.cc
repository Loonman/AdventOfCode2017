#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include "ringbuffer.hh"
int sum_matches_next_number(std::string input);

int sum_matches_half_rotation(std::string input);

int main() 
{
    std::fstream inputfile;
    inputfile.open("./input.txt");
    std::string input;
    
    inputfile >> input;
    int part1 = sum_matches_next_number(input);
    std::cout << part1 << std::endl;
    int part2 = sum_matches_half_rotation(input);
    std::cout << part2 << std::endl;
}

int sum_matches_next_number(std::string input)
{
    
    std::string::iterator inputIterator;
    std::vector<int> matches;
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
    return std::accumulate(matches.begin(), matches.end(), 0);
}

int sum_matches_half_rotation(std::string input) {
    int size = input.length();
    int offset = size/2;
    std::cout << size << " " << offset << std::endl;
    RingBuffer<int> buffer(size);

    std::string::iterator inputIterator;
    std::vector<int> matches;
    for(inputIterator = input.begin(); inputIterator != input.end(); inputIterator++)
    {
        buffer.put(*inputIterator - '0');
    }

    for(int i = 0; i < offset; i++)
    {
        if(buffer.read(i) == buffer.read(i + offset))
        {
            matches.push_back(buffer.read(i));
        }
    }
    return std::accumulate(matches.begin(), matches.end(), 0) * 2;
}