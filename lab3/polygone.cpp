#include <GL/freeglut.h>
#include <cmath>

// Window dimensions
int screenWidth = 800;
int screenHeight = 600;

void drawEquilateralTriangle()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, -0.2f); // Bottom-left vertex
    glVertex2f(0.2f, -0.2f);  // Bottom-right vertex
    glVertex2f(0.0f, 0.4f);   // Top vertex
    glEnd();
}

void drawHexagon()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4f, 0.0f);  // Leftmost vertex
    glVertex2f(-0.2f, -0.3464f); // Bottom-left vertex
    glVertex2f(0.2f, -0.3464f);  // Bottom-right vertex
    glVertex2f(0.4f, 0.0f);   // Rightmost vertex
    glVertex2f(0.2f, 0.3464f);  // Top-right vertex
    glVertex2f(-0.2f, 0.3464f); // Top-left vertex
    glEnd();
}

void drawSquare()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, -0.2f); // Bottom-left vertex
    glVertex2f(0.2f, -0.2f);  // Bottom-right vertex
    glVertex2f(0.2f, 0.2f);   // Top-right vertex
    glVertex2f(-0.2f, 0.2f);  // Top-left vertex
    glEnd();
}

void drawPentagon()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3f, 0.0f);  // Left vertex
    glVertex2f(-0.15f, -0.29f); // Bottom-left vertex
    glVertex2f(0.15f, -0.29f);  // Bottom-right vertex
    glVertex2f(0.3f, 0.0f);   // Right vertex
    glVertex2f(0.0f, 0.3f);   // Top vertex
    glEnd();
}

void drawRhombus()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.15f, 0.0f);  // Left vertex
    glVertex2f(0.0f, -0.3f);   // Bottom vertex
    glVertex2f(0.15f, 0.0f);   // Right vertex
    glVertex2f(0.0f, 0.3f);    // Top vertex
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glPushMatrix();
    drawEquilateralTriangle(); // Equilateral Triangle
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green
    glPushMatrix();
    glTranslatef(-0.6f, -0.6f, 0.0f); // Move left and down for hexagon
    drawHexagon(); // Hexagon
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 1.0f); // Set color to blue
    glPushMatrix();
    glTranslatef(0.6f, -0.6f, 0.0f); // Move right and down for square
    drawSquare(); // Square
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f); // Set color to yellow
    glPushMatrix();
    glTranslatef(-0.6f, 0.6f, 0.0f); // Move left and up for pentagon
    drawPentagon(); // Pentagon
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 1.0f); // Set color to cyan
    glPushMatrix();
    glTranslatef(0.6f, 0.6f, 0.0f); // Move right and up for rhombus
    drawRhombus(); // Rhombus
    glPopMatrix();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Polygons");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black

    glutMainLoop();
    return 0;
}