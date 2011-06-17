//
// main.cpp
//

#include "Common.h"

#include "sceneViewer.h"

static SceneViewer* g_Viewer = NULL;

static const float framesPerSecond = 60.0f;
static const int windowWidth = 1024;
static const int windowHeight = 768;

void TimerTickCallback(int value)
{
    g_Viewer->Update(1.0f / framesPerSecond);

    glutPostRedisplay();

    glutTimerFunc( (int)(1000.0f / framesPerSecond), TimerTickCallback, 0);
}

void DisplayCallback()
{
    g_Viewer->Render();
}

void KeyboardCallback(unsigned char key, int x, int y)
{
    g_Viewer->KeyPress(key);
}

void ReshapeCallback(int w, int h)
{
    g_Viewer->ReSize(w, h);
}

void MouseCallback(int button, int state, int x, int y)
{
    /*if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)
    {
        gMouseButton = button;
    }
    else
    {
        gMouseButton = -1;
    }

    if (state == GLUT_UP)
    {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }*/
}

void MouseMotionCallback(int x, int y)
{

}

int main(int argc, char** argv)
{
    std::cout << "Scene Viewer\n";

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Stanford Scene Database Viewer");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(DisplayCallback);
    glutKeyboardFunc(KeyboardCallback);
    glutReshapeFunc(ReshapeCallback);
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotionCallback);

    g_Viewer = new SceneViewer;
    g_Viewer->Init();
    g_Viewer->ReSize(windowWidth, windowHeight);

    glutTimerFunc( 16, TimerTickCallback, 0);

    glutMainLoop();

    return 0;
}
