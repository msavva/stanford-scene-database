//
// SceneViewer.h
//

#include "Common.h"

class SceneViewer
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
    int _windowWidth, _windowHeight;

    Parameters _params;
    Assets _assets;
    Scene _scene;
    Camera _camera;

    int _mouseButton, _mouseX, _mouseY;
};