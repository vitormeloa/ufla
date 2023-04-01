#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

// desenha as paredes
void drawWalls(){
    glBegin(GL_LINES);
    glVertex2d(0.85,-0.5);
    glVertex2d(0.85,0.85);
    glVertex2d(-0.85,0.85);
    glVertex2d(0.85,0.85);
    glVertex2d(-0.85,0.85);
    glVertex2d(-0.85,-0.85);
    glVertex2d(0.85,-0.85);
    glVertex2d(-0.85,-0.85);
    glVertex2d(0.85,-0.85);
    glVertex2d(0.85,-0.8);
    glVertex2d(0.85,-0.8);
    glVertex2d(0.45,-0.6);

    glEnd();
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
    drawCloset();
    drawMobile();
    drawBedTable();
    glFlush();
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  //background color
}



int main(int argc, char* argv[])
{
    // iniciando GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Cria uma janela com o titulo especificado
    glutCreateWindow("Meu quarto");

    glutDisplayFunc(RenderScene);

    // Executa a inicializacao de parametros de exibicao
    SetupRC();

    // Escrever informacoes sobre a versao de OpenGL em uso porque pode ser util saber.
    std::cout   << "Usando OpenGL '" << glGetString(GL_VERSION) << "' implementado por '" << glGetString(GL_VENDOR)
                << "' em arquitetura '" << glGetString(GL_RENDERER)
                << std::endl;

    // Entra no loop de tratamento de eventos da GLUT
    glutMainLoop();
    return 0;
}
