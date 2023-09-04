#include <GL/glut.h>
#include <cmath>

void ngon(int n, double cx, double cy, double radius, double rotAngle) {
    if (n < 3) {
        return;
    }
    double angle = rotAngle * 3.14159265 / 180;
    double angleInc = 2 * 3.14159265 / n;

    glBegin(GL_LINE_LOOP); // Begin drawing loop for the polygon
    for (int k = 0; k < n; k++) {
        glVertex2d(radius * cos(angle) + cx, radius * sin(angle) + cy);
        angle += angleInc;
    }
    glEnd(); // End drawing loop for the polygon
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black

    // Approximate a circle with 100 sides
    ngon(100, 150, 150, 100, 0);

    glFlush();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0);       // Set drawing color to black
    glPointSize(4.0);               // Set point size to 4
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Approximating a Circle");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
