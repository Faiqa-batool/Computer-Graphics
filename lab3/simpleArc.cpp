#include <GL/glut.h>
#include <cmath>

class Point2 {
public:
    Point2(float x, float y) : x(x), y(y) {}
    float getX() const { return x; }
    float getY() const { return y; }
private:
    float x, y;
};

void drawArc(Point2 center, float radius, float startAngle, float sweep) {
    const int n = 30;
    float angle = startAngle * 3.14159265 / 180;
    float angleInc = sweep * 3.14159265 / (180 * n);
    float cx = center.getX(), cy = center.getY();
    glVertex2d(cx + radius * cos(angle), cy + radius * sin(angle));
    for (int k = 1; k < n; k++, angle += angleInc)
        glVertex2d(cx + radius * cos(angle), cy + radius * sin(angle));
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black

    glBegin(GL_LINE_STRIP); // Begin drawing arc
    drawArc(Point2(150, 150), 100, 30, 120); // Draw arc with center (150, 150), radius 100, start angle 30, sweep 120
    glEnd(); // End drawing arc

    glFlush();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0);       // Set drawing color to black
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Drawing an Arc");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
