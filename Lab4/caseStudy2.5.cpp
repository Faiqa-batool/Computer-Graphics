#include <GL/glut.h>
#include <iostream>
#include<algorithm>
#include<random>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>

const int R = 10; // Rows
const int C = 10; // Columns
const int CELL_SIZE = 40;
bool walls[R][C][4]; // Up, Right, Down, Left
bool visited[R][C];

enum Direction {
    UP, RIGHT, DOWN, LEFT
};

std::stack<std::pair<int, int>> pathStack;

void removeWall(int row, int col, Direction dir) {
    walls[row][col][dir] = false;

    int newRow = row + (dir == UP) - (dir == DOWN);
    int newCol = col + (dir == RIGHT) - (dir == LEFT);

    walls[newRow][newCol][3 - dir] = false;
}

void generateMaze() {
    for (int row = 0; row < R; ++row) {
        for (int col = 0; col < C; ++col) {
            walls[row][col][UP] = true;
            walls[row][col][RIGHT] = true;
            walls[row][col][DOWN] = true;
            walls[row][col][LEFT] = true;
            visited[row][col] = false;
        }
    }

    srand(time(nullptr));
    std::stack<std::pair<int, int>> stack;
    int startRow = rand() % R;
    int startCol = rand() % C;
    stack.push(std::make_pair(startRow, startCol));

    while (!stack.empty()) {
        int row = stack.top().first;
        int col = stack.top().second;
        stack.pop();

        visited[row][col] = true;

        std::vector<Direction> directions = { UP, RIGHT, DOWN, LEFT };
        std::random_shuffle(directions.begin(), directions.end());

        for (Direction dir : directions) {
            int newRow = row + (dir == UP) - (dir == DOWN);
            int newCol = col + (dir == RIGHT) - (dir == LEFT);

            if (newRow >= 0 && newRow < R && newCol >= 0 && newCol < C &&
                walls[newRow][newCol][UP] && walls[newRow][newCol][RIGHT] &&
                walls[newRow][newCol][DOWN] && walls[newRow][newCol][LEFT]) {

                removeWall(row, col, dir);
                stack.push(std::make_pair(newRow, newCol));
            }
        }
    }
}

void drawMaze() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    for (int row = 0; row < R; ++row) {
        for (int col = 0; col < C; ++col) {
            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;

            if (walls[row][col][UP]) {
                glVertex2i(x, y);
                glVertex2i(x + CELL_SIZE, y);
            }
            if (walls[row][col][RIGHT]) {
                glVertex2i(x + CELL_SIZE, y);
                glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
            }
            if (walls[row][col][DOWN]) {
                glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
                glVertex2i(x, y + CELL_SIZE);
            }
            if (walls[row][col][LEFT]) {
                glVertex2i(x, y + CELL_SIZE);
                glVertex2i(x, y);
            }

            if (visited[row][col]) {
                glColor3f(0.0, 0.0, 1.0); // Blue color for visited cells
                glRecti(x + 1, y + 1, x + CELL_SIZE - 1, y + CELL_SIZE - 1);
                glColor3f(0.0, 0.0, 0.0);
            }
        }
    }
    glEnd();

    if (!pathStack.empty()) {
        int currRow = pathStack.top().first;
        int currCol = pathStack.top().second;
        glColor3f(1.0, 0.0, 0.0); // Red color for current cell
        glRecti(currCol * CELL_SIZE + 1, currRow * CELL_SIZE + 1, (currCol + 1) * CELL_SIZE - 1, (currRow + 1) * CELL_SIZE - 1);
    }

    glFlush();
}

void display() {
    drawMaze();
    glutSwapBuffers();
}

void timer(int value) {
    if (!pathStack.empty()) {
        int currRow = pathStack.top().first;
        int currCol = pathStack.top().second;

        std::vector<Direction> validDirections;
        if (currRow > 0 && !walls[currRow][currCol][UP] && !visited[currRow - 1][currCol])
            validDirections.push_back(UP);
        if (currCol < C - 1 && !walls[currRow][currCol][RIGHT] && !visited[currRow][currCol + 1])
            validDirections.push_back(RIGHT);
        if (currRow < R - 1 && !walls[currRow][currCol][DOWN] && !visited[currRow + 1][currCol])
            validDirections.push_back(DOWN);
        if (currCol > 0 && !walls[currRow][currCol][LEFT] && !visited[currRow][currCol - 1])
            validDirections.push_back(LEFT);

        if (!validDirections.empty()) {
            Direction chosenDir = validDirections[rand() % validDirections.size()];
            int newRow = currRow + (chosenDir == UP) - (chosenDir == DOWN);
            int newCol = currCol + (chosenDir == RIGHT) - (chosenDir == LEFT);

            removeWall(currRow, currCol, chosenDir);
            pathStack.push(std::make_pair(newRow, newCol));
            visited[newRow][newCol] = true;
        }
        else {
            glColor3f(0.0, 0.0, 1.0); // Blue color for backtracked cells
            glRecti(currCol * CELL_SIZE + 1, currRow * CELL_SIZE + 1, (currCol + 1) * CELL_SIZE - 1, (currRow + 1) * CELL_SIZE - 1);
            glColor3f(0.0, 0.0, 0.0);
            pathStack.pop();
        }

        glutPostRedisplay();
        glutTimerFunc(100, timer, 0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(C * CELL_SIZE, R * CELL_SIZE);
    glutCreateWindow("Maze Generation and Running");
    glClearColor(1.0, 1.0, 1.0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, C * CELL_SIZE, R * CELL_SIZE, 0);

    generateMaze();

    int startRow = rand() % R;
    int startCol = rand() % C;
    pathStack.push(std::make_pair(startRow, startCol));
    visited[startRow][startCol] = true;

    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);

    glutMainLoop();
    return 0;
}