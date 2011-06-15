//
// Utility.cpp
//

#include "Utility.h"

std::vector<std::string> Utility::GetFileLines(const std::string &filename, unsigned int minLineLength)
{
    std::ifstream file(filename);
    std::vector<std::string> result;
    std::string curLine;
    while(!file.fail())
    {
        std::getline(file, curLine);
        if(!file.fail() && curLine.length() >= minLineLength)
        {
            result.push_back(curLine);
        }
    }
    return result;
}
