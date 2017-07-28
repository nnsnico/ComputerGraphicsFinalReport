#include <GL\glut.h>
#include "drawer.h"

void drawHead(int head) {
	/* head */
	glPushMatrix();
		glTranslated(0.0, 1.25, 0.0);
		glRotated(90, 0.0, 1.0, 0.0);
		glRotated((double)head, 0.0, 1.0, 0.0);
		glPushMatrix();
			glScaled(1.0, 1.0, 1.0);
			glutWireSphere(0.5, 20.0, 10.0);
		glPopMatrix();

		glTranslated(0.0, 0.0, 0.5);
		glPushMatrix();
			glScaled(1.0, 1.0, 1.0);
			glutWireCone(0.125, 0.25, 20.0, 10.0);
		glPopMatrix();
	glPopMatrix();
}

void drawRightArm(int shoulder, int elbow) {
	glPushMatrix();
		/* right arm (1st link) */
		glTranslated(0.0, 0.7, 0.0);
		glRotated((double)shoulder, 0.0, 0.0, 1.0);
		glTranslated(0.5, 0.0, 1.0);
		glPushMatrix();
			glScaled(1.0, 0.5, 0.5);
			glutWireCube(1.0);
		glPopMatrix();

		/* right arm (2nd link) */
		glTranslated(0.5, 0.0, 0.0);				//move to the end of 1st link
		glRotated((double)elbow, 0.0, 0.0, 1.0);
		glTranslated(0.5, 0.0, 0.0);
		glPushMatrix();
			glScaled(1.0, 0.5, 0.5);
			glutWireCube(1.0);
		glPopMatrix();

		/* right arm (3rd link) */
		glTranslated(0.5, 0.0, 0.0);				//move to the end of 1st link
		glTranslated(0.2, 0.0, 0.0);
		glPushMatrix();
			glScaled(0.5, 0.5, 0.5);
			glutWireSphere(0.5, 20.0, 10.0);
		glPopMatrix();
	glPopMatrix();
}

void drawLeftArm(int shoulder, int elbow) {
	glPushMatrix();
		/* left arm (1st link) */
		glTranslated(0.0, 0.7, 0.0);
		glRotated((double)shoulder, 0.0, 0.0, 1.0);
		glTranslated(0.5, 0.0, -1.0);
		glPushMatrix();
			glScaled(1.0, 0.5, 0.5);
			glutWireCube(1.0);
		glPopMatrix();

		/* left arm (2nd link) */
		glTranslated(0.5, 0.0, 0.0);				//move to the end of 1st link
		glRotated((double)elbow, 0.0, 0.0, 1.0);
		glTranslated(0.5, 0.0, 0.0);
		glPushMatrix();
			glScaled(1.0, 0.5, 0.5);
			glutWireCube(1.0);
		glPopMatrix();

		/* left arm (3rd link) */
		glTranslated(0.5, 0.0, 0.0);				//move to the end of 1st link
		glTranslated(0.2, 0.0, 0.0);
		glPushMatrix();
			glScaled(0.5, 0.5, 0.5);
			glutWireSphere(0.5, 20.0, 10.0);
		glPopMatrix();
	glPopMatrix();
}

void drawRightLeg(int groin, int knee) {
	glPushMatrix();
		/* right leg (1st link) */
		glTranslated(0.0, -0.85, 0.0);
		glRotated((double)groin, 0.0, 0.0, 1.0);
		glTranslated(1.0, 0.0, 0.5);
		glPushMatrix();
			glScaled(2.0, 0.7, 0.7);
			glutWireCube(1.0);
		glPopMatrix();

		/* right leg (2nd link) */
		glTranslated(1.0, 0.0, 0.0);
		glRotated((double)knee, 0.0, 0.0, 1.0);
		glTranslated(1.0, 0.0, 0.0);
		glPushMatrix();
			glScaled(2.0, 0.7, 0.7);
			glutWireCube(1.0);
		glPopMatrix();

		/* right leg (3rd link) */
		glTranslated(1.25, 0.125, 0.0);
		glPushMatrix();
			glScaled(0.5, 1.0, 0.7);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

void drawLeftLeg(int groin, int knee) {
	glPushMatrix();
		/* left leg (1st link) */
		glTranslated(0.0, -0.85, 0.0);
		glRotated((double)groin, 0.0, 0.0, 1.0);
		glTranslated(1.0, 0.0, -0.5);
		glPushMatrix();
			glScaled(2.0, 0.7, 0.7);
			glutWireCube(1.0);
		glPopMatrix();
		/* left leg (2nd link) */
		glTranslated(1.0, 0.0, 0.0);
		glRotated((double)knee, 0.0, 0.0, 1.0);
		glTranslated(1.0, 0.0, 0.0);
		glPushMatrix();
			glScaled(2.0, 0.7, 0.7);
			glutWireCube(1.0);
		glPopMatrix();

		/* left leg (3rd link) */
		glTranslated(1.25, 0.125, 0.0);
		glPushMatrix();
			glScaled(0.5, 1.0, 0.7);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();
}
