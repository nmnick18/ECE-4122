#define ESC 27

#include <iostream>
#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions



class ECE_Board {

public:
	// map visual appearance:
	void DrawWall();
	void DrawInnerWalls();
	void drawMaze();
};