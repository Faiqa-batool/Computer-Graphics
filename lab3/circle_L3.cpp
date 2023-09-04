#include <GL/glut.h>
#include <cmath>

const int screenWidth = 640;
const int screenHeight = 480;
const float radius = 0.3f; // Radius of the circle
const int numSegments = 100; // Number of triangles to approximate the circle

void drawCircle() {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the circle
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f); // Move circle away from camera

    drawCircle();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Circle Drawing");
    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up the coordinate system
    glutMainLoop();
    return 0;
}
