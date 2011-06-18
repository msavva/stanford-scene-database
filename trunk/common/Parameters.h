//
// Parameters.h
//

#include "Common.h"

struct Parameters
{
    void Init(const std::string &filename);

    std::string databaseDirectory;
    std::string defaultScene;

    std::string textQuery;
};