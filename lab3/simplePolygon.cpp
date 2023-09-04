#include <GL/glut.h>
#include <cmath>

// Window dimensions
int screenWidth = 800;
int screenHeight = 600;

// Regular polygon parameters
int numSides = 6; // Change this to the desired number of sides
float radius = 0.4f; // Change this to the desired radius

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate the angle between each vertex
    float pi = 3.14159265358979323846;
    float angle = 2.0f * pi / numSides;

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < numSides; ++i)
    {
        float x = radius * std::cos(i * angle);
        float y = radius * std::sin(i * angle);
        glVertex2f(x, y);
    }

    glEnd();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Regular Polygon");


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}