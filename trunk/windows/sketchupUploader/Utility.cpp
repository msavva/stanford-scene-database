//
// Utility.cpp
//

#include "Main.h"

bool Utility::FileExists(const string &filename)
{
    std::ifstream file(filename);
    return (!file.fail());
}

vector<string> Utility::GetFileLines(const string &filename, unsigned int minLineLength)
{
    if(!Utility::FileExists(filename))
    {
        std::cout << "Required file not found: " << filename << '\n';
        exit(1);
    }
    std::ifstream file(filename);
    vector<string> result;
    string curLine;
    while(!file.fail())
    {
        std::getline(file, curLine);
        if(!file.fail() && curLine.length() >= minLineLength)
        {
        	if (curLine.at(curLine.length()-1) == '\r')
        		curLine = curLine.substr(0,curLine.size()-1);
            result.push_back(curLine);
        }
    }
    return result;
}

vector<string> Utility::PartitionString(const string &s, const string &separator)
{
    vector<string> result;
    string curEntry;
    for(unsigned int outerCharacterIndex = 0; outerCharacterIndex < s.length(); outerCharacterIndex++)
    {
        bool isSeperator = true;
        for(unsigned int innerCharacterIndex = 0; innerCharacterIndex < separator.length() && outerCharacterIndex + innerCharacterIndex < s.length() && isSeperator; innerCharacterIndex++)
        {
            if(s[outerCharacterIndex + innerCharacterIndex] != separator[innerCharacterIndex])
            {
                isSeperator = false;
            }
        }

        if(isSeperator)
        {
            if(curEntry.length() > 0)
            {
                result.push_back(curEntry);
                curEntry.clear();
            }
            outerCharacterIndex += separator.length() - 1;
        }
        else
        {
            curEntry.push_back(s[outerCharacterIndex]);
        }
    }
    if(curEntry.length() > 0)
    {
        result.push_back(curEntry);
    }
    return result;
}

int Utility::StringToInt(const string &s)
{
    std::stringstream stream(std::stringstream::in | std::stringstream::out);
    stream << s;
    
    int result;
    stream >> result;
    return result;
}

float Utility::StringToFloat(const string &s)
{
    std::stringstream stream(std::stringstream::in | std::stringstream::out);
    stream << s;

    float result;
    stream >> result;
    return result;
}

vector<int> Utility::StringToIntegerList(const string &s, const string &prefix)
{
    string subString = Utility::PartitionString(s, prefix)[0];
    auto parts = Utility::PartitionString(subString, " ");

    vector<int> result(parts.size());
    for(unsigned int resultIndex = 0; resultIndex < result.size(); resultIndex++)
    {
        result[resultIndex] = Utility::StringToInt(parts[resultIndex]);
    }
    return result;
}

vector<float> Utility::StringToFloatList(const string &s, const string &prefix)
{
    string subString = Utility::PartitionString(s, prefix)[0];
    auto parts = Utility::PartitionString(subString, " ");

    vector<float> result(parts.size());
    for(unsigned int resultIndex = 0; resultIndex < result.size(); resultIndex++)
    {
        result[resultIndex] = Utility::StringToFloat(parts[resultIndex]);
    }
    return result;
}
