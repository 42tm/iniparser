#include <iostream>

#include "../src/iniparser.hpp"

int main()
{
    iniFile<std::string> myFile;
    myFile.read("test//01.ini");
    std::cout << myFile;
    myFile.write("01.out.ini");
}