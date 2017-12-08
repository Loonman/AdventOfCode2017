#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

void get_mem_bank_configs(std::fstream& inputfile);
std::string toString(std::vector<int> banks);

int get_first_max_index(std::vector<int> banks, int max);

int main()
{
    std::fstream inputfile;
    std::string filename;
    std::cout << "Please input the file to test: ";
    std::cin >> filename;
    inputfile.open(filename);

    get_mem_bank_configs(inputfile);
}

void get_mem_bank_configs(std::fstream& inputfile)
{
    std::unordered_set<std::string> configurations;
    std::string line;
    std::string bank;
    std::vector<int> banks;
    while(std::getline(inputfile, line))
    {
        std::stringstream s(line);
        while(std::getline(s, bank, '\t'))
        {
            banks.push_back(std::stoi(bank));
        }
    }

    int size = banks.size();
    int max = 0;
    while(configurations.count(toString(banks)) != 1)
    {
        configurations.insert(toString(banks));
        max = *std::max_element(banks.begin(), banks.end());
        int j = get_first_max_index(banks, max);
        
        banks[j] = 0;

        while(max > 0)
        {
            j++;
            banks[j%size] += 1;
            max--;
        }
    }

    std::cout << configurations.size() << std::endl;
    configurations.clear();

    std::string baseVec = toString(banks);

    while(configurations.count(baseVec) != 1)
    {
        max = *std::max_element(banks.begin(), banks.end());
        int j = get_first_max_index(banks, max);
        
        banks[j] = 0;

        while(max > 0)
        {
            j++;
            banks[j%size] += 1;
            max--;
        }
        configurations.insert(toString(banks));
    }

    std::cout << configurations.size() << std::endl;
}

std::string toString(std::vector<int> banks)
{
    std::vector<int>::iterator it;
    std::ostringstream convert;
    for(it = banks.begin(); it != banks.end(); it++)
    {
        convert << *it << " ";
    }

    return convert.str();
}

int get_first_max_index(std::vector<int> banks, int max)
{
    for(int i = 0; i < banks.size(); i++)
    {
        if(banks[i] == max) return i;
    }
}
