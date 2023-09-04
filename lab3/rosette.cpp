#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

class Point2 {
public:
    float x, y;
    void set(float dx, float dy) {
        x = dx;
        y = dy;
    }
    void set(Point2& p) {
        x = p.x;
        y = p.y;
    }
    Point2(float xx, float yy) {
        x = xx;
        y = yy;
    }
    Point2() {
        x = y = 0;
    }
};

Point2 currPos;
Point2 CP;

void moveTo(Point2 p) {
    CP.set(p);
}

void lineTo(Point2 p) {
    glBegin(GL_LINES);
    glVertex2f(CP.x, CP.y);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
    CP.set(p);
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Background color is white
    glColor3f(0.0, 0.0, 0.0); // Drawing color is black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the world window
}

void rosette(int N, float radius) {
    Point2* pointlist = new Point2[N];
    GLfloat theta = (2.0f * 3.1415926536) / N;

    // Calculate the points of the polygon
    for (int c = 0; c < N; c++) {
        pointlist[c].set(radius * sin(theta * c), radius * cos(theta * c));
    }

    // Draw lines connecting the points to create the rosette
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            moveTo(pointlist[i]);
            lineTo(pointlist[j]);
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(10, 10, 640, 480);

    // Draw 5-gon rosette
    glPushMatrix();
    glTranslatef(-0.5f, 0.5f, 0.0f);
    rosette(5, 0.3f);
    glPopMatrix();

    // Draw 11-gon rosette
    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.0f);
    rosette(11, 0.3f);
    glPopMatrix();

    // Draw 17-gon rosette
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    rosette(17, 0.3f);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Rosettes");
    glutDisplayFunc(render);

    myInit();
    glutMainLoop();

    return 0;
}
