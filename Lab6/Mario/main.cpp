#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "pixMap.h"
#include "Mario.h"

Mario m(Point2(0, 0));

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m.changeMode(Mario::STAY);

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m.render();
	glFlush();
}

void spinner(int t)
{
	glutPostRedisplay();
	glutTimerFunc(200, spinner, t);

}


void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case 'r':

		m.changeMode(Mario::RUN);
		break;

	case 'j':

		m.changeMode(Mario::JUMP);
		break;
	}

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("My Mario----");


	glutDisplayFunc(display);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	glutIdleFunc(display);
	glutMainLoop();
}

