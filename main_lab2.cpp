#include <iostream>
#include <GL/glut.h>
#include<cmath>

void drawHouse() {
    // Draw the base of the house
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.6f, 0.4f); // Light Brown Color
    glVertex2f(-0.5f, -0.7f);    // Lower the position of the house
    glVertex2f(0.5f, -0.7f);     // Lower the position of the house
    glVertex2f(0.5f, -0.2f);     // Lower the position of the house
    glVertex2f(-0.5f, -0.2f);    // Lower the position of the house
    glEnd();

    // Draw the roof of the house
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red Color
    glVertex2f(-0.6f, -0.2f);    // Lower the position of the house
    glVertex2f(0.6f, -0.2f);     // Lower the position of the house
    glVertex2f(0.0f, 0.3f);      // Lower the position of the house
    glEnd();

    // Draw the chimney on the top right side of the roof
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red Color
    glVertex2f(0.3f, 0.0f);      // Top left corner of the chimney
    glVertex2f(0.35f, 0.0f);     // Top right corner of the chimney
    glVertex2f(0.35f, 0.15f);    // Bottom right corner of the chimney
    glVertex2f(0.3f, 0.15f);     // Bottom left corner of the chimney
    glEnd();


    // Draw the door of the house
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f); // Dark Gray Color
    glVertex2f(-0.1f, -0.7f);    // Lower the position of the house
    glVertex2f(0.1f, -0.7f);     // Lower the position of the house
    glVertex2f(0.1f, -0.3f);     // Lower the position of the house
    glVertex2f(-0.1f, -0.3f);    // Lower the position of the house
    glEnd();

    // Draw the window of the house
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.9f); // Light Gray Color
    glVertex2f(0.2f, -0.6f);     // Move the window down
    glVertex2f(0.45f, -0.6f);    // Move the window down
    glVertex2f(0.45f, -0.4f);    // Move the window down and left
    glVertex2f(0.2f, -0.4f);     // Move the window left
    glEnd();

    // Draw black cross lines inside the window
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // Black Color
    glVertex2f(0.325f, -0.6f);   // Horizontal line start
    glVertex2f(0.325f, -0.4f);   // Horizontal line end
    glVertex2f(0.2f, -0.5f);     // Vertical line start
    glVertex2f(0.45f, -0.5f);    // Vertical line end
    glEnd();

    // Draw the doorknob
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow Color
    float xCenter = -0.07f;
    float yCenter = -0.5f;
    float radius = 0.02f;
    int numSegments = 100;
    glVertex2f(xCenter, yCenter);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = xCenter + radius * cos(angle);
        float y = yCenter + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawSun() {
    // Draw the sun (a circle)
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.7f, 0.0f); // Orange Color
    float xCenter = 0.5f;
    float yCenter = 0.8f; // Position the sun in the sky
    float radius = 0.15f;
    int numSegments = 100;
    glVertex2f(xCenter, yCenter);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = xCenter + radius * cos(angle);
        float y = yCenter + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw sun rays
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i <= 360; i += 15) {
        float angle = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(360);
        float x1 = xCenter + radius * cos(angle);
        float y1 = yCenter + radius * sin(angle);
        float x2 = xCenter + (radius + 0.1f) * cos(angle);
        float y2 = yCenter + (radius + 0.1f) * sin(angle);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}

void drawGrass() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.6f, 0.0f); // Dark Green Color
    glVertex2f(-1.2f, -0.7f);    // Extend the grass till the bottom-left (a little extra on the left side)
    glVertex2f(1.2f, -0.7f);     // Extend the grass till the bottom-right (a little extra on the right side)
    glVertex2f(1.2f, -1.0f);     // Extend the grass till the bottom-right
    glVertex2f(-1.2f, -1.0f);    // Extend the grass till the bottom-left
    glEnd();


}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.6f, 0.7f, 1.0f, 0.0f); // Sky Blue Color

    glLoadIdentity();
    glTranslatef(0.0f, -0.1f, -1.0f); // Move the house away from the camera

    drawSun();
    drawHouse();
    drawGrass();

    drawHouse();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lab 2");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
