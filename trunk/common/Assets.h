//
// Assets.h
//

#include "Common.h"

class Assets
{
public:
    Model* GetModel(const Parameters &params, const std::string &modelName);

private:
    std::map<std::string, Model*> _models;
};