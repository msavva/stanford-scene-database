//
// SceneViewer.cpp
//

#include "Mesh.h"

void MeshMaterial::Set()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(diffuseColor.x, diffuseColor.y, diffuseColor.z);
}

Mesh::Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices, const MeshMaterial &material)
{
    _displayList = glGenLists(1);
    
    glNewList(_displayList, GL_COMPILE);
    {
        glBegin(GL_TRIANGLES);
        {
            _material.Set();

            for(unsigned int triangleIndex = 0; triangleIndex < indices.size() / 3; triangleIndex++)
            {
                for(unsigned int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
                {
                    const MeshVertex &curVertex = vertices[ indices[triangleIndex * 3 + vertexIndex] ];
                    glTexCoord2f(curVertex.tx, curVertex.ty);
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
