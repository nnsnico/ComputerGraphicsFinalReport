#include "drawer.h"
#include <GL\glut.h>

void drawGround() {
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = -35; i < 36; i += 2) {
		glVertex3i(  i, 0, -35);
		glVertex3i(  i, 0,  35);
		glVertex3i(-50, 0,   i);
		glVertex3i( 50, 0,   i);
	}
	glEnd();
}