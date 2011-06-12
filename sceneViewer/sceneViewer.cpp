//
// SceneViewer.cpp
//

#include "sceneViewer.h"
#include "glut.h"

void SceneViewer::ReSize(int windowWidth, int windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
}

void SceneViewer::Update()
{

}

void SceneViewer::Render()
{
    glClearColor(.1f, .1f, .1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, _windowWidth, _windowHeight);
  
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    float aspectRatio = float(_windowWidth) / float(_windowHeight);
    gluPerspective(60.0f, aspectRatio, 0.1f, 100.0f);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutSwapBuffers();
}
