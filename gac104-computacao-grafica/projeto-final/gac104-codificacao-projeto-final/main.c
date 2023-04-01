#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "chemistry.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>


GLuint textures[2];

Substance *subs;
int nsubs;
Reaction *reacts;
int nreacts;

int w, h;
float mousex, mousey;

float asp;

float bb[2][2] = {};

float bbs[][4] = {
    // copos da mesa
    { -0.31, 0.16, -0.06, -0.34 },
    { -0.75, 0.16, -0.45, -0.34 },

    // copos da prateleira
    { 0.15, 0.81, 0.28, 0.57 },
    { 0.33, 0.82, 0.47, 0.57 },
    { 0.51, 0.82, 0.65, 0.58 },
    { 0.68, 0.84, 0.84, 0.57 },
    { 0.15, 0.51, 0.27, 0.28 },
    { 0.32, 0.51, 0.44, 0.28 },
    { 0.48, 0.50, 0.61, 0.28 },
    { 0.64, 0.51, 0.79, 0.28 },
    { 0.14, 0.24, 0.25, 0.01 },
    { 0.30, 0.24, 0.42, 0.01 },
    { 0.46, 0.24, 0.58, 0.01 },
    { 0.61, 0.24, 0.75, 0.02 },
    { 0.13, -0.00, 0.24, -0.22 },
    { 0.29, -0.00, 0.40, -0.22 },
    { 0.43, -0.00, 0.55, -0.22 },
    { 0.59, -0.00, 0.71, -0.22 },
    { 0.13, -0.25, 0.23, -0.43 },
    { 0.28, -0.24, 0.38, -0.44 },
    { 0.42, -0.25, 0.53, -0.44 },
    { 0.57, -0.24, 0.68, -0.44 },
};
int currentbb = -1;

typedef struct {
    Substance *sub;
    Reaction *react;
    int t;
} Copo;

typedef enum {
    PARADO,
    ENCHENDO,
    MOVENDO_COPO,
    VIRANDO_COPO,
    DESCENDO_COPO
} Estado;

Substance *lastsub = NULL;
Copo copos[2] = {};

Estado estado = PARADO;

int estadot = 0;

// tempo atual da cena
int atualt = 0;

// tempo pausado da cena
int pausadot = 0;

// se a cena está pausada
int pausado = 0;

int difuso = 1, ambiente = 1, specular = 1;

// delta T de um tempo até agora, levando em consideração o tempo pausado
int deltat(int v) {
    return atualt - pausadot - v;
}

// deixa uma variável com o tempo atual levando em consideração o tempo pausado
void setnow(int *v) {
    *v = atualt - pausadot;
}

// limita x até v
int clamp(int x, int v) {
    if (x > v) return v;
    else return x;
}

// desenha um segmento do copo
void copoSegmento(Substance *s1, Substance *s2, float alpha, double t, double r, double ht, double hl, double theta, double *last, double *first, int isFirst) {
    // pura trigonometria
    double x = r * cos(t) + r; // x do segmento
    double z = r * sin(t) + r; // z do segmento
    // y onde o líquido termina e o copo começa
    double ym = hl - (r - r * cos(t)) / tan(-theta - M_PI_2);

    // limita ym para as dimensões do copo
    if (ym < 0) ym = 0;
    else if (ym > ht) ym = ht;

    int empty = !s1 || !s2;
    float color[4];
    if (!empty) {
        // mistura de cores de substância
        for (int i = 0; i < 4; i++) {
            color[i] = s1->color[i] * (1 - alpha) + s2->color[i] * alpha;
        }
    }

    float glass[4] = {1, 1, 1, 0.3};
    if (!isFirst) {
        // base
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glass);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float[]){1.0, 1.0, 1.0, 1.0});
        glBegin(GL_TRIANGLES);
            glVertex3d(x, 0, z);
            glVertex3d(last[0], 0, last[1]);
            glVertex3d(first[0], 0, first[1]);
        glEnd();

        // líquido
        if (!empty) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        }
        glBegin(GL_QUADS);
            glVertex3d(x, 0, z);
            glVertex3d(last[0], 0, last[1]);
            glVertex3d(last[0], last[2], last[1]);
            glVertex3d(x, ym, z);
        glEnd();

        if (!empty && ym > 0) {
            // topo do líquido
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
            glBegin(GL_TRIANGLES);
                glVertex3d(x, ym, z);
                glVertex3d(last[0], last[2], last[1]);
                glVertex3d(first[0], first[2], first[1]);
            glEnd();
        }

        // parte de cima do copo
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glass);
        glBegin(GL_QUADS);
            glVertex3d(x, ym, z);
            glVertex3d(x, ht, z);
            glVertex3d(last[0], ht, last[1]);
            glVertex3d(last[0], last[2], last[1]);
        glEnd();
    } else {
        first[0] = x;
        first[1] = z;
        first[2] = ym;
    }

    last[0] = x;
    last[1] = z;
    last[2] = ym;
}

void copoComSubstanciaMix(Substance *s1, Substance *s2, float alpha, double r, double ht, double hl, double theta, int div) {
    glDisable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (float[]){50});

    double last[3];
    double first[3];
    for (int i = 0; i < div; i++) {
        // parametriza i em t
        double t = 2 * M_PI * i / div;
        copoSegmento(s1, s2, alpha, t, r, ht, hl, theta, last, first, i == 0);
    }
    // desenha o último segmento
    copoSegmento(s1, s2, alpha, 0, r, ht, hl, theta, last, first, 0);
    glEnable(GL_TEXTURE_2D);
}

void copoComSubstancia(Substance *sub, double r, double ht, double hl, double theta, int div) {
    copoComSubstanciaMix(sub, sub, 0, r, ht, hl, theta, div);
}

void desenharPrateleira() {
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1, 1, 1, 1});
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float[]){0, 0, 0, 0});

    glPushMatrix();
    glTranslatef(0, -0.01, 0);
    for (int i = 0; i < 5; i++) {
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(0.2, 0, 0);
            glTexCoord2f(1, 0); glVertex3f(0.2, 0, 1);
            glTexCoord2f(1, 1); glVertex3f(5, 0, 1);
            glTexCoord2f(0, 1); glVertex3f(5, 0, 0);
        glEnd();
        glTranslatef(0, 1, 0);
    }
    glPopMatrix();

    for (int i = 0; i < nsubs; i++) {
        int row = 4 - i / 4;
        int col = 4 - i % 4;

        glPushMatrix();
        glTranslatef(col, row, 0.2);
        copoComSubstancia(&subs[i], 0.3, 0.7, 0.4, 0, 20);
        glPopMatrix();
    }
}

void desenharPerna(int i, int j) {
    
}

void desenharCopos() {
    glTranslatef(0.5, 0.01, 0.25);

    int delta = deltat(estadot);
    float p;

    glPushMatrix();
    switch (estado) {
        case PARADO:
            setnow(&estadot);
            copoComSubstancia(copos[0].sub, 0.1, 0.7, copos[0].sub ? 0.7 : 0, 0, 20);

            break;

        case ENCHENDO:
            delta = clamp(delta, 2000);
            p = delta / 2000.0;
            copoComSubstancia(copos[0].sub, 0.1, 0.7, 0.7 * p, 0, 20);
            if (p >= 1) estado = PARADO;
            break;

        case MOVENDO_COPO:
            delta = clamp(delta, 2000);
            p = delta / 2000.0;
            glTranslatef(0.9 * p, 0.8 * p, 0);
            copoComSubstancia(copos[0].sub, 0.1, 0.7, 0.7, 0, 20);
            if (p >= 1) {
                setnow(&estadot);
                estado = VIRANDO_COPO;
                p = 0;
            }
            break;

        case VIRANDO_COPO:
            delta = clamp(delta, 3000);
            p = delta / 3000.0;
            glTranslatef(0.9 - (p*0.5), 0.8 + (p*0.2), 0);
            glRotatef(-90 * p, 0, 0, 1);
            copoComSubstancia(copos[0].sub, 0.1, 0.7, 0.7, M_PI_2 * p, 20);
            if (p >= 1) {
                setnow(&estadot);
                estado = DESCENDO_COPO;
                if (!copos[1].react) {
                    if (!copos[1].sub) {
                        lastsub = copos[1].sub;
                        copos[1].sub = copos[0].sub;
                    }
                    else {
                        int ridx = findReaction(copos[0].sub, copos[1].sub);
                        lastsub = copos[1].sub;

                        copos[1].sub = NULL;
                        if (ridx != -1) {
                            copos[1].react = &reacts[ridx];
                            setnow(&copos[1].t);
                        }
                    }
                }
                copos[0].sub = NULL;
            }
            break;

        case DESCENDO_COPO:
            delta = clamp(delta, 1000);
            p = delta / 1000.0;
            glTranslatef(0.4*(1-p), 1*(1-p), 0);
            glRotatef(-90 * (1-p), 0, 0, 1);
            copoComSubstancia(copos[0].sub, 0.1, 0.7, 0.7, M_PI_2 * (1-p), 20);
            if (p >= 1) {
                setnow(&estadot);
                estado = PARADO;
            }
            break;
    }

    glPopMatrix();

    glTranslatef(1, 0, 0);
    if (estado == VIRANDO_COPO) {
        if (copos[1].sub == NULL) {
            copoComSubstancia(copos[0].sub, 0.3, 0.7, 0.2 * p, 0, 20);
        } else {
            copoComSubstancia(copos[1].sub, 0.3, 0.7, 0.2 * (1 + p), 0, 20);
        }
    } else if (!copos[1].react) {
        copoComSubstancia(copos[1].sub, 0.3, 0.7, copos[1].sub ? 0.2 : 0, 0, 20);
    } else {
        int s1 = copos[1].react->subs[0];
        int s2 = copos[1].react->subs[1];
        float alpha = (float) deltat(copos[1].t) / copos[1].react->time;
        Substance *result = &subs[copos[1].react->result];
        copoComSubstanciaMix(&subs[s1], result, alpha, 0.3, 0.7, 0.4 - 0.2 * alpha, 0, 20);
        if (alpha >= 1) {
            copos[1].sub = result;
            copos[1].react = NULL;
        }
    }
}

void desenharMesa() {
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){0.6, 0.6, 0.6, 1});
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float[]){0, 0, 0, 0});

    glPushMatrix();
    glTranslatef(0, 2.5, 0);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1); glVertex3f(0, 0, 1);
        glTexCoord2f(1, 1); glVertex3f(2.5, 0, 1);
        glTexCoord2f(1, 0); glVertex3f(2.5, 0, 0);
    glEnd();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            desenharPerna(i, j);
        }
    }

    desenharCopos();

    glPopMatrix();
}

void strokeString(const char *s) {
    for (; *s; s++) {
        if (*s == '\n') {
            glTranslatef(0, 1, 0);
        } else {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
        }
    }
}

void desenharTexto() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(bb[0][0], bb[0][1]);
        glVertex2f(bb[1][0], bb[0][1]);
        glVertex2f(bb[1][0], bb[1][1]);
        glVertex2f(bb[0][0], bb[1][1]);
    glEnd();

    glTranslatef(mousex, mousey, 0);

    float escala = 0.0005;
    glScaled(escala / asp, escala, 1.0);

    glColor3f(1.0, 1.0, 1.0);
    if (currentbb >= 2) {
        int idx = currentbb-2;
        if (idx < nsubs) {
            strokeString(subs[idx].name);
        }
    } else if (currentbb >= 0) {
        char buf[8];
        Copo *c = &copos[currentbb];
        if (!(currentbb == 0 && estado != PARADO)) {
            if (c->react) {
                int *rsubs = c->react->subs;
                glPushMatrix();
                strokeString(subs[rsubs[0]].name);
                strokeString(" + ");
                strokeString(subs[rsubs[1]].name);
                strokeString(" = ");
                strokeString(subs[c->react->result].name);
                strokeString("\n");
                glPopMatrix();

                sprintf(buf, "%.0f%%", (float) deltat(c->t) / c->react->time * 100);
                glPushMatrix();
                glTranslatef(0, 130, 0);
                strokeString(buf);
                glPopMatrix();
            } else if (c->sub) {
                strokeString(c->sub->name);
            }
        }
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void draw() {
    static int ultimot = 0;

    atualt = glutGet(GLUT_ELAPSED_TIME);
    int delta = atualt - ultimot;
    ultimot = atualt;
    if (pausado) pausadot += delta;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    if (ambiente) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, (float[]){0.4, 0.4, 0.4, 1});
    } else {
        glLightfv(GL_LIGHT0, GL_AMBIENT, (float[]){0, 0, 0, 0});
    }
    if (difuso) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, (float[]){1, 1, 1, 1});
    } else {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, (float[]){0, 0, 0, 0});
    }
    if (specular) {
        glLightfv(GL_LIGHT0, GL_SPECULAR, (float[]){1, 1, 1, 1});
    } else {
        glLightfv(GL_LIGHT0, GL_SPECULAR, (float[]){0, 0, 0, 0});
    }
    glLightfv(GL_LIGHT0, GL_POSITION, (float[]){2, 5, 5, 0});

    glPushMatrix();
    glTranslatef(-3.5, 0, 6);
    glColor3d(1, 1, 1);
    desenharPrateleira();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(2, 0, 2.5);
    glColor3d(1, 1, 1);
    desenharMesa();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    desenharTexto();
    glEnable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int nw, int nh) {
    w = nw;
    h = w * 500.0 / 800.0;
    asp = (float) 800.0 / 500.0;
    glutReshapeWindow(w, h);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, asp, 0.01, 5000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 4.1, 0, 2, 3.4, 2, 0, 1, 0);
}

