#include <iostream>
#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include "ECE_Board.h"
#include "ECE_Ghost.h"
#include "ECE_pacman.h"



// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts


// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Camera position
float camX = 0.0, camY = -5.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == ESC || key == 'q' || key == 'Q')
    {
        exit(0);
    }
}

void pressSpecialKey(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_UP: deltaMove = 1.0; break;
    case GLUT_KEY_DOWN: deltaMove = -1.0; break;
    }
}

void releaseSpecialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: deltaMove = 0.0; break;
    case GLUT_KEY_DOWN: deltaMove = 0.0; break;
    }
}

//----------------------------------------------------------------------
// Process mouse drag events
//
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void mouseMove(int x, int y)
{
    if (isDragging)
    { // only when dragging
        // update the change in angle
        deltaAngle = (x - xDragStart) * 0.005;

        // camera's direction is set to angle + deltaAngle
        lx = -sin(angle + deltaAngle);
        ly = cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        { // left mouse button pressed
            isDragging = 1; // start dragging
            xDragStart = x; // save x where button first pressed
        }
        else
        { /* (state = GLUT_UP) */
            angle += deltaAngle; // update camera turning angle
            isDragging = 0; // no longer dragging
        }
    }
}

int main(int argc, char** argv)
{
    printf
        ("\n\n\n\
-----------------------------------------------------------------------\n\
  OpenGL Sample Program:\n\
  - Press Ctrl + c to quit \n\n\n\n\
  - Press R to rotate\n\
-----------------------------------------------------------------------\n"
        );

    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Pacman");

    // register callbacks
    glutReshapeFunc(changeSize); // window reshape callback
    glutDisplayFunc(renderScene); // (re)display callback
    glutSpecialUpFunc(releaseSpecialKey); // process special key release

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    if (!quadratic)
        quadratic = gluNewQuadric();


    // enter GLUT event processing cycle
    glutMainLoop();

    return 0; // this is just to keep the compiler happy
}