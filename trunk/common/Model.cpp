//
// Model.cpp
//

#include "Common.h"

Model::Model(const std::string &directory, const std::string &baseFilename)
{
    std::cout << "  Loading model: " << baseFilename << '\n';
    //
    // Note that this obj loader is not designed to function on all possible obj files, and does not handle improperly formatted files correctly
    //

    std::vector<std::string> objLines = Utility::GetFileLines(directory + baseFilename + std::string(".obj"), 3);
    std::vector<std::string> mtlLines = Utility::GetFileLines(directory + baseFilename + std::string(".mtl"), 3);

    //
    // Load materials
    //
    std::map<std::string, MeshMaterial> materials;
    MeshMaterial *activeMaterial = NULL;
    for(unsigned int lineIndex = 0; lineIndex < mtlLines.size(); lineIndex++)
    {
        const std::string &curLine = mtlLines[lineIndex];
        if(curLine.find("newmtl ") == 0)
        {
            const std::string materialName = curLine.substr(7);
            materials[materialName] = MeshMaterial();
            activeMaterial = &materials[materialName];
        }
        if(curLine[0] == 'K' && curLine[1] == 'd')
        {
            std::stringstream stream(std::stringstream::in | std::stringstream::out);
            stream << curLine.substr(3);
            stream >> activeMaterial->diffuseColor.x >> activeMaterial->diffuseColor.y >> activeMaterial->diffuseColor.z;
        }
        if(curLine[0] == 'd' && curLine[1] == ' ')
        {
            std::stringstream stream(std::stringstream::in | std::stringstream::out);
            stream << curLine.substr(3);
            stream >> activeMaterial->transparency;
        }
        if(curLine.find("map_Kd ") == 0)
        {
            const std::string textureName = curLine.substr(7);
            
            //
            // Load the texture
            //
            activeMaterial->texture = Utility::MakeOpenGLBitmap(directory + textureName);
        }
    }

    //
    // Load meshes
    //
    std::vector<MeshVertex> vertices;
    std::vector<unsigned int> indices;
    activeMaterial = NULL;
    for(unsigned int lineIndex = 0; lineIndex < objLines.size(); lineIndex++)
    {
        const std::string &curLine = objLines[lineIndex];
        if(curLine[0] == 'v' && curLine[1] == ' ')
        {
            vertices.push_back(MeshVertex());
            MeshVertex &curVertex = vertices[vertices.size() - 1];

            std::stringstream stream(std::stringstream::in | std::stringstream::out);
            stream << curLine.substr(2);
            stream >> curVertex.position.x >> curVertex.position.y >> curVertex.position.z;

            if(vertices.size() == 1)
            {
                _boundingBoxMin = curVertex.position;
                _boundingBoxMax = curVertex.position;
            }
            else
            {
                _boundingBoxMin = Vec3f::Minimize(_boundingBoxMin, curVertex.position);
                _boundingBoxMax = Vec3f::Maximize(_boundingBoxMax, curVertex.position);
            }
        }
        if(curLine[0] == 'v' && curLine[1] == 't')
        {
            MeshVertex &curVertex = vertices[vertices.size() - 1];

            std::stringstream stream(std::stringstream::in | std::stringstream::out);
            stream << curLine.substr(3);
            stream >> curVertex.tx >> curVertex.ty;
        }
        if(curLine[0] == 'f' && curLine[1] == ' ')
        {
            std::stringstream stream(std::stringstream::in | std::stringstream::out);

            unsigned int index0, index1, index2;
            if(curLine.find('/') == std::string::npos)
            {
                stream << curLine.substr(2);
                stream >> index0 >> index1 >> index2;
            }
            else
            {
                std::string curLineCopy = curLine.substr(2);
                for(unsigned int charIndex = 0; charIndex < curLineCopy.size(); charIndex++)
                {
                    if(curLineCopy[charIndex] == '/')
                    {
                        curLineCopy[charIndex] = ' ';
                    }
                }
                stream << curLineCopy;
                unsigned int temp0, temp1, temp2;
                stream >> index0 >> temp0 >> index1 >> temp1 >> index2 >> temp2;
            }
            indices.push_back(index0 - 1);
            indices.push_back(index1 - 1);
            indices.push_back(index2 - 1);
        }
        if(curLine.find("usemtl ") == 0)
        {
            if(indices.size() > 0)
            {
                _meshes.push_back(new Mesh(vertices, indices, *activeMaterial));
                indices.clear();
            }
            const std::string materialName = curLine.substr(7);
            activeMaterial = &materials[materialName];
        }
    }

    if(indices.size() > 0)
    {
        _meshes.push_back(new Mesh(vertices, indices, *activeMaterial));
        indices.clear();
    }

    //
    // Compile meshes
    //
    _displayList = glGenLists(1);
    
    glNewList(_displayList, GL_COMPILE);
    {
        for(unsigned int meshIndex = 0; meshIndex < _meshes.size(); meshIndex++)
        {
            _meshes[meshIndex]->Render();
        }
    }
    glEndList();
}

void Model::Render()
{
    glCallList(_displayList);
}
