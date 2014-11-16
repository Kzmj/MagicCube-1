#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gl/freeglut.h>
#include "MagicCube.h"
#include "TextureSet.h"

#define EACH_SIDE 512              // 一个小正方体的边长
#define BETWEEN_GAP 64             // 小方块之间的间隔

void display();
void reshape(int width, int height);
void idle();

void init();

MagicCube* magicCube = nullptr;
Point* eye = nullptr;
Point* upOrder = nullptr;

int screenWidth = 768;
int screenHeight = 700;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("magic cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	init();
	glutMainLoop();
	return 0;
}

void init() {
	magicCube = new MagicCube(EACH_SIDE, BETWEEN_GAP);
	eye = new Point(1500, 1500, 1500);
	upOrder = new Point(-1, 1, -1);
	srand((unsigned)time(0));
}

void reshape(int width, int height) {
	screenHeight = width;
	screenHeight = height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-500, 500, -500, 500, 400, 10000);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), 0, 0, 0, upOrder->getX(), upOrder->getY(), upOrder->getZ());

	magicCube->dispatchDraw();

	glFlush();
	glutSwapBuffers();
}

void idle() {
	if (!magicCube->isNeedRefresh()) {
		GLint orientation = 1 + rand() % 2;
		GLint ratateSurface = rand() % 6;

		magicCube->startRotate(orientation, ratateSurface);
	}

	magicCube->calulateRotate();
	glutPostRedisplay();
}
