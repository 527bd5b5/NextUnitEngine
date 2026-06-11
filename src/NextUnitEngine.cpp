#include <iostream>

#include <GL/glut.h>

#include "Engine/WorldReader.hpp"
#include "Engine/WorldRunner.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "NextUnitEngine.hpp"
#include "Utils/String.hpp"

int main(int argc, const char** argv)
{
    if (argc < 2)
        util::printErrorLine("NUE file not specified.", 1);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(640, 480);
    glutInit(&argc, (char**)argv);
    glutCreateWindow("Next Unit Engine");

    glutEvent::init();
    glutDraw::init();
    worldReader::readNueFile(argv[1]);
    worldRunner::reset();

    glutMainLoop();

    return 0;
}
