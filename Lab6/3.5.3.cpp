#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Initial position of the turtle
float turtleX = 0.0, turtleY = 0.0;
float turtleAngle = 0.0;

void drawSequence() {
    std::string commands = "FLFLFLFRFLFLFLFRFLFLFLFR";

    glBegin(GL_LINE_STRIP);

    // Add starting point
    glVertex2f(turtleX, turtleY);

    for (char command : commands) {
        if (command == 'R') {
            turtleAngle -= 60.0;
        }
        else if (command == 'L') {
            turtleAngle += 60.0;
        }
        else if (command == 'F') {
            // Calculate new position based on angle
            turtleX += cos(turtleAngle * 3.14159 / 180.0);
            turtleY += sin(turtleAngle * 3.14159 / 180.0);
            glVertex2f(turtleX, turtleY); // Add the new position to the path
        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    drawSequence();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Figure Drawing");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-10, 10, -10, 10);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}