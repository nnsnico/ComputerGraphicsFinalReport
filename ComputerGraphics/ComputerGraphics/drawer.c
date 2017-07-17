#include "drawer.h"
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
	for (i = 0; i < 4; i++) { 						// skip four in header
		while (1) {
			if ((ch = fgetc(fp)) != '#') break;		// skip comment
			fgets((char*)texImage, 1024, fp);   	// dummy read
			while (isspace(ch)) ch = fgetc(fp);  	// skip space
		}
		while (!isspace(ch)) ch = fgetc(fp);		// read header
													/* Newline or other single terminator after header may exist. */
		if (i < 3) {
			while (isspace(ch)) ch = fgetc(fp);		// skip terminator
		}
	}
	fread(texImage, 1, imageWidth*imageHeight * 3, fp);	// read RGB data
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glEnable(GLUT_DEPTH);
	glEnable(GL_SHININESS);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	// ループで貼り付け
	for (int i = -35; i < 36; i += 2) {
		glTexCoord2d(0.0, tc);		glVertex3i(-35, 0, i);
		glTexCoord2d(0.0, 0.0);		glVertex3i(i, 0, 35);
		glTexCoord2d(tc,  0.0);		glVertex3i(i, 0, -35);
		glTexCoord2d(tc,  tc);		glVertex3i( 35, 0,   i);
	}
	glEnd();

	glFlush();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_SHININESS);
	glDisable(GL_DEPTH);
}

void drawBackGround() {

}

