#include <iostream>
#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions

using namespace std;

#define ESC 27

//----------------------------------------------------------------------
// Global variables
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera position. The values (lx, ly)
// point in the direction the camera is looking. The variables angle and
// deltaAngle control the camera's angle. The variable deltaMove
// indicates the amount of incremental motion for the camera with each
// redraw cycle. The variables isDragging and xDragStart are used to
// monitor the mouse when it drags (with the left button down).
//----------------------------------------------------------------------

// Camera position
float x = 0.0, y = -5.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

GLUquadricObj* quadratic{ nullptr };        //sphere


// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

float Blue[3] = { 0.0, 0.0, 1.0 };
float Yellow[3] = { 1.0, 1.0, 0.0 };
float Green[3] = { 0.0, 1.0, 0.0 };
float Red[3] = { 1.0, 0.0, 0.0 };
float Pink[3] = { 1.0, 0.75, 0.8 };
float Gold[3] = { 0.83, 0.686274, 0.215686 };
float Silver[3] = { 0.75294117647, 0.75294117647, 0.75294117647 };
//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100000.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


void drawMaze()
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Blue);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Blue);
    //Draw body (a 20x20 spherical mesh of radius 0.75 at height 0.75)

    glColor3f(0.0, 1.0, 0.0); // set drawing color to white
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.75);
    glutSolidSphere(0.75, 20, 20);
    glPopMatrix();
}

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update(void)
{
    if (deltaMove) { // update camera position
        x += deltaMove * lx * 0.1;
        y += deltaMove * ly * 0.1;
    }
    glutPostRedisplay(); // redisplay everything
}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We first update the camera location based on its distance from the
// origin and its direction.
//----------------------------------------------------------------------
void renderScene(void)
{
    int i, j;

    // Clear color and depth buffers
    glClearColor(1.0, 0.0, 1.0, 0.0); // background is pink
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();


    gluLookAt(90.0, -90.0, 200.0, 90.0, 100.0, 0.0, 0.0, 0.0, 1.0);

    // Draw the pacman 
    //////////////////////////////////////////////
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Yellow);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Yellow);


    glPushMatrix();                 //the top ri
    glTranslatef(25.0, 70.0, 5.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glutSolidSphere(10.0, 20.0, 20.0); // head sphere
    glPopMatrix();

    //Draw the ghosts
    ////////////////////////////////////////////////////////



    glPushMatrix();
    glTranslatef(90.0, 60.0, 7.0); // position head
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(10.0, 20.0, 20.0); // head sphere
    glPopMatrix();

    // // Draw Eyes (two small black spheres)
    // glColor3f(1.0, 0.0, 2.0); // eyes are black
    // glPushMatrix();
    // glTranslatef(70.0, 70.0, 7.0); // lift eyes to final position
    // glPushMatrix();
    // glTranslatef(79.95, 80.0, 7.0);
    // glutSolidSphere(0.05, 10, 10); // right eye
    // glPopMatrix();
    // glPushMatrix();
    // glTranslatef(80.05, 90.0, 7.0);
    // glutSolidSphere(0.05, 10, 10); // left eye
    // glPopMatrix();
    // glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, Blue);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Blue);

    // the walls of the maze
    //////////////////////////////////////////////////////////
    glPushMatrix();                 //the bottom right side the maze
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic, 3.0f, 3.0f, 50.0f, 32, 32);
    glPopMatrix();

    // glPushMatrix();                 //the top right side the maze 
    // glTranslatef(90.0, 0.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 3.0f, 3.0f, 50.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //the top right side the maze 
    // glTranslatef(0.0, 200.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 3.0f, 3.0f, 50.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //the bottom left side the maze 
    // glTranslatef(110.0, 200.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 3.0f, 3.0f, 70.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //the bottom of the maze
    // glTranslatef(0.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 3.0f, 3.0f, 200.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //the top wall of the maze
    // glTranslatef(180.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 3.0f, 3.0f, 200.0f, 32, 32);
    // glPopMatrix();

    // //the bottom right side of the maze
    // /////////////////////////////////////////////////////////////////////
    // glPushMatrix();                 //one pice (1)
    // glTranslatef(30.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //5 pices (2)
    // glTranslatef(10.0, 10.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 50.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //one pice (3)
    // glTranslatef(40.0, 10.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (4)
    // glTranslatef(20.0, 20.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices on the wall (5)
    // glTranslatef(50.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //one pice near to the two pices on the wall (6)
    // glTranslatef(50.0, 20.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices on the wall (7)
    // glTranslatef(70.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 // (11) pice on the 5 pices cylinder to adjest it I changed it to 35 units far from the wall
    // glTranslatef(10.0, 40.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (12) 
    // glTranslatef(10.0, 70.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //4 pices (13)
    // glTranslatef(20.0, 50.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 40.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //2 pices (14)
    // glTranslatef(30.0, 70.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //4 pices (15)
    // glTranslatef(50.0, 50.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 40.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //2 pices (16)
    // glTranslatef(50.0, 40.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //2 pices (17)
    // glTranslatef(40.0, 40.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // //the bottom left of the maze
    // //////////////////////////////////////////////////////////

    // glPushMatrix();                 //5 pices (18)
    // glTranslatef(10.0, 110.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 50.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (19)
    // glTranslatef(10.0, 130.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (20)
    // glTranslatef(30.0, 190.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //2 pices (21)
    // glTranslatef(20.0, 180.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (22)
    // glTranslatef(40.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //2 pices (23)
    // glTranslatef(40.0, 140.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (24)
    // glTranslatef(50.0, 170.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices on the wall (25)
    // glTranslatef(50.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices near to the two pices on the wall (26)
    // glTranslatef(50.0, 180.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices on the wall (27)
    // glTranslatef(70.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // //the top right of the maze
    // //////////////////////////////////////////////////////////
    // glPushMatrix();                 //two pices on the wall (8)
    // glTranslatef(90.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //one pice near to the two pices on the wall (9)
    // glTranslatef(90.0, 20.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices on the wall (10)
    // glTranslatef(110.0, 0.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //3 pices (45)
    // glTranslatef(90.0, 30.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 30.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (50)
    // glTranslatef(110.0, 30.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (51)
    // glTranslatef(160.0, 30.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (52)
    // glTranslatef(170.0, 30.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (53)
    // glTranslatef(160.0, 30.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (54)
    // glTranslatef(160.0, 50.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();


    // glPushMatrix();                 //1 pice (55)
    // glTranslatef(160.0, 10.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (56)
    // glTranslatef(170.0, 10.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (57)
    // glTranslatef(160.0, 10.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (58)
    // glTranslatef(160.0, 20.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (59)
    // glTranslatef(150.0, 10.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // //the top left of the maze
    // //////////////////////////////////////////////////////////
    // glPushMatrix();                 //two pices on the wall (28)
    // glTranslatef(90.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (29)
    // glTranslatef(90.0, 180.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices on the wall (30)
    // glTranslatef(110.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (35)
    // glTranslatef(150.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (36)
    // glTranslatef(160.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (37)
    // glTranslatef(170.0, 180.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (38)
    // glTranslatef(160.0, 180.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (39)
    // glTranslatef(160.0, 190.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (40)
    // glTranslatef(160.0, 150.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (41)
    // glTranslatef(170.0, 150.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (42)
    // glTranslatef(160.0, 150.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (43)
    // glTranslatef(160.0, 170.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //2 pice (44)
    // glTranslatef(160.0, 100.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //3 pices (45)
    // glTranslatef(90.0, 170.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 30.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //two pices (46)
    // glTranslatef(110.0, 150.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //4 pices (47)
    // glTranslatef(150.0, 120.0, 0.0);
    // glRotatef(-90.0, 1.0, 0.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 40.0f, 32, 32);
    // glPopMatrix();

    // glPushMatrix();                 //1 pice (48)
    // glTranslatef(140.0, 140.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // gluCylinder(quadratic, 2.0f, 2.0f, 10.0f, 32, 32);
    // glPopMatrix();



    //the center of the maze
    ///////////////////////////////////////////
    glPushMatrix();                 //4 pices (31)
    glTranslatef(70.0, 50.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic, 2.0f, 2.0f, 40.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();                 //4 pices (32)
    glTranslatef(90.0, 50.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic, 2.0f, 2.0f, 40.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();                 //1 pice (33)
    glTranslatef(70.0, 50.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();                 //1 pice (34)
    glTranslatef(70.0, 90.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic, 2.0f, 2.0f, 20.0f, 32, 32);
    glPopMatrix();

    //void gluCylinder(GLUquadric * quad,
    //    GLdouble base,
    //    GLdouble top,
    //    GLdouble height,
    //    GLint slices,
    //    GLint stacks);


    //// Draw 36 snow men
    //for (i = -3; i < 3; i++)
    //{
    //    for (j = -3; j < 3; j++)
    //    {
    //        glPushMatrix();
    //        glTranslatef(i * 7.5, j * 7.5, 0);
    //        drawSnowman();
    //        glPopMatrix();
    //    }
    //}
    glutSwapBuffers(); // Make it all visible
}

//----------------------------------------------------------------------
// User-input callbacks
//
// processNormalKeys: ESC, q, and Q cause program to exit
// pressSpecialKey: Up arrow = forward motion, down arrow = backwards
// releaseSpecialKey: Set incremental motion to zero
//----------------------------------------------------------------------
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
    printf("\n\
-----------------------------------------------------------------------\n\
  OpenGL Sample Program:\n\
  - Drag mouse left-right to rotate camera\n\
  - Hold up-arrow/down-arrow to move camera forward/backward\n\
  - q or ESC to quit\n\
-----------------------------------------------------------------------\n");

    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Pacman");

    // register callbacks
    glutReshapeFunc(changeSize); // window reshape callback
    glutDisplayFunc(renderScene); // (re)display callback
    glutIdleFunc(update); // incremental update
    glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
    glutMouseFunc(mouseButton); // process mouse button push/release
    glutMotionFunc(mouseMove); // process mouse dragging motion
    glutKeyboardFunc(processNormalKeys); // process standard key clicks
    glutSpecialFunc(pressSpecialKey); // process special key pressed
                        // Warning: Nonstandard function! Delete if desired.
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