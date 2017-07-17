#include <stdio.h>
#include <GL/glut.h>
#include "drawer.h"

void myInit(char *progname) {
	int width = 800, height = 600;
	// init Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	// init camera
	gluLookAt(
		-2.0, 2.0, -2.0,
		0.0, 0.0, 0.0,
		0.5, 0.5, 0.5);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0.7, 1.0, 1.0);
	//glPushMatrix();	//1
	//	glPushMatrix();	//2
	//		glRotated(1.0, 1.0, 1.0, 1.0);
	//		glColor3d(1.0, 0.0, 0.0);
	//		glutWireTeapot(1.0);
	//	glPopMatrix();	//2
		drawGround();
	glPopMatrix();	//1
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	// keyboard
	switch (key) {
		// ESC
		case 27:
			exit(0);
		default:
			break;
	}
}

void myIdle(void) {
	// loop
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	myInit("Computer Graphics Final Report");
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}