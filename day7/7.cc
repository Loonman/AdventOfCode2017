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

typedef std::pair<int, int> MyPairType;
struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second < right.second;
    }
};

class Program {
    public:

    Program(std::string define)
    {
        std::stringstream definestr (define);
        std::getline(definestr, this->name, ' ');
        std::string remain = definestr.str();
        std::smatch sm;
        std::regex weights_subprograms ("(?:\\w+ )(?:\\((\\d+)\\))(?: -> )?((?:[\\w]+, )*[\\w]+)?");
        std::regex_match(remain, sm, weights_subprograms);
        
        this->weight = std::stoi(sm[1]);
        std::string match;

        std::stringstream subprograms(sm[2].str());
        while(std::getline(subprograms, match, ','))
        {
            if(*(match.begin()) == ' ')
            {
                match = match.substr(1, match.size());
            }

            this->above.push_back(match);
            
        }
    }

    int set_tower_weight(bool root)
    {
        
        if(this->tower.empty())
        {
            return this->weight;
        }
        else 
        {
            int result = this->weight;
            for(auto it = tower.begin(); it < tower.end(); it++)
            {
                result += it->set_tower_weight(false);
            }

            this->tower_weight = result - this->weight;
            
            return result;
        }
    }

    int total_weight()
    {
        return this->weight + this->tower_weight;
    }

    Program * get_program_from_weight(int weight)
    {
        for(auto it = this->tower.begin(); it < this->tower.end(); it++)
        {
            if(it->total_weight() == weight)
            {
                return &(*it);
            }
        }
    }

    int get_tower_weight_count()
    {
        std::map<int, int> weightMap;
        for(auto it = this->tower.begin(); it < this->tower.end(); it++)
        {
            std::cout << it->total_weight() <<std::endl;
            if( weightMap.find(it->total_weight()) == weightMap.end())
            {
                std::pair<int,int> totalWeight (it->total_weight(), 1);
                
                weightMap.insert(totalWeight);
               
                
            } else {
                std::pair<const int, int> * weightMapEntry = &(*weightMap.find(it->total_weight()));
                weightMapEntry->second++;
            }
        }
        return weightMap.size();
    }

    int get_imbalanced_weight()
    {
        std::map<int, int> weightMap;
        std::map<int, int> towerWeightMap;
        for(auto it = this->tower.begin(); it < this->tower.end(); it++)
        {
            
            if( weightMap.find(it->total_weight()) == weightMap.end())
            {
                std::pair<int,int> totalWeight (it->total_weight(), 1);
                
                weightMap.insert(totalWeight);
               
                
            } else {
                std::pair<const int, int> * weightMapEntry = &(*weightMap.find(it->total_weight()));
                weightMapEntry->second++;
            }
            
        }
        if(weightMap.size() > 1)
        {
            std::cout << weightMap.size() << std::endl;
            int wrongWeight = std::min_element(weightMap.begin(), weightMap.end(), CompareSecond())->first;
            int rightWeight = std::max_element(weightMap.begin(), weightMap.end(), CompareSecond())->first;
            std::cout << wrongWeight << std::endl;

            //This element is out of whack
            Program * result = get_program_from_weight(wrongWeight);
            std::cout << result->name << std::endl;
            std::cout << "Wrong, right " << wrongWeight << ", " << rightWeight << std::endl;
            if(result->get_tower_weight_count() == 1)
            {
                int diff = (wrongWeight > rightWeight ? rightWeight - wrongWeight : wrongWeight - rightWeight);
                return result->weight + diff;
            }
            //Something further up the tower
            else
            {
                return result->get_imbalanced_weight();
            }
        }
    }
    std::string name;
    int weight;
    int tower_weight;
    std::vector<std::string> above;
    std::vector<Program> tower;
};

void get_base_program(std::fstream& inputfile);
Program create_tower(std::vector<Program> programs, Program root);

int main()
{
    std::fstream inputfile;
    
    inputfile.open("input.txt");
    get_base_program(inputfile);

}

void get_base_program(std::fstream& inputfile)
{
    std::string programstring;
    std::vector<Program> programs;
    while(std::getline(inputfile, programstring))
    {
        programs.push_back(Program(programstring));
    }
    std::cout << "---------------" << std::endl;
    std::unordered_set<std::string> children;
    for(auto it = programs.begin(); it < programs.end(); it++)
    {
        for(auto it2 = it->above.begin(); it2 < it->above.end(); it2++)
        {
            children.insert(*it2);
        }
    }
    for(auto it = programs.begin(); it < programs.end(); it++)
    {
        if(!children.count(it->name))
        {
            std::cout << it->name << std::endl;
            Program root = create_tower(programs, *it);
            std::cout << root.set_tower_weight(true) << std::endl;
            std::cout << root.weight << std::endl;
            std::cout << root.tower_weight << std::endl;
            std::cout << root.get_imbalanced_weight();
        }
    }
}


Program create_tower(std::vector<Program> programs, Program root)
{
    Program* program = NULL;
    for(auto it = root.above.begin(); it < root.above.end(); it++)
    {
        for(auto it2 = programs.begin(); it2 < programs.end(); it2++)
        {
            if(it2->name == *it)
            {
                program = &(*it2);
                break;
            }
        }
        
        root.tower.push_back(create_tower(programs, *program));
    }
    return root;
}

