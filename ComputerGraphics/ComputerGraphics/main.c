#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "back.h"
#include "GLMetaseq.h"
#include "robot.h"
#include "animator.h"

double theta = 10.0;
double camera = 0.0;
int xStart, yStart;
double xAngle = 0, yAngle = 0;
unsigned char mouseFlag = GL_FALSE;
static int head = 0, body_r = 0;
static int r_shoulder = -90; r_elbow = 0, r_groin = -90, r_knee = 0;
static int l_shoulder = -90, l_elbow = 0, l_groin = -90, l_knee = 0;
static double ball_dist = 0.0;
static int flag = 0, time = 0;
static int ball_flag = 0;
static int ball_speed = 1.0;

static GLfloat lightPosition[4] = { -20.0, 100.0, -20.0, 1.0 }; 
static GLfloat lightDiffuse[3] = { 1.0, 1.0, 1.0 };
static GLfloat lightAmbient[3] = { 1.0, 1.0, 1.0 };
static GLfloat lightSpecular[3] = { 1.0,   1.0, 1.0 };

MQO_MODEL model;

void setMaterial(const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, GLfloat shiness) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);
}

void myInit(char *progname) {
	int width = 1280, height = 720;
	// init Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GL_STENCIL);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	// drawing mode
	glMatrixMode(GL_PROJECTION);
	gluPerspective(30.0, (double)width / (double)height, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	// light
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLoadIdentity();
	// init camera
	gluLookAt(
		-30.0, 30.0f, -30.0f,
		0.0, 0.0, 0.0,
		0.5f, 0.5f, 0.5f);
	glShadeModel(GL_FLAT);
}

void mqoInitalize() {
	mqoInit();
	model = mqoCreateModel("ポリバケツ.mqo", 0.05);
}

void myDisplay(void) {
	glPushMatrix();	//1

	glRotated(xAngle, 1.0, 0.0, 0.0);
	glRotated(yAngle, 0.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0 };
	GLfloat specular[] = { 0.25, 0.25, 0.25, 1.0 };
	GLfloat insideface[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat shiness = 0.6;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);

	drawBackGround();

	drawGround();

	GLfloat b_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
	GLfloat b_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
	GLfloat b_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
	GLfloat b_shiness = 0.4;

	glPushMatrix();
		setMaterial(b_ambient, b_diffuse, b_specular, b_shiness);
		glTranslated(18.0, 0.0, -5.0);
		mqoCallModel(model);
	glPopMatrix();

	GLfloat t_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
	GLfloat t_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
	GLfloat t_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
	GLfloat t_shiness = 0.4;

	GLfloat r_ambient[] = { 0.25, 0.20725, 0.20725, 1.0 };
	GLfloat r_diffuse[] = { 1, 0.829, 0.829, 1.0 };
	GLfloat r_specular[] = { 0.296648, 0.296648, 0.296648, 1.0 };
	GLfloat r_shiness = 5.0;
	
	// main robot
	glPushMatrix();
		glTranslated(15.0, 5.35, 0.0);
		glRotated((double)body_r + 180, 0.0, 1.0, 0.0);
		setMaterial(r_ambient, r_diffuse, r_specular, r_shiness);
		glPushMatrix();
			glScaled(1.0, 1.7, 1.7);
			glutSolidCube(1.0);
		glPopMatrix();
		drawHead(head);
		drawRightArm(0, 0, ball_flag, ball_dist);
		drawLeftArm(-120, 30);
		drawRightLeg(-120, -5);
		drawLeftLeg(-60, -30);
	glPopMatrix();

	// robot
	glPushMatrix();
		glTranslated(15.0, 5.35, 10.0);
		glRotated(80, 0.0, 1.0, 0.0);
		setMaterial(t_ambient, t_diffuse, t_specular, t_shiness);
		glPushMatrix();
			glScaled(1.0, 1.7, 1.7);
			glutSolidCube(1.0);
		glPopMatrix();
		drawHead(head);
		drawRightArm(r_shoulder, r_elbow, 0, 0);
		drawLeftArm(l_shoulder, l_elbow);
		drawRightLeg(r_groin, r_knee);
		drawLeftLeg(l_groin, l_knee);
	glPopMatrix();

	if (ball_flag == 1) {
		// 玉のようなもの，発射！！！！！！
		glPushMatrix();
			glTranslated(12.0, 6.0, -1.0);
			glTranslated(ball_dist, 0.0, ball_speed * cos(ball_dist));
			setMaterial(t_ambient, t_diffuse, t_specular, t_shiness);
			glPushMatrix();
				glScaled(0.5, 0.5, 0.5);
				glutSolidSphere(0.5, 20.0, 10.0);
			glPopMatrix();
		glPopMatrix();
	}

	glPopMatrix();	//1

	glFlush();

	glutSwapBuffers();
}

void getValueFromMenu(int value) {
	switch (value) {
		case 1:
			ball_speed = 1.0;
			break;
		case 2:
			ball_speed = 2.0;
			break;
		case 3:
			ball_speed = 4.0;
			break;
		default :
			break;
	}
}

void mySetMenu() {
	glutCreateMenu(getValueFromMenu);
	glutAddMenuEntry("Init Ball Speed", 1);
	glutAddMenuEntry("Ball Speed = x2", 2);
	glutAddMenuEntry("Ball Speed = x4", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myMouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xStart = x;
		mouseFlag = GL_TRUE;
	} else {
		mouseFlag = GL_FALSE;
	}
}

void myMotionFunc(int x, int y) {
	int xdis, ydis;
	double a = 0.5;

	if (mouseFlag == GL_FALSE) return;
	xdis = x - xStart;
	ydis = y - yStart;
	xAngle += (double) ydis *a;
	yAngle += (double) xdis *a;
	xStart = x;
	yStart = y;
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
	// keyboard
	switch (key) {
		case 'a':
			if (flag == 0) {
				time = 0;
				// elbow
				r_elbow = 30;
				l_elbow = 30;
				// shoulder
				l_shoulder = -125;
				r_shoulder = -65;
				flag = 1;
			}
			else {
				flag = 0;
			}
			break;
		case 'b':
			ball_flag = 1;
			break;
		// ESC
		case 27:
			exit(0);
		default:
			break;
	}
}

void myIdle(int value) {
	// loop
	if (ball_flag == 1 && ball_dist <= 30) {
		ball_dist -= ball_speed;
		if (ball_dist <= -30) {
			ball_flag = 0;
			ball_dist = 0.0;
		}
		glutPostRedisplay();
	}

	// robot idle
	time = time + 100;
	if (flag == 1) {
		r_shoulder = r_animate(r_shoulder, time);
		l_shoulder = l_animate(l_shoulder, time);
	} else {
		glutPostRedisplay();
	}
	glutTimerFunc(50, myIdle, value);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	myInit("Computer Graphics Final Report");
	mySetMenu();
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMotionFunc);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	//glutIdleFunc(myIdle);
	mqoInitalize();
	glutTimerFunc(50, myIdle, 1);

	glutMainLoop();
	mqoDeleteModel(model);
	mqoCleanup();
	return 0;
}