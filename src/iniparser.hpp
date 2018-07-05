#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

template <class value_type>
class iniFile : public std::map<std::string, std::map<std::string, value_type>>
{

  public:
    // Constructor
    iniFile() {}
    iniFile(std::string file_name) { this->read(file_name); }

    // Basic functions
    void read(std::string file_name);
    void write(std::string file_name);

    // Operator
    friend std::ostream &operator<<(std::ostream &os, const iniFile<value_type> &ini)
    {
        for (const auto &parent : ini)
        {
            os << '[' << parent.first << ']' << std::endl;
            for (const auto &[key, val] : parent.second)
            {
                os << key << '=' << val << std::endl;
            }
        }
        return os;
    }
    friend std::istream &operator>>(std::istream &is, iniFile<value_type> &ini)
    {
        for (std::string line, parent; std::getline(is, line);)
        {
            switch (line.front())
            {
            case '[':
                if (line.find_first_of(']') == line.size() - 1 && line.find_last_of('[') == 0)
                {
                    line.pop_back();
                    line.erase(line.begin());
                    parent = line;
                }
            case '#':
            case ';':
                break;
            default:
                if (line.find('=', 1))
                {
                    std::istringstream iss(line);
                    std::string name, val;
                    std::getline(iss, name, '=');
                    std::getline(iss, val);
                    ini[parent][name] = val;
                }
            }
        }
        return is;
    }
};

template <class value_type>
void iniFile<value_type>::read(std::string file_name)
{
    std::ifstream fInput(file_name);
    fInput >> (*this);
    fInput.close();
}

template <class value_type>
void iniFile<value_type>::write(std::string file_name)
{
    std::ofstream fOutput(file_name);
    fOutput << (*this);
    fOutput.close();
}