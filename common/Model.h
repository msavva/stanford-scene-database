//
// Model.h
//

#include "Common.h"

class Model
{
public:
    Model(const std::string &directory, const std::string &baseFilename);

    void Render();

private:
    GLuint _displayList;
    std::vector<Mesh*> _meshes;
};