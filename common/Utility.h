//
// Utility.h
//

#include <vector>
#include <string>
#include <fstream>

namespace Utility
{
    std::vector<std::string> GetFileLines(const std::string &filename, unsigned int minLineLength);
};