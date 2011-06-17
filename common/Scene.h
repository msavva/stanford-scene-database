//
// Scene.h
//

#include "Common.h"

class Scene
{
public:
    void Load(const std::string &filename);
    void Render();

private:
    ModelInstance *_root;
};