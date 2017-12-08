#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <regex>
#include <map>

void get_exit(std::fstream& inputFile);
int process_tape(std::vector<int> tape);
int main()
{
    std::fstream inputfile;
    
    inputfile.open("input.txt");
    
    get_exit(inputfile);
}

void get_exit(std::fstream& inputFile)
{
    std::vector<int> tape;
    std::string instruction;
    while(getline(inputFile, instruction))
    {
        tape.push_back(std::stoi(instruction));
    }

    std::cout << process_tape(tape) << std::endl;
}

int process_tape(std::vector<int> tape)
{
    int steps = 0;
    int i = 0;
    int max = tape.size();
    while(i >= 0 && i < max)
    {
        int temp = tape[i];
        if(temp >= 3 )
        {
            tape[i]--;
        }
        else
        {
            tape[i]++;
        }
        i = i + temp;
        steps++;
    }
    return steps;
}