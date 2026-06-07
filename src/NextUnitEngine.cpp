#include <GL/glut.h>

#include "Engine/World.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "NextUnitEngine.hpp"

int main(int argc, const char** argv)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(640, 480);
    glutInit(&argc, (char**)argv);
    glutCreateWindow("Next Unit Engine");

    glutEvent::init();
    glutDraw::init();
    world::reset();

    glutMainLoop();

    return 0;
}
