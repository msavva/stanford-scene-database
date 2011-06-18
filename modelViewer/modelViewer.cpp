//
// ModelViewer.cpp
//

#include "Common.h"
#include "modelViewer.h"

void ModelViewer::Init()
{
    _params.Init("parameters.txt");

    std::cout << "Usage: Modify parameters.txt to change which scene is loaded\n";

    _camera.Reset(Vec3f(100.0f, 100.0f, 100.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 0.0f, 0.0f));

    _database.Init(_params);
    _activeModel = _assets.GetModel(_params, _database.Entries().begin()->first);

    std::cout << "\n[W/A/S/D/R/F]: Translate camera\n";
    std::cout << "[2/4/6/8]: Look around\n";
    std::cout << "[Left mouse drag]: Look around\n";
    std::cout << "[Right mouse drag]: Pan camera\n";
    
}

void ModelViewer::ReSize(int windowWidth, int windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
}

void ModelViewer::Update(float seconds)
{
    
}

void ModelViewer::MouseDown(int button, int x, int y)
{
    _mouseButton = button;
    _mouseX = x;
    _mouseY = y;
}

void ModelViewer::MouseMove(int x, int y)
{
    const float angleScale = 0.02f;
    const float moveScale = 1.0f;

    const int mouseDiffX = x - _mouseX;
    const int mouseDiffY = y - _mouseY;

    _mouseX = x;
    _mouseY = y;

    if(_mouseButton == GLUT_LEFT_BUTTON)
    {
        _camera.LookRight(-angleScale * mouseDiffX);
        _camera.LookUp(angleScale * mouseDiffY);
    }
    if(_mouseButton == GLUT_RIGHT_BUTTON)
    {
        _camera.Strafe(-moveScale * mouseDiffX);
        _camera.Jump(-moveScale * mouseDiffY);
    }
}

void ModelViewer::KeyPress(unsigned char key)
{
    const float moveDistance = 15.0f;
    const float angleDistance = 0.15f;

    switch(key)
    {
    case 'w':
        _camera.Move(-moveDistance);
        break;
    case 's':
        _camera.Move(moveDistance);
        break;
    case 'a':
        _camera.Strafe(moveDistance);
        break;
    case 'd':
        _camera.Strafe(-moveDistance);
        break;
    case 'r':
        _camera.Jump(moveDistance);
        break;
    case 'f':
        _camera.Jump(-moveDistance);
        break;
    case '2':
        _camera.LookUp(angleDistance);
        break;
    case '8':
        _camera.LookUp(-angleDistance);
        break;
    case '4':
        _camera.LookRight(angleDistance);
        break;
    case '6':
        _camera.LookRight(-angleDistance);
        break;
    default:
        //std::cout << key << ' ' << int(key) << std::endl;
        break;
    }
}

void ModelViewer::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, _windowWidth, _windowHeight);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    float aspectRatio = float(_windowWidth) / float(_windowHeight);
    gluPerspective(60.0f, aspectRatio, 0.1f, 1000.0f);
  
    glMatrixMode(GL_MODELVIEW);
    _camera.Update();
    glLoadMatrixf(_camera.Matrix()[0]);

    _activeModel->Render();

    glutSwapBuffers();
}

void ModelViewer::WriteModelInfo()
{
    const ModelEntry &curEntry = _database.GetEntry(_activeModel->Hash());
    std::cout << "Model Hash: " << curEntry.hash << '\n';
    std::cout << "Name: " << curEntry.name << '\n';
    std::cout << "Tags:\n";
    for(auto tagIterator = curEntry.tags.begin(); tagIterator != curEntry.tags.end(); tagIterator++)
    {
        std::cout << *tagIterator << '\n';
    }
}
