//
// ModelViewer.h
//

#include "Common.h"

class ModelViewer
{
public:
    void Init();
    
    void Update(float seconds);
    void Render();

    void ASCIIKeyPress(unsigned char key);
    void SpecialKeyPress(int key);

    void MouseDown(int button, int x, int y);
    void MouseMove(int x, int y);
    
    void ReSize(int windowWidth, int windowHeight);

private:
    void WriteModelInfo();

    int _windowWidth, _windowHeight;

    Parameters _params;
    Assets _assets;
    Camera _camera;
    ModelDatabase _database;

    std::vector<const ModelEntry*> _modelList;

    Model *_activeModel;
    int _activeModelIndex;

    int _mouseButton, _mouseX, _mouseY;
};