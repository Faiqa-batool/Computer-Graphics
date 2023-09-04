#include <GL/glut.h>
#include <cmath>
#include <vector>

// Struct to represent a golden rectangle
struct GoldenRectangle {
    float x, y, width, height;
};

std::vector<GoldenRectangle> goldenRectangles;
std::vector<float> regressionSlopes;

// Calculate the next golden rectangle based on the previous one
GoldenRectangle calculateNextGoldenRectangle(const GoldenRectangle& prevRectangle) {
    GoldenRectangle nextRectangle;
    if (prevRectangle.width > prevRectangle.height) {
        nextRectangle.width = prevRectangle.height;
        nextRectangle.height = prevRectangle.height / 1.61803398875; // Golden ratio
    }
    else {
        nextRectangle.height = prevRectangle.width;
        nextRectangle.width = prevRectangle.width * 1.61803398875; // Golden ratio
    }
    nextRectangle.x = prevRectangle.x + (prevRectangle.width - nextRectangle.width) / 2.0;
    nextRectangle.y = prevRectangle.y + (prevRectangle.height - nextRectangle.height) / 2.0;
    return nextRectangle;
}

// Calculate regression line using least squares method
float calculateRegressionLine(const std::vector<float>& xValues, const std::vector<float>& yValues) {
    int n = xValues.size();
    float sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXSquare = 0.0;
    for (int i = 0; i < n; ++i) {
        sumX += xValues[i];
        sumY += yValues[i];
        sumXY += xValues[i] * yValues[i];
        sumXSquare += xValues[i] * xValues[i];
    }
    float slope = (n * sumXY - sumX * sumY) / (n * sumXSquare - sumX * sumX);
    return slope;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 400);

    GoldenRectangle firstRectangle = { 100, 100, 400, 250 };
    goldenRectangles.push_back(firstRectangle);

    for (int i = 0; i < 10; ++i) {
        GoldenRectangle nextRectangle = calculateNextGoldenRectangle(goldenRectangles.back());
        goldenRectangles.push_back(nextRectangle);

        std::vector<float> xValues, yValues;
        for (const GoldenRectangle& rect : goldenRectangles) {
            xValues.push_back(rect.x + rect.width / 2.0);
            yValues.push_back(rect.y + rect.height / 2.0);
        }
        float slope = calculateRegressionLine(xValues, yValues);
        regressionSlopes.push_back(slope);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    for (const GoldenRectangle& rect : goldenRectangles) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(rect.x, rect.y);
        glVertex2f(rect.x + rect.width, rect.y);
        glVertex2f(rect.x + rect.width, rect.y + rect.height);
        glVertex2f(rect.x, rect.y + rect.height);
        glEnd();
    }

    for (int i = 0; i < regressionSlopes.size(); ++i) {
        glBegin(GL_LINES);
        glVertex2f(0, regressionSlopes[i] * 0 + regressionSlopes[i]);
        glVertex2f(600, regressionSlopes[i] * 600 + regressionSlopes[i]);
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Golden Rectangles Regression");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
