//
// ModelInstance.h
//

#include "Common.h"

class ModelInstance
{
public:
    ModelInstance(Model *model, const Matrix4 &transform)
    {
        _model = model;
        _transform = transform;
    }
    void AddChild(ModelInstance *child)
    {
        _children.push_back(child);
    }
    void Render();

private:
    Model *_model;
    Matrix4 _transform;
    std::vector<ModelInstance*> _children;
};
