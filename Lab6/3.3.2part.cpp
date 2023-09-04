#include <GL/glut.h>
#include <cmath>

class Canvas {
public:
    Canvas(int width, int height, const char* window_title) {
        glutInitWindowSize(width, height);
        glutInitWindowPosition(0, 0);
        glutCreateWindow(window_title);
        window[0] = 0;
        window[1] = width;
        window[2] = 0;
        window[3] = height;
        viewport[0] = 0;
        viewport[1] = width;
        viewport[2] = 0;
        viewport[3] = height;
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        cp[0] = 0.0f;
        cp[1] = 0.0f;
        cd = 0.0;
        set_window(0, width, 0, height);
        set_viewport(0, width, 0, height);
    }

    float window_aspect() {
        return (window[1] - window[0]) / (window[3] - window[2]);
    }

    static void swap() {
        glutSwapBuffers();
    }

    static void clear_screen() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void set_bc(float r, float g, float b) {
        glClearColor(r, g, b, 0.0);
    }

    static void thick(float t) {
        glLineWidth(t);
    }

    void set_color(float r, float g, float b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        glColor3f(r, g, b);
    }

    void set_window(float l, float r, float b, float t) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(l, r, b, t);
        window[0] = l;
        window[1] = r;
        window[2] = b;
        window[3] = t;
    }

    void set_viewport(int left, int right, int bottom, int top) {
        glViewport(left, bottom, right - left, top - bottom);
        viewport[0] = left;
        viewport[1] = right;
        viewport[2] = bottom;
        viewport[3] = top;
    }

    void line_to(float x, float y) {
        glBegin(GL_LINES);
        glVertex2f(cp[0], cp[1]);
        glVertex2f(x, y);
        glEnd();
        glFlush();
        cp[0] = x;
        cp[1] = y;
    }

    void line_rel(float dx, float dy) {
        line_to(cp[0] + dx, cp[1] + dy);
    }

    void turn(float ang) {
        cd += ang;
    }

    void forward(float dist, bool isVisible = true) {
        const float rad_per_deg = 0.017453393f;
        float x = cp[0] + (dist * std::cos(rad_per_deg * cd));
        float y = cp[1] + (dist * std::sin(rad_per_deg * cd));
        if (isVisible) {
            line_to(x, y);
        }
        else {
            cp[0] = x;
            cp[1] = y;
        }
    }

    void arrow(float f, float h, float t, float w) {
        line_rel(-w - (t / 2), -f);
        line_rel(w, 0);
        line_rel(0, -h);
        line_rel(t, 0);
        line_rel(0, h);
        line_rel(-w, 0);
        line_rel(-w - (t / 2), f);
    }

    void hook(float side) {
        forward(3 * side);
        turn(90);
        forward(side);
        turn(90);
        forward(side);
        turn(90);
    }

    float window[4];
    float viewport[4];
    float color[3];
    float cp[2];
    float cd;
};


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    Canvas hook_cvs(640, 480, "a hook motif(Turtle Graphics)");
    hook_cvs.set_bc(1.0, 1.0, 1.0);
    hook_cvs.clear_screen();
    hook_cvs.set_color(0, 0, 0);
    hook_cvs.cp[0] = 250;
    hook_cvs.cp[1] = 350;
    for (int i = 0; i < 4; ++i) {
        hook_cvs.hook(70);
    }
    hook_cvs.swap();
    glutMainLoop();
    return 0;
}