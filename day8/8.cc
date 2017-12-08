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
enum Operation { inc, dec };
enum Comparator {eq, neq, gt, lt, gte, lte};

typedef std::pair<std::string, int> MyPairType;
struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second < right.second;
    }
};

class Condition
{
    public:
    Condition(Comparator comp, int value)
    {
        this->comp = comp;
        this->value = value;
    }
    Comparator comp;
    int value;
};

class Instruction
{
    public:
    Instruction(std::string instr)
    {
        std::regex instr_parse ("(\\w+) ((?:inc)|(?:dec)) (-?\\d+) if (\\w+) (!=|==|<|>|<=|>=) (-?\\d+)");
        std::smatch sm;
        std::regex_match(instr, sm, instr_parse);
        this->output_register = sm[1].str();
        this->operation = sm[2].str() == "inc" ? inc : dec;
        this->value = std::stoi(sm[3].str());
        Comparator comp;
        this->input_register = sm[4].str();
        if(sm[5].str() == "!=") comp = neq;
        if(sm[5].str() == "==") comp = eq;
        if(sm[5].str() == "<") comp = lt;
        if(sm[5].str() == ">") comp = gt;
        if(sm[5].str() == ">=") comp = gte;
        if(sm[5].str() == "<=") comp = lte;
        this->cond = new Condition(comp, std::stoi(sm[6].str()));
    }

    std::string output_register;
    std::string input_register;
    int value;
    Operation operation;
    Condition *cond;
};

class Computer
{
    public:
    Computer()
    {
        this->largest = 0;
    }

    void process(Instruction instr)
    {
        if(instr.cond->comp == eq)
        {
            
            if(registers[instr.input_register] == instr.cond->value)
            {
                if(instr.operation == inc)
                {
                    registers[instr.output_register] += instr.value;
                }
                else
                {
                    registers[instr.output_register] -= instr.value;
                }
            }
        }
        if(instr.cond->comp == neq)
        {
            if(registers[instr.input_register] != instr.cond->value)
            {
                if(instr.operation == inc)
                {
                    registers[instr.output_register] += instr.value;
                }
                else
                {
                    registers[instr.output_register] -= instr.value;
                }
            }
        }
        if(instr.cond->comp == lt)
        {
            if(registers[instr.input_register] < instr.cond->value)
            {
                if(instr.operation == inc)
                {
                    registers[instr.output_register] += instr.value;
                }
                else
                {
                    registers[instr.output_register] -= instr.value;
                }
            }
        }
        if(instr.cond->comp == gt)
        {
            if(registers[instr.input_register] > instr.cond->value)
            {
                if(instr.operation == inc)
                {
                    registers[instr.output_register] += instr.value;
                }
                else
                {
                    registers[instr.output_register] -= instr.value;
                }
            }
        }
        if(instr.cond->comp == lte)
        {
            if(registers[instr.input_register] <= instr.cond->value)
            {
                if(instr.operation == inc)
                {
                    registers[instr.output_register] += instr.value;
                }
                else
                {
                    registers[instr.output_register] -= instr.value;
                }
            }
        }
        if(instr.cond->comp == gte)
        {
            if(registers[instr.input_register] >= instr.cond->value)
            {
                if(instr.operation == inc)
                {
                    registers[instr.output_register] += instr.value;
                }
                else
                {
                    registers[instr.output_register] -= instr.value;
                }
            }
        }
        int current_largest = this->get_largest_register();
        this->largest = this->largest > current_largest ? this->largest : current_largest;
    }

    int get_largest_register()
    {
        return (std::max_element(registers.begin(), registers.end(), CompareSecond()))->second;
    }
    int get_largest_ever()
    {
        return this->largest;
    }
    private:
    int largest;
    std::map<std::string, int> registers;
};


void get_largest_register(std::fstream& inputFile);

int main()
{
    std::fstream inputfile;
    
    inputfile.open("input.txt");
    get_largest_register(inputfile);

}

void get_largest_register(std::fstream& inputFile)
{
    std::string instruction_str;
    Computer computer;
    int i = 0;
    while(std::getline(inputFile, instruction_str))
    {
        i++;
        computer.process(Instruction(instruction_str));
    }

    std::cout << computer.get_largest_register() <<std::endl;
    std::cout << computer.get_largest_ever()<<std::endl;

}