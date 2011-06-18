//
// Model.h
//

#include "Common.h"

class Model
{
public:
    Model(const std::string &directory, const std::string &baseFilename);

    void Render();

    //
    // Accessors
    //
    inline const Vec3f& boundingBoxMin()
    {
        return _boundingBoxMin;
    }
    inline const Vec3f& boundingBoxMax()
    {
        return _boundingBoxMax;
    }

private:
    GLuint _displayList;
    std::vector<Mesh*> _meshes;
    Vec3f _boundingBoxMin, _boundingBoxMax;
};
