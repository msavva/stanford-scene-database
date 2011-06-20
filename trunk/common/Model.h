//
// Model.h
//

#include "Common.h"

class Assets;
class Model
{
public:
    Model(const std::string &directory, const std::string &baseFilename, Assets &textureStore);

    void Render();

    //
    // Accessors
    //
    inline const Vec3f& BoundingBoxMin()
    {
        return _boundingBoxMin;
    }
    inline const Vec3f& BoundingBoxMax()
    {
        return _boundingBoxMax;
    }
    inline const std::string& Hash()
    {
        return _hash;
    }

private:
    GLuint _displayList;

    std::vector<Mesh*> _meshes;
    
    std::string _hash;
    
    Vec3f _boundingBoxMin, _boundingBoxMax;
};
