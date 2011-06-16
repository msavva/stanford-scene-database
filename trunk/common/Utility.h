//
// Utility.h
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "glut.h"

namespace Utility
{
    std::vector<std::string> GetFileLines(const std::string &filename, unsigned int minLineLength);

    void ExecuteCommand(const char *command);
    GLuint MakeOpenGLBitmap(const std::string &filename);
};