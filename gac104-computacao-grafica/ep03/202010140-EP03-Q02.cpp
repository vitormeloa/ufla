/*
Comandos que utilizei para compilar e executar o programa:

    1: g++ -c -Wall 202010140-EP03-Q02.cpp
    2: g++ 202010140-EP03-Q02.o -lglut -lGLU -lGL -o <nome-do-executavel>
    3: ./<nome-do-executavel>
*/

#include <GL/glut.h>
#include <stdlib.h>

#define GL_DIFFUSE 1.0
#define AMBIENTE 0
#define DIFUSA 1

static int shoulder = 0, elbow = 0, fingerOne = 0, fingerTwo = 0;
int ModoDeIluminacao = AMBIENTE;
int LuzAmbEhMax = 0;

void DefineLuzAMBIENTE(void)
{	
	glDisable(GL_LIGHTING);
	return;
}

void DefineLuzDIFUSA(void)
{
  GLfloat LuzAmbiente[] = {0.24725f, 0.1995f, 0.07f };
  GLfloat LuzAmbienteMAX[] = {1, 1, 1};
  GLfloat LuzDifusa[] = {0.75164f, 0.60648f, 0.22648f, 1.0f };
  GLfloat PosicaoLuz0[] = {3.0f, 3.0f, 0.0f, 1.0f };
  GLfloat PosicaoLuz1[] = {-3.0f, -3.0f, 0.0f, 1.0f };
  GLfloat Especularidade[] = {0,0,0,1 };

  glEnable (GL_COLOR_MATERIAL);

  glEnable(GL_LIGHTING);

   if (LuzAmbEhMax) {
	  glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
   }
   else {
      glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
   }

  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
  glEnable(GL_LIGHT0);

  glEnable(GL_COLOR_MATERIAL);

  glMateriali(GL_FRONT,GL_SHININESS,51);

   if (LuzAmbEhMax) {
	  glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
   }
   else {
      glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
   }

  glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa);
  glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   switch(ModoDeIluminacao)
	{
	case DIFUSA:
			DefineLuzDIFUSA();
			break;
	case AMBIENTE:
			DefineLuzAMBIENTE();
			break;
	}

	glMatrixMode(GL_MODELVIEW);
   glClear (GL_COLOR_BUFFER_BIT);
   
   glPushMatrix();
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) fingerOne, 0.0, 0.0, 0.5);
   glColor3f(0.0, 1.0, 1.0);
   glTranslatef (0.2, 0.2, 0.0);
   glPushMatrix();
   glScalef (0.7, 0.2, 0.1);
   glutSolidCube (0.7);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) fingerTwo, 1.0, 1.0, 1.0);
   glColor3f(1.0, 1.0, 0.0);
   glTranslatef (-1.0, -0.4, 0.0);
   glPushMatrix();
   glScalef (0.7, 0.2, 0.1);
   glutSolidCube (0.7);
   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'w':
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'W':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      case 's':
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
      case 'a': ModoDeIluminacao = AMBIENTE;
            LuzAmbEhMax = 0;
            break;
      case 'd': ModoDeIluminacao = DIFUSA;
            LuzAmbEhMax = 0;
            break;
      case '1': LuzAmbEhMax = !LuzAmbEhMax;
            break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

void arrow_keys (int a_keys, int x, int y)  
{
	switch ( a_keys ) 
	{
	    case GLUT_KEY_DOWN:     
			glutInitWindowSize(800, 800); 
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("EP03-P2-Vitor Melo");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc (arrow_keys);
   glutIdleFunc (display);
   glutMainLoop();
   return 0;
}