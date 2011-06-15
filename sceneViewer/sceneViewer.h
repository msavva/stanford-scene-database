//
// SceneViewer.h
//

#include "Model.h"

class SceneViewer
{
public:
    void Init();
    void ReSize(int windowWidth, int windowHeight);
    void Update(float seconds);
    void Render();

private:
    int _windowWidth, _windowHeight;

    Model *_m;
    float _time;
};