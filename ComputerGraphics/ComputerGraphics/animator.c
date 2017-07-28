#include<GL\glut.h>
#include<math.h>
#include "drawer.h"

int r_animate(int target, int value) {
	if ((ceil(sin(2 * 3.14 * value)) == 1)) {
		printf("forword\n");
		target = (target + 5) % 360;
	}
	else {
		printf("back\n");
		target = (target - 5) % 360;
	}
	glutPostRedisplay();
	printf("target = %d\nvalue = %d\n", target, value);
	printf("sin = %f\n", ceil(sin(2 * 3.14 * value)));
	return target;
}

void l_animate(int target, int value) {
	if ((ceil(sin(2 * 3.14 * value)) == 1)) {
		printf("forword\n");
		target = (target - 5) % 360;
	}
	else {
		printf("back\n");
		target = (target + 5) % 360;
	}
	glutPostRedisplay();
	printf("target = %d\nvalue = %d\n", target, value);
	printf("sin = %f\n", ceil(sin(2 * 3.14 * value)));
	return target;
}