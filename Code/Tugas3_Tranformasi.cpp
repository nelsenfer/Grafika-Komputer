#include <GL/freeglut.h>

float posX = 0.0f;
float posY = 0.0f;
float angle = 0.0f;
float scaleSize = 1.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(posX, posY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(scaleSize, scaleSize, 1.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.2f, 0.2f);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int, int)
{
    if (key == 'w')
        posY += 0.05f; // Geser ke atas
    if (key == 's')
        posY -= 0.05f; // Geser ke bawah
    if (key == 'a')
        posX -= 0.05f; // Geser ke kiri
    if (key == 'd')
        posX += 0.05f; // Geser ke kanan

    if (key == 'q')
        angle += 5.0f; // Putar searah jarum jam
    if (key == 'e')
        angle -= 5.0f; // Putar berlawanan arah jarum jam

    if (key == 'z')
        scaleSize += 0.1f; // Perbesar objek
    if (key == 'c' && scaleSize > 0.1f)
        scaleSize -= 0.1f; // Perkecil objek

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Transformasi Objek Nelss");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
