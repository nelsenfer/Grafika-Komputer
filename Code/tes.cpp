#include <GL/freeglut.h>

#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Pengaturan Alat Gambar (Kuas)
    glPointSize(10.0);
    glLineWidth(3.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 2. Eksekusi Gambar Titik Besar
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0); // Warna Merah
    glVertex2f(-0.5, 0.5);
    glEnd();

    // 3. Eksekusi Gambar Garis Tebal
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0); // Warna Hijau
    glVertex2f(-0.5, 0.0);
    glVertex2f(0.5, 0.0);
    glEnd();

    // 4. Eksekusi Gambar Poligon (Akan tampil sebagai kerangka saja)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Warna Biru
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, -0.1);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Game FreeGLUT Nelss");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}