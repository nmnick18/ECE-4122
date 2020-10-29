#pragma once
#include "ECE_Ghost.h"


extern GLUquadricObj* quadratic;

void ECE_ghost::Draw_Ghost(int r, int g, int b)
{

    glPushMatrix();
    glTranslatef(112, 0, 4.7);
    glTranslatef(0, 135, 4.7);
    glutSolidSphere(5.0, 20.0, 20.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(112, 0, 0);
    glTranslatef(0, 135, 0);
    gluCylinder(quadratic, 5.0f, 5.0f, 8.0f, 32, 32);
    glPopMatrix();

}



