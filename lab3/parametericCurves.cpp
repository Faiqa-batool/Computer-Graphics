#include <GL/glut.h>
#include <cmath>

const int numPoints = 200; // the number of sample points to use for the parametric curve
#define CIRCLE 1
#define ROSE 4

float x(float t, int curveType) {
    if (curveType == CIRCLE) {
        return cos(t);
    }
    else if (curveType == ROSE) {
        return cos(4 * t) * cos(t);
    }
    return 0;
}

float y(float t, int curveType) {
    if (curveType == CIRCLE) {
        return sin(t);
    }
    else if (curveType == ROSE) {
        return cos(4 * t) * sin(t);
    }
    return 0;
}

void computeCurve(int curveType) {
    glBegin(GL_POINTS);
    for (int i = 0; i < numPoints; i++) {
        float t = 2 * 3.14159265 * i / numPoints;
        glVertex2f(x(t, curveType), y(t, curveType));
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0); // Set drawing color to blue

    // Plot circle
    glPointSize(2.0);
    computeCurve(CIRCLE);

    // Plot rose
    glColor3f(1.0, 0.0, 0.0); // Set drawing color to red
    glPointSize(1.5);
    computeCurve(ROSE);

    glFlush();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0);       // Set drawing color to black
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Parametric Curves");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}
