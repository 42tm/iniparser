#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

template <class __data_type>
class iniFile : public std::map<std::string, std::map<std::string, __data_type>>
{

  public:
    // Constructor
    iniFile() {}
    iniFile(std::string filename) { this->read(filename); }

    // Basic functions
    __data_type test(__data_type);
    void read(std::string);
    void write(std::string);
    void setBuffSize(const unsigned int &_Count) { this->buff_size = _Count; }

    // Operator
    friend std::ostream &operator<<(std::ostream &os, const iniFile<__data_type> &ini)
    {
        for (const auto &parent : ini)
        {
            os << '[' << parent.first << ']' << std::endl;
            for (const auto &[name, val] : parent.second)
            {
                os << name << '=' << val << std::endl;
            }
        }
        return os;
    }

  private:
    ssize_t buff_size = 256;
};

template <class __data_type>
void iniFile<__data_type>::read(std::string filename)
{
    std::ifstream fInput(filename);
    std::string parent;
    for (std::string line; std::getline(fInput, line);)
    {
        switch (line.front())
        {
        case '[':
            if (line.find_first_of(']') == line.size() - 1 && line.find_last_of('[') == 0)
            {
                line.pop_back();
                line.erase(line.begin());
                parent = line;
#ifdef __INIPARSER_DEBUG__
                std::cout << "[" << line << "]" << std::endl;
#endif
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
                (*this)[parent][name] = val;
#ifdef __INIPARSER_DEBUG__
                std::cout << name << ':' << val << std::endl;
#endif
            }
        }
    }
    fInput.close();
}

template <class __data_type>
void iniFile<__data_type>::write(std::string filename)
{
    std::ofstream fOutput(filename);
    fOutput << (*this);
    fOutput.close();
}