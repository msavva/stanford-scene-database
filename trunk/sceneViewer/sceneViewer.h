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
    void ReSize(int windowWidth, int windowHeight);

private:
    int _windowWidth, _windowHeight;

    Scene _scene;
    Camera _camera;
    Model *_m;
    float _time;
};