//
// SceneViewer.h
//

class SceneViewer
{
public:
    void ReSize(int windowWidth, int windowHeight);
    void Update();
    void Render();

private:
    int _windowWidth, _windowHeight;
};