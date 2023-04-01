#include <GL/glut.h>
#include <ctime>

static int x0, x1, y0, y1;

bool rasterizar = false;

void algoritmoBresenham(int x0, int x1, int y0, int y1) {

	int dX = x1 - x0, dY = y1 - y0, ix = 1, iy = 1, e, x, y, i;

	if (dX < 0) {
      ix = -ix;
   }

	if (dY < 0) {
      iy = -iy;
   }

	dX = abs(dX);
	dY = abs(dY);	

	x = x0;
	y = y0;

	if (dX > dY) {
		e = (dY << 1) - dX;
		glBegin(GL_POINTS);
         for (i = 0; i < dX; i++) {
            glVertex2i(x,y);

            if (e < 0) {
               e += dY << 1;
            } 
            else {
               y += iy;
               e += (dY - dX) << 1;
            }

            x += ix;
         }
		glEnd();
	} 
   else {
		e = (dX << 1) - dY;
		glBegin(GL_POINTS);

         for (i = 0; i < dY; i++) {
            glVertex2i(x,y);

            if (e < 0) {
               e += dX << 1;
            }
            else {
               x += ix;
               e += (dX - dY) << 1;
            }
            y += iy;
         }
      glEnd();
	}
}

void display(void) {
   glColor3f(0.0, 1.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, 500.0, 0.0, 500.0);

   srand(time(NULL));
	x0 = rand() % 500;
	x1 = rand() % 500;
	y0 = rand() % 500; 
	y1 = rand() % 500;
	
   if (rasterizar) {
	   algoritmoBresenham(x0, x1, y0, y1);
   }

   glFlush();
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
        case 'e':
            if(!rasterizar) {
                rasterizar = true;
            }
            else {
                rasterizar = false;
            }
            glutPostRedisplay();
        default:
            break;
   }
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);   
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("EP04 - Vitor Melo");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}