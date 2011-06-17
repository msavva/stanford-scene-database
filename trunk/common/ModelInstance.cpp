//
// ModelInstance.cpp
//

#include "Common.h"

void ModelInstance::Render()
{
    glPushMatrix();
    glMultMatrixf(_transform[0]);
    _model->Render();
    glPopMatrix();

    for(auto childIterator = _children.begin(); childIterator != _children.end(); childIterator++)
    {
        (*childIterator)->Render();
    }
}
