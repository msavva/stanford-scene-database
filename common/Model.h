//
// Model.h
//

#include "Mesh.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <map>

class Model
{
public:
    Model(const std::string &directory, const std::string &baseFilename);

    void Render();

private:
    GLuint _displayList;
    std::vector<Mesh*> _meshes;
};