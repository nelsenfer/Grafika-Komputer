#include <GL/freeglut.h> // Penyesuaian wajib untuk ekosistem Windows/freeGLUT

const int A = 500;
const float B = 500;
const float D = 200;

void myinit(void)
{
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-B / 2, B / 2, -B / 2, B / 2);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-D / 2, -D / 2);
    glVertex2f(D / 2, -D / 2);
    glVertex2f(D / 2, D / 2);
    glVertex2f(-D / 2, D / 2);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(A, A);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("GRAFKOM TEKNOLOGI GAME");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();

    return 0;
}