#include <iostream>
#include <vector>

// define __INIPARSER_DEBUG__ to enable debug mode
// #define __INIPARSER_DEBUG__

#include "../src/iniparser.hpp"

int main()
{
    iniFile<std::string> myFile;
    myFile.read("test//01.cfg");
    myFile.write("01.out");
}