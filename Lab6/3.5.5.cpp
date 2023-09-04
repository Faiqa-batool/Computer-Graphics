#include <GL/glut.h>
#include <cmath>

float turtleX = 0.0f;
float turtleY = 0.0f;
float turtleAngle = 0.0f;

void forward(float distance) {
    float newX = turtleX + distance * cos(turtleAngle);
    float newY = turtleY + distance * sin(turtleAngle);

    glBegin(GL_LINES);
    glVertex2f(turtleX, turtleY);
    glVertex2f(newX, newY);
    glEnd();

    turtleX = newX;
    turtleY = newY;
}

void turn(float angle) {
    turtleAngle += angle;
}

void drawT(float size) {
    forward(size);
    turn(90.0f);
    forward(10.0f); // Width of the T
    turn(-90.0f);
    forward(size);
    turn(-90.0f);
    forward(20.0f); // Gap between Ts
    forward(size);
    turn(90.0f);
    forward(10.0f); // Width of the T
    turn(-90.0f);
    forward(size);
    turn(90.0f);    // Turn back to original orientation
}

void drawOppositeT(float size) {
    forward(size);
    turn(-90.0f);
    forward(10.0f); // Width of the T
    turn(90.0f);
    forward(size);
    turn(90.0f);
    forward(20.0f); // Gap between Ts
    forward(size);
    turn(-90.0f);
    forward(10.0f); // Width of the T
    turn(90.0f);
    forward(size);
    turn(-90.0f);   // Turn back to original orientation
}

void drawPattern(int rowCount, int colCount, float size, float spacing) {
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            drawT(size);
            forward(spacing);
            drawOppositeT(size);
            forward(spacing);
        }
        turtleX = 0.0f; // Reset the X position after each row
        turtleY -= spacing * 2; // Move down by double spacing
    }
    turtleX = 0.0f;
    turtleY = 0.0f;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    turtleX = 0.0f;
    turtleY = 300.0f;
    turtleAngle = 0.0f;

    glPushMatrix();
    drawPattern(3, 5, 30.0f, 80.0f);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Pattern of Ts and Reversed Ts");
    gluOrtho2D(0, 400, 0, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}