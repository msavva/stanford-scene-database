//
// SceneViewer.cpp
//

#include "Common.h"

void MeshMaterial::Set() const
{
    if(texture == 0)
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

Mesh::Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices, const MeshMaterial &material)
{
    _displayList = glGenLists(1);
    
    glNewList(_displayList, GL_COMPILE);
    {
        material.Set();

        glBegin(GL_TRIANGLES);
        {
            for(unsigned int triangleIndex = 0; triangleIndex < indices.size() / 3; triangleIndex++)
            {
                for(unsigned int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
                {
                    const MeshVertex &curVertex = vertices[ indices[triangleIndex * 3 + vertexIndex] ];
                    glTexCoord2f(curVertex.tx, curVertex.ty);
                    glColor3f(material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z);
                    glVertex3f(curVertex.position.x, curVertex.position.y, curVertex.position.z);
                }
            }
        }
        glEnd();
    }
    glEndList();
}

void Mesh::Render() const
{
    glCallList(_displayList);
}
