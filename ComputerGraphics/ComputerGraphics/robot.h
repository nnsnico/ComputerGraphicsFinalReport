#pragma once
#ifndef _ROBOT_H_
#define _ROBOT_H_
#include<GL\glut.h>

void drawHead(int head);
void drawRightArm(int shoulder, int elbow, int ball_flag, double ball_dist);
void drawLeftArm(int shoulder, int elbow);
void drawRightLeg(int groin, int knee);
void drawLeftLeg(int groin, int knee);

#endif // _ROBOT_H_
