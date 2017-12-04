#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

bool passphrase_is_valid(std::vector<std::string> passphrase);

int get_valid_passphrase_count(std::fstream& inputfile);

int main()
{
    std::fstream inputfile;
    inputfile.open("./input.txt");

    //int part1 =  sum_diff(inputfile);
    //std::cout << part1 << std::endl;
    int part2 = get_valid_passphrase_count(inputfile);
    std::cout << part2 << std::endl;
}

int get_valid_passphrase_count(std::fstream& inputfile)
{
    int sum = 0;
    std::vector<std::string> words;
    std::string line;
    std::string word;
    while(std::getline(inputfile, line))
    {
        std::string num;
        std::stringstream s(line);
        while(std::getline(s, word, ' '))
        {
            words.push_back(word);
        }
        if(passphrase_is_valid(words)) sum++;
        words.clear();
    }
    return sum;
}

bool passphrase_is_valid(std::vector<std::string> passphrase)
{
    std::unordered_set<std::string> set;
    std::vector<std::string>::iterator it;
    bool valid = true;
    for(it = passphrase.begin(); it != passphrase.end(); it++)
    {
        std::sort((*it).begin(), (*it).end());
        if(set.count(*it) != 0)
        {
            return false;
        }
        set.insert(*it);
    }
    return true;
}

