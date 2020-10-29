#include "ECE_pacman.h"

void ECE_Pacman::Draw()
{
     glPushMatrix();              
     glTranslatef(110.0, 0.0, 0.0);
     glTranslatef(0.0, 60.0, 0.0);
     glutSolidSphere(5.0, 90, 20.0);
     glPopMatrix();
}
