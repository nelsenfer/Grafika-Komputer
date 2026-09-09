#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Kotak Merah (Atas Kiri)
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); // Merah
    glVertex2f(-0.8, 0.8);
    glVertex2f(-0.3, 0.8);
    glVertex2f(-0.3, 0.3);
    glVertex2f(-0.8, 0.3);
    glEnd();

    // 2. Segienam Kuning (Atas Kanan)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0); // Kuning
    glVertex2f(0.5, 0.8);
    glVertex2f(0.7, 0.8);
    glVertex2f(0.8, 0.5);
    glVertex2f(0.7, 0.2);
    glVertex2f(0.5, 0.2);
    glVertex2f(0.4, 0.5);
    glEnd();

    // 3. Kotak Hijau (Tengah Kiri)
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // Hijau
    glVertex2f(-0.6, 0.1);
    glVertex2f(-0.1, 0.1);
    glVertex2f(-0.1, -0.4);
    glVertex2f(-0.6, -0.4);
    glEnd();

    // 4. Kotak Gradien Grayscale (Bawah Kiri - Menimpa Hijau)
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(-0.8, -0.3); // Abu Terang
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-0.4, -0.3); // Abu-abu
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.4, -0.7); // Hitam
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-0.8, -0.7); // Putih
    glEnd();

    // 5. Segitiga Biru (Bawah Kanan - Belakang)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Biru
    glVertex2f(0.5, 0.1);
    glVertex2f(0.2, -0.6);
    glVertex2f(0.8, -0.6);
    glEnd();

    // 6. Segitiga Gradien RGB (Bawah Kanan - Depan)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.3, -0.4); // Merah
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.9, -0.4); // Hijau
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.6, -0.9); // Biru
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Game FreeGLUT");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}