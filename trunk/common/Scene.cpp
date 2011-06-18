//
// Scene.cpp
//

#include "Common.h"

void Scene::Load(const Parameters &params, const std::string &filename, Assets &assets)
{
    std::string sceneFilename = params.databaseDirectory + "scenes/" + filename + ".txt";
    std::cout << "Loading Scene: " << sceneFilename << '\n';
    auto lines = Utility::GetFileLines(sceneFilename, 2);
    if(lines[0] != "StanfordSceneDatabase" || lines[1] != "version 1.0")
    {
        std::cout << "This is not a valid scene file\n";
        return;
    }

    ModelInstance *activeModelInstance = NULL;
    for(auto lineIterator = lines.begin(); lineIterator != lines.end(); lineIterator++)
    {
        const std::string &curLine = *lineIterator;
        if(curLine.find("modelCount ") == 0)
        {
            const unsigned int modelCount = Utility::StringToIntegerList(curLine, "modelCount ")[0];
            _allModels.resize(modelCount);
            for(unsigned int modelIndex = 0; modelIndex < modelCount; modelIndex++)
            {
                _allModels[modelIndex] = new ModelInstance;
            }
        }
        if(curLine.find("newModel ") == 0)
        {
            auto parts = Utility::PartitionString(curLine, " ");
            int modelIndex = Utility::StringToInt(parts[1]);
            activeModelInstance = _allModels[modelIndex];
            activeModelInstance->_model = assets.GetModel(params, parts[2]);
        }
        if(curLine.find("parentIndex ") == 0)
        {
            int parentIndex = Utility::StringToIntegerList(curLine, "parentIndex ")[0];
            if(parentIndex >= 0)
            {
                activeModelInstance->_parent = _allModels[parentIndex];
            }
        }
        if(curLine.find("children ") == 0)
        {
            auto children = Utility::StringToIntegerList(curLine, "children ");
            for(auto childIterator = children.begin(); childIterator != children.end(); childIterator++)
            {
                activeModelInstance->_children.push_back(_allModels[*childIterator]);
            }
        }
        if(curLine.find("parentContactPosition ") == 0)
        {
            auto v = Utility::StringToFloatList(curLine, "parentContactPosition ");
            activeModelInstance->_parentContactPosition.x = v[0];
            activeModelInstance->_parentContactPosition.y = v[1];
            activeModelInstance->_parentContactPosition.z = v[2];
        }
        if(curLine.find("parentContactNormal ") == 0)
        {
            auto v = Utility::StringToFloatList(curLine, "parentContactNormal ");
            activeModelInstance->_parentContactNormal.x = v[0];
            activeModelInstance->_parentContactNormal.y = v[1];
            activeModelInstance->_parentContactNormal.z = v[2];
        }
        if(curLine.find("parentOffset ") == 0)
        {
            auto v = Utility::StringToFloatList(curLine, "parentOffset ");
            activeModelInstance->_parentOffset.x = v[0];
            activeModelInstance->_parentOffset.y = v[1];
            activeModelInstance->_parentOffset.z = v[2];
        }
        if(curLine.find("transform ") == 0)
        {
            auto transform = Utility::StringToFloatList(curLine, "transform ");
            for(unsigned int elementIndex = 0; elementIndex < 16; elementIndex++)
            {
                activeModelInstance->_transform[0][elementIndex] = transform[elementIndex];
            }
        }
    }

    _root = _allModels[0];
}

void Scene::Render()
{
    _root->Render();
}
