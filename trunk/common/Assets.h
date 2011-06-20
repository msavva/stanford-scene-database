//
// Assets.h
//

#include "Common.h"

class Assets
{
public:
    Model* GetModel(const Parameters &params, const std::string &modelName);
    GLuint GetTexture(const std::string &textureFilename);

private:
    std::map<std::string, Model*> _models;
    std::map<std::string, GLuint> _textures;
};