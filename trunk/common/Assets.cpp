//
// Assets.cpp
//

#include "Common.h"

Model* Assets::GetModel(const Parameters &params, const std::string &modelName)
{
    if(_models.find(modelName) != _models.end())
    {
        return _models[modelName];
    }
    Model *result = new Model(params.databaseDirectory + "models/", modelName);
    _models[modelName] = result;
    return result;
}
