#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

GLfloat angle = 0.0f;
GLfloat angleChair = 0.0f;

// desenha as paredes
void drawWalls(){
    glBegin(GL_LINES);
    glVertex2d(0.85,-0.35);
    glVertex2d(0.85,0.85);
    glVertex2d(-0.85,0.85);
    glVertex2d(0.85,0.85);
    glVertex2d(-0.85,0.85);
    glVertex2d(-0.85,-0.85);
    glVertex2d(0.85,-0.85);
    glVertex2d(-0.85,-0.85);
    glVertex2d(0.85,-0.85);
    glVertex2d(0.85,-0.8);
    glEnd();

    glPushMatrix();
    glTranslatef(0.85f,-0.8f,0.0f);
    glRotatef(angle,0.0f,0.0f,1.0f);
    glTranslatef(-0.85f,0.8f,0.0f);

    glBegin(GL_POLYGON);
    glVertex3d(0.85,-0.8,0.0);
    glVertex3d(0.45,-0.6,0.0);
    glVertex3d(0.45,-0.57,0.0);
    glVertex3d(0.85,-0.77,0.0);
    glEnd();
    glPopMatrix();
}

//desenha a cadeira
void drawChair(){
    glPushMatrix();
    glTranslatef(-0.30f,0.5f,0.0f);
    glRotatef(angleChair,0.0f,0.0f,1.0f);
    glTranslatef(0.30f,-0.5f,1.0f);

    glBegin(GL_POLYGON);
    glVertex3d(0.0,0.3,0.0);
    glVertex3d(-0.30,0.3,0.0);
    glVertex3d(-0.30,0.3,0.0);
    glVertex3d(-0.30,0.5,0.0);
    glVertex3d(0.0,0.3,0.0);
    glVertex3d(0.0,0.5,0.0);
    glVertex3d(0.0,0.5,0.0);
    glVertex3d(-0.30,0.5,0.0);
    glEnd();
    glPopMatrix();
}

// desenha a janela
void drawWindow(){
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.85,0.1);
    glVertex2d(-0.85,0.5);
    glVertex2d(-0.8,0.5);
    glVertex2d(-0.8,0.1);
    glEnd();
}

// desenha a cama
void drawBed(){

    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.5,-0.8);
    glVertex2d(-0.5,-0.1);
    glVertex2d(0.1,-0.1);
    glVertex2d(0.1,-0.8);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(-0.45,-0.75,0.0);
    glVertex3f(-0.45,-0.55,0.0);
    glVertex3f(-0.25,-0.55,0.0);
    glVertex3f(-0.25,-0.75,0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(-0.15,-0.75,0.0);
    glVertex3f(-0.15,-0.55,0.0);
    glVertex3f(0.05,-0.55,0.0);
    glVertex3f(0.05,-0.75,0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-0.5,-0.5);
    glVertex2d(0.1,-0.5);
    glEnd();
}

// desenha o guarda-roupas
void drawCloset(){
    glBegin(GL_LINE_LOOP);
    glVertex2d(0.5,-0.3);
    glVertex2d(0.8,-0.3);
    glVertex2d(0.8,0.8);
    glVertex2d(0.5,0.8);
    glEnd();
}

//desenha a cômoda
void drawMobile(){
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.7,0.8);
    glVertex2d(0.1,0.8);
    glVertex2d(0.1,0.6);
    glVertex2d(-0.7,0.6);
    glEnd();
}

//desenha o criado-mudo
void drawBedTable(){
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.8,-0.8);
    glVertex2d(-0.55,-0.8);
    glVertex2d(-0.55,-0.5);
    glVertex2d(-0.8,-0.5);
    glEnd();
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawWalls();
    drawWindow();
    drawBed();
    drawChair();
    drawCloset();
    drawMobile();
    drawBedTable();
    glFlush();
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  //background color
}

void KeyboardOptions(int key, int x, int y)
{
    switch (key) {
      case GLUT_KEY_RIGHT:
          if(angle > -63.0)
          angle -= 3;
          break;
      case GLUT_KEY_LEFT:
          if(angleChair > -90.0)
            angleChair -= 1;
          break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // iniciando GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // cria uma janela com o titulo especificado
    glutCreateWindow("Meu quarto");

    glutSpecialFunc(KeyboardOptions);

    glutDisplayFunc(RenderScene);

    // loop que trata os eventos GLUT
    glutMainLoop();

    return 0;
}
