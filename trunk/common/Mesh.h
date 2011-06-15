//
// Mesh.h
//

#ifndef __MESH_H
#define __MESH_H

#include <stdlib.h>
#include "glut.h"
#include "Vec3f.h"
#include <vector>

struct MeshVertex
{
    Vec3f position;
    float tx, ty;
};

struct MeshMaterial
{
    MeshMaterial()
    {
        texture = 0;
        diffuseColor = Vec3f(1.0f, 1.0f, 1.0f);
        transparency = 0.0f;
    }
    void Set();
    
    GLuint texture;
    Vec3f diffuseColor;
    float transparency;
};

class Mesh
{
public:
    Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices, const MeshMaterial &material);
    
    void Render() const;

private:
    GLuint _displayList;
    MeshMaterial _material;
};

#endif