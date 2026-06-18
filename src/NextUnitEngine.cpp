#include <GL/glut.h>

#include "Engine/WorldReader.hpp"
#include "Engine/WorldRunner.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "NextUnitEngine.hpp"
#include "Option.hpp"

int frameWidth = 640;
int frameHeight = 480;
int framePositionX = 10;
int framePositionY = 10;

int main(int argc, const char** argv)
{
    option::set(argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(framePositionX, framePositionY);
    glutInitWindowSize(frameWidth, frameHeight);
    glutInit(&argc, (char**)argv);
    glutCreateWindow("Next Unit Engine");

    glutEvent::init();
    glutDraw::init();
    worldReader::readNueFile();
    worldRunner::reset();

    glutMainLoop();

    return 0;
}
