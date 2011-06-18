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

    void KeyPress(unsigned char key);

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

    Model *_activeModel;

    int _mouseButton, _mouseX, _mouseY;
};