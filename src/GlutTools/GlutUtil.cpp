#include <iostream>

#include <GL/glut.h>

#include "GlutTools/GlutUtil.hpp"

namespace glutUtil
{
    void drawCoordinateSystem(double scale = 1.0)
    {
        GLdouble coordinateSystemVertex[][3] = {
            {0.0, 0.0, 0.0},
            {scale, 0.0, 0.0},
            {0.0, scale, 0.0},
            {0.0, 0.0, scale}
        };

        glBegin(GL_LINES);

        glColor3d(1.0, 0.0, 0.0);
        glVertex3dv(coordinateSystemVertex[0]);
        glVertex3dv(coordinateSystemVertex[1]);

        glColor3d(0.0, 1.0, 0.0);
        glVertex3dv(coordinateSystemVertex[0]);
        glVertex3dv(coordinateSystemVertex[2]);

        glColor3d(0.0, 0.0, 1.0);
        glVertex3dv(coordinateSystemVertex[0]);
        glVertex3dv(coordinateSystemVertex[3]);

        glEnd();

        glColor3d(0.5, 0.5, 0.5);
        glRasterPos3dv(coordinateSystemVertex[0]);
        drawString("O");

        glColor3d(1.0, 0.0, 0.0);
        glRasterPos3dv(coordinateSystemVertex[1]);
        drawString("X");

        glColor3d(0.0, 1.0, 0.0);
        glRasterPos3dv(coordinateSystemVertex[2]);
        drawString("Y");

        glColor3d(0.0, 0.0, 1.0);
        glRasterPos3dv(coordinateSystemVertex[3]);
        drawString("Z");
    }

    void drawSampleCube(double scale = 1.0)
    {
        //      3----[2]----2
        //     /|          /|
        //   [B]|        [A]|
        //   / [3]       / [1]
        //  7----[6]----6   |
        //  |   |       |   |
        //  |   0----[0]|---1
        // [7] /       [5] /
        //  |[8]        |[9]
        //  |/          |/
        //  4----[4]----5

        double shift = -scale / 2;

        GLdouble sampleCubeVertex[][3] = {
            {shift, shift, shift},
            {scale + shift, shift, shift},
            {scale + shift, scale + shift, shift},
            {shift, scale + shift, shift},
            {shift, shift, scale + shift},
            {scale + shift, shift, scale + shift},
            {scale + shift, scale + shift, scale + shift},
            {shift, scale + shift, scale + shift}
        };

        static int sampleCubeEdge[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
                                          {4, 5}, {5, 6}, {6, 7}, {7, 4},
                                          {0, 4}, {1, 5}, {2, 6}, {3, 7}};

        static int sampleCubeFace[][4] = {{1, 0, 3, 2}, {4, 5, 6, 7},
                                          {0, 1, 5, 4}, {7, 6, 2, 3},
                                          {0, 4, 7, 3}, {5, 1, 2, 6}};

        static GLdouble sampleCubeColor[][3] = {
            {0.0, 0.0, 0.3}, {0.0, 0.0, 1.0}, {0.0, 0.3, 0.0},
            {0.0, 1.0, 0.0}, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.0}
        };

        glBegin(GL_QUADS);

        for (int i = 0; i < 6; i++)
        {
            glColor3dv(sampleCubeColor[i]);

            for (int j = 0; j < 4; j++)
            {
                glVertex3dv(sampleCubeVertex[sampleCubeFace[i][j]]);
            }
        }

        glEnd();

        glColor3d(1.0, 1.0, 1.0);
        glBegin(GL_LINES);

        for (int i = 0; i < 12; ++i)
        {
            glVertex3dv(sampleCubeVertex[sampleCubeEdge[i][0]]);
            glVertex3dv(sampleCubeVertex[sampleCubeEdge[i][1]]);
        }

        glEnd();
    }

    void drawGridGround(int x, int z, double scale = 1.0)
    {
        static GLdouble gridGroundVertex[][3] = {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        };

        glColor3d(0.5, 0.5, 0.5);
        glBegin(GL_LINES);

        double shiftX = (double)x * scale / 2.0;
        double shiftZ = (double)z * scale / 2.0;

        gridGroundVertex[0][2] = -shiftZ;
        gridGroundVertex[1][2] = (double)z * scale - shiftZ;

        for (int i = 0; i <= x; ++i)
        {
            gridGroundVertex[0][0] = gridGroundVertex[1][0] =
                (double)i * scale - shiftX;

            glVertex3dv(gridGroundVertex[0]);
            glVertex3dv(gridGroundVertex[1]);
        }

        gridGroundVertex[0][0] = -shiftX;
        gridGroundVertex[1][0] = (double)x * scale - shiftX;

        for (int i = 0; i <= z; ++i)
        {
            gridGroundVertex[0][2] = gridGroundVertex[1][2] =
                (double)i * scale - shiftZ;

            glVertex3dv(gridGroundVertex[0]);
            glVertex3dv(gridGroundVertex[1]);
        }

        glEnd();
    }

    void drawString(const char* text)
    {
        while (*text)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text++);
    }

    void drawString(const std::string& text)
    {
        for (int i = 0; i < text.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
