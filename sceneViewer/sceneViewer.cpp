//
// SceneViewer.cpp
//

#include "sceneViewer.h"
#include "Mesh.h"

void SceneViewer::Init()
{
    _time = 0.0f;
    _m = new Model("C:\\SceneModeling\\", "exportTest");
}

void SceneViewer::ReSize(int windowWidth, int windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
}

void SceneViewer::Update(float seconds)
{
    _time += seconds;
}

void SceneViewer::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, _windowWidth, _windowHeight);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    float aspectRatio = float(_windowWidth) / float(_windowHeight);
    gluPerspective(80.0f, aspectRatio, 0.1f, 1000.0f);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(_time * 180.0f, 1.0f, 0.0f, 0.0f);

    _m->Render();

    glutSwapBuffers();
}
