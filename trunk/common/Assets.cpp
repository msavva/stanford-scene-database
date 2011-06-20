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
    Model *result = new Model(params.databaseDirectory + "models/", modelName, *this);
    _models[modelName] = result;
    return result;
}

GLuint Assets::GetTexture(const std::string &filename)
{
    if(_textures.find(filename) != _textures.end())
    {
        return _textures[filename];
    }
    GLuint result = Utility::MakeOpenGLBitmap(filename);
    _textures[filename] = result;
    return result;
}
