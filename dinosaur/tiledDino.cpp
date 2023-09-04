#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <vector>

struct Point {
    GLfloat x, y;
};

std::vector<std::vector<Point>> polylines;

void drawPolylines() {
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black

    for (const auto& polyline : polylines) {
        glBegin(GL_LINE_STRIP);
        for (const auto& point : polyline) {
            glVertex2f(point.x, point.y);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            glViewport(i * 128, j * 96, 128, 96);
            drawPolylines();
        }
    }

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void parseData() {
    std::ifstream inFile("dino.dat");
    if (!inFile) {
        std::cerr << "Unable to open file." << std::endl;
        exit(1);
    }

    int numPolylines;
    inFile >> numPolylines;

    for (int i = 0; i < numPolylines; i++) {
        int numVertices;
        inFile >> numVertices;

        std::vector<Point> polyline;
        for (int j = 0; j < numVertices; j++) {
            Point point;
            inFile >> point.x >> point.y;
            polyline.push_back(point);
        }

        polylines.push_back(polyline);
    }

    inFile.close();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab Activity 02: Tiled Dinosaurs");
    parseData();
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}