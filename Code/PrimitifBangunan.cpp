#include <GL/glut.h>
#include <math.h>

/*
 * Sistem koordinat dibuat seperti koordinat gambar:
 * (0,0) di kiri-atas, (600,650) di kanan-bawah.
 * Jadi nilai Y makin besar = makin ke bawah.
 * TINGGI dinaikkan dari 560 jadi 650 supaya muat dasaran + tangga.
 */
#define LEBAR 600
#define TINGGI 650

/* ================== WARNA ================== */
void warnaMerah() { glColor3f(0.91f, 0.24f, 0.24f); }
void warnaMerahTua() { glColor3f(0.65f, 0.12f, 0.12f); }
void warnaBayangan() { glColor3f(0.27f, 0.15f, 0.18f); }
void warnaDinding() { glColor3f(0.33f, 0.33f, 0.36f); }
void warnaKaca() { glColor3f(0.47f, 0.56f, 0.62f); }

/* warna batu (dasaran & tangga) */
void warnaBatu() { glColor3f(0.62f, 0.62f, 0.64f); }
void warnaBatuTerang() { glColor3f(0.72f, 0.72f, 0.74f); }
void warnaBatuTua() { glColor3f(0.45f, 0.45f, 0.48f); }
void warnaGarisBatu() { glColor3f(0.28f, 0.28f, 0.31f); }

/* ================== BENTUK DASAR ================== */
void kotak(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void garis(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

/* Jendela: kaca biru-abu dengan bingkai & kisi merah */
void jendela(float x, float y, float w, float h)
{
    warnaKaca();
    kotak(x, y, x + w, y + h);

    warnaMerah();
    glLineWidth(2.0f);
    /* bingkai */
    garis(x, y, x + w, y);
    garis(x, y + h, x + w, y + h);
    garis(x, y, x, y + h);
    garis(x + w, y, x + w, y + h);
    /* kisi tengah */
    garis(x + w / 2, y, x + w / 2, y + h);
    garis(x, y + h / 2, x + w, y + h / 2);
}

/* ================== DASARAN BATU & TANGGA ================== */
/*
 * Susunan batu bata/batu kali: tiap baris digeser setengah batu
 * tBaris : tinggi satu baris batu
 * lBatu  : lebar satu batu
 */
void susunBatu(float x1, float y1, float x2, float y2, float tBaris, float lBatu)
{
    float x, y;
    int baris = 0;

    warnaBatu();
    kotak(x1, y1, x2, y2);

    warnaGarisBatu();
    glLineWidth(1.5f);

    /* garis mendatar antar baris */
    for (y = y1 + tBaris; y < y2 - 0.1f; y += tBaris)
        garis(x1, y, x2, y);

    /* garis tegak, tiap baris digeser selang-seling */
    for (y = y1; y < y2 - 0.1f; y += tBaris, baris++)
    {
        float yb = y + tBaris;
        if (yb > y2)
            yb = y2;
        for (x = x1 + ((baris % 2) ? lBatu / 2 : lBatu); x < x2 - 0.1f; x += lBatu)
            garis(x, y, x, yb);
    }

    /* garis tepi */
    glLineWidth(2.0f);
    garis(x1, y1, x2, y1);
    garis(x1, y2, x2, y2);
    garis(x1, y1, x1, y2);
    garis(x2, y1, x2, y2);
}

/* Tangga: anak tangga selang-seling terang/gelap + pipi tangga di kiri-kanan */
void tangga(float cx, float yAtas, float yBawah, float setengahW, int jumlah)
{
    int i;
    float t = (yBawah - yAtas) / jumlah;

    /* anak tangga */
    for (i = 0; i < jumlah; i++)
    {
        float y0 = yAtas + i * t;
        if (i % 2 == 0)
            warnaBatuTerang();
        else
            warnaBatu();
        kotak(cx - setengahW, y0, cx + setengahW, y0 + t);

        warnaGarisBatu();
        glLineWidth(2.0f);
        garis(cx - setengahW, y0 + t, cx + setengahW, y0 + t);
    }

    /* pipi tangga kiri (sedikit melebar ke bawah) */
    warnaBatuTua();
    glBegin(GL_QUADS);
    glVertex2f(cx - setengahW - 12, yAtas);
    glVertex2f(cx - setengahW, yAtas);
    glVertex2f(cx - setengahW, yBawah);
    glVertex2f(cx - setengahW - 20, yBawah);
    glEnd();

    /* pipi tangga kanan */
    glBegin(GL_QUADS);
    glVertex2f(cx + setengahW, yAtas);
    glVertex2f(cx + setengahW + 12, yAtas);
    glVertex2f(cx + setengahW + 20, yBawah);
    glVertex2f(cx + setengahW, yBawah);
    glEnd();

    /* garis tepi pipi tangga */
    warnaGarisBatu();
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx - setengahW - 12, yAtas);
    glVertex2f(cx - setengahW, yAtas);
    glVertex2f(cx - setengahW, yBawah);
    glVertex2f(cx - setengahW - 20, yBawah);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx + setengahW, yAtas);
    glVertex2f(cx + setengahW + 12, yAtas);
    glVertex2f(cx + setengahW + 20, yBawah);
    glVertex2f(cx + setengahW, yBawah);
    glEnd();
}

void dasaran()
{
    /* tingkat bawah (lebih lebar) */
    susunBatu(50, 580, 550, 612, 10.7f, 34);

    /* tingkat atas */
    susunBatu(70, 550, 530, 580, 10.0f, 34);

    /* list/bibir dasaran di atas tingkat atas */
    warnaBatuTua();
    kotak(66, 550, 534, 557);
    warnaGarisBatu();
    glLineWidth(2.0f);
    garis(66, 557, 534, 557);

    /* tangga di depan pintu utama, turun sampai ke tanah */
    tangga(300, 557, 628, 42, 8);
}

/* ================== ATAP MELENGKUNG ================== */
/*
 * cx      : titik tengah horizontal atap
 * atasY   : posisi Y bagian atas atap
 * atasW   : setengah lebar bagian atas atap
 * W       : setengah lebar atap sampai ujung (teritisan)
 * ujungY  : posisi Y ujung atap
 * naik    : seberapa tinggi ujung atap melengkung ke atas
 */
float sisiAtas(float x, float cx, float atasY, float atasW,
               float W, float ujungY, float naik)
{
    float d = fabsf(x - cx);
    float a = d / W;
    float y;

    if (d <= atasW)
    {
        y = atasY;
    }
    else
    {
        /* lengkung: curam di atas, landai di bawah */
        float u = (d - atasW) / (W - atasW);
        y = atasY + (ujungY - atasY) * (1.0f - (1.0f - u) * (1.0f - u));
    }
    return y - naik * powf(a, 8.0f); /* ujung melengkung ke atas */
}

float sisiBawah(float x, float cx, float W, float ujungY, float naik)
{
    float a = fabsf(x - cx) / W;
    return ujungY + 3.0f + 6.0f * (1.0f - a * a) - naik * powf(a, 8.0f);
}

void atap(float cx, float atasY, float atasW, float W, float ujungY, float naik)
{
    const int N = 150;
    int i;

    /* 1. Bayangan gelap di bawah atap */
    warnaBayangan();
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= N; i++)
    {
        float x = cx - W + (2.0f * W) * i / N;
        glVertex2f(x, sisiAtas(x, cx, atasY, atasW, W, ujungY, naik));
        glVertex2f(x, sisiBawah(x, cx, W, ujungY, naik) + 8.0f);
    }
    glEnd();

    /* 2. Atap merah */
    warnaMerah();
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= N; i++)
    {
        float x = cx - W + (2.0f * W) * i / N;
        glVertex2f(x, sisiAtas(x, cx, atasY, atasW, W, ujungY, naik));
        glVertex2f(x, sisiBawah(x, cx, W, ujungY, naik));
    }
    glEnd();
}

/* ================== LANTAI ================== */
/* Lantai atas (lantai 2 & 3): 4 jendela dengan tiang merah di antaranya */
void lantaiAtas(float x1, float x2, float y1, float y2)
{
    float tiangX[5] = {187, 243, 299, 355, 411};
    int i;

    warnaDinding();
    kotak(x1, y1, x2, y2);

    /* tiang merah tipis */
    warnaMerah();
    for (i = 0; i < 5; i++)
        kotak(tiangX[i] - 3, y1, tiangX[i] + 3, y2);

    /* 4 jendela di antara tiang (dilebarkan: 42 -> 46) */
    for (i = 0; i < 4; i++)
        jendela(tiangX[i] + 5, y1 + 8, 46, (y2 - y1) - 14);
}

void lantai1()
{
    float tiang[6] = {95, 165, 235, 365, 435, 505};
    int i;

    /* dinding (dilebarkan sampai tiang paling luar) */
    warnaDinding();
    kotak(95, 440, 505, 550);

    /* jendela diperbesar: 34x72 -> 50x82 */
    jendela(105, 463, 50, 82);
    jendela(175, 463, 50, 82);
    jendela(375, 463, 50, 82);
    jendela(445, 463, 50, 82);

    /* tiang merah */
    warnaMerah();
    for (i = 0; i < 6; i++)
        kotak(tiang[i] - 4, 440, tiang[i] + 4, 550);

    /* pintu utama */
    warnaMerah();
    kotak(268, 468, 332, 550);
    warnaMerahTua();
    glLineWidth(3.0f);
    garis(268, 468, 332, 468);
    garis(268, 468, 268, 550);
    garis(332, 468, 332, 550);
    garis(300, 468, 300, 550);
    garis(268, 495, 332, 495);
}

/* ================== PAGODA ================== */
void drawPagoda()
{
    /* --- Dasaran batu + tangga (paling belakang/bawah) --- */
    dasaran();

    /* --- Dinding & tiang (digambar dulu, nanti tertutup atap) --- */
    lantai1();

    /* tiang luar lantai 2 */
    warnaMerah();
    kotak(136, 345, 144, 405);
    kotak(456, 345, 464, 405);

    lantaiAtas(165, 435, 345, 405); /* lantai 2 */
    lantaiAtas(170, 430, 232, 295); /* lantai 3 */

    /* --- Atap dari bawah ke atas --- */
    atap(300, 398, 170, 295, 445, 10); /* atap lantai 1 (paling lebar) */
    atap(300, 292, 135, 226, 336, 8);  /* atap lantai 2 */
    atap(300, 180, 140, 228, 225, 8);  /* atap lantai 3 */
    atap(300, 80, 14, 176, 168, 6);    /* atap puncak */

    /* --- Puncak / menara runcing --- */
    warnaBayangan();
    kotak(284, 72, 316, 81);

    warnaMerah();
    glBegin(GL_TRIANGLES);
    glVertex2f(300, 8);
    glVertex2f(291, 73);
    glVertex2f(309, 73);
    glEnd();
}

/* ================== GLUT ================== */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawPagoda();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* sumbu Y dibalik agar (0,0) di kiri-atas seperti gambar */
    gluOrtho2D(0, LEBAR, TINGGI, 0);
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); /* latar putih */
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LEBAR, TINGGI);
    glutCreateWindow("Ilustrasi Pagoda - FreeGLUT");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}