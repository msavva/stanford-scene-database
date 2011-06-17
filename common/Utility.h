//
// Utility.h
//

#include "Common.h"

namespace Utility
{
    std::vector<std::string> GetFileLines(const std::string &filename, unsigned int minLineLength);

    void ExecuteCommand(const char *command);
    GLuint MakeOpenGLBitmap(const std::string &filename);
};