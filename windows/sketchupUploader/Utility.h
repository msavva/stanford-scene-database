//
// Utility.h
//

namespace Utility
{
    bool FileExists(const string &filename);
    vector<string> GetFileLines(const string &filename, unsigned int minLineLength);
    
    vector<string> PartitionString(const string &s, const string &separator);
    
    int StringToInt(const string &s);
    float StringToFloat(const string &s);
    vector<int> StringToIntegerList(const string &s, const string &prefix);
    vector<float> StringToFloatList(const string &s, const string &prefix);
};
