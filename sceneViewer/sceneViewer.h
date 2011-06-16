//
// SceneViewer.h
//

#include "Model.h"
#include "Camera.h"

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

    Camera _camera;
    Model *_m;
    float _time;
};