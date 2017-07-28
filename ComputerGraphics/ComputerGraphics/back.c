#include "back.h"
#include <GL\glut.h>
#include <stdio.h>

#define imageWidth 256
#define imageHeight 256

unsigned char texImage[imageHeight][imageWidth][3];

void readPPMImage(char* filename) {
	FILE *fp;
	int  ch, i;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Cannot open ppm file %s\n", filename);
		exit(1);
	}
	for (i = 0; i < 4; i++) { 						
		while (1) {
			if ((ch = fgetc(fp)) != '#') break;		
			fgets((char*)texImage, 1024, fp);   	
			while (isspace(ch)) ch = fgetc(fp);  	
		}
		while (!isspace(ch)) ch = fgetc(fp);		

		if (i < 3) {
			while (isspace(ch)) ch = fgetc(fp);		
		}
	}
	fread(texImage, 1, imageWidth*imageHeight * 3, fp);
	fclose(fp);
}

void setupTexture(char* filename) {
	readPPMImage(filename);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// テクスチャの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
}

void drawGround() {
	double	tc = 10.0;

	setupTexture("ground.ppm");

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_STENCIL_TEST);

	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_NOTEQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glBegin(GL_QUADS);
	// ループで貼り付け
	glColor3d(1.0, 1.0, 1.0);
	/* x = 20 * 10, z = 20 * 10 */
	for (int i = -20; i < 21; i += 2) {
		glTexCoord2d(0.0, 0.0); glVertex3i(-20, -0.5, i);
		glTexCoord2d(0.0, tc); glVertex3i(20, -0.5, i);
		glTexCoord2d(tc, tc); glVertex3i(i, -0.5, 20);
		glTexCoord2d(tc,  0.0); glVertex3i(i, -0.5, -20);
	}
	glEnd();

	glStencilFunc(GL_EQUAL, 1, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_2D);
}

void drawBackGround() {
	glClearColor(0.5, 0.7, 1.0, 1.0);
}