void screenToClip(int x, int y, float *cx, float *cy) {
    *cx = ((float) x / w - 0.5) * 2;
    *cy = -((float) y / h - 0.5) * 2;
}

void mouse(int button, int state, int x, int y) {
    int idx = currentbb - 2;
    if (estado == PARADO) {
            if (idx >= 0 && idx < nsubs) {
                copos[0].sub = &subs[idx];
                estado = ENCHENDO;
            }
            if (currentbb == 0 && copos[0].sub != NULL) {
                estado = MOVENDO_COPO;
            }
    }
}

void move(int x, int y) {
    screenToClip(x, y, &mousex, &mousey);
    currentbb = -1;
    for (int i = 0; i < sizeof(bbs) / sizeof(bbs[0]); i++) {
        if (mousex >= bbs[i][0] &&
            mousex <= bbs[i][2] &&
            mousey >= bbs[i][3] &&
            mousey <= bbs[i][1]
        ) {
            currentbb = i;
            break;
        }
    }
}

void keypress(unsigned char key, int x, int y) {
    float nx, ny;
    screenToClip(x, y, &nx, &ny);
    if (key == '\e') {
        exit(0);
    } else if (key == ' ') {
        pausado = !pausado;
    } else if (key == 'd') {
        difuso = !difuso;
    } else if (key == 'a') {
        ambiente = !ambiente;
    } else if (key == 's') {
        specular = !specular;
    } else if (key == 'r') {
        copos[1].sub = lastsub;
        copos[1].react = NULL;
    } else if (key == '1') {
        copos[1].react = NULL;
        copos[1].sub = NULL;
    } else if (key == '2') {
        copos[0].sub = NULL;
    }
    else if (key == '7') {
        bb[0][0] = nx;
        bb[0][1] = ny;
    } else if (key == '8') {
        bb[1][0] = nx;
        bb[1][1] = ny;
    } else if (key == '9') {
        float tl[2];
        float br[2];
        if (bb[0][0] < bb[1][0]) {
            tl[0] = bb[0][0];
            br[0] = bb[1][0];
        } else {
            tl[0] = bb[1][0];
            br[0] = bb[0][0];
        }

        if (bb[0][1] > bb[1][1]) {
            tl[1] = bb[0][1];
            br[1] = bb[1][1];
        } else {
            tl[1] = bb[1][1];
            br[1] = bb[0][1];
        }

        printf("{ %.2f, %.2f, %.2f, %.2f }\n", tl[0], tl[1], br[0], br[1]);
    }
}

void carregarTextura(const char *name, GLuint t) {
    int x, y, c;
    unsigned char *data = stbi_load(name, &x, &y, &c, 3);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, x, y, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    loadChemistry("quimica.txt");
    getSubstances(&subs, &nsubs);
    getReactions(&reacts, &nreacts);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 500);
    glutCreateWindow("OpenGL");

    glGenTextures(2, textures);
    carregarTextura("metal1.jpg", textures[0]);
    carregarTextura("metal2.jpg", textures[1]);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(0.2, 0.2, 0.2, 0);
    glShadeModel(GL_SMOOTH);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (float[]){0, 0, 0, 0});
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, (float[]){1.0});

    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutKeyboardFunc(keypress);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(move);

    glutMainLoop();
    return 0;
}
