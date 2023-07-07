/**
*   Programa para ilustrar:
*   - Uso da gluLookAt
*   - Pilha de transformacoes
*   - Projecao pespectiva
*   - Interacao com o mouse/teclado
*   - cullFace, frontFace

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>


#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>

#define SCREEN_X 500
#define SCREEN_Y 500
#define SIZE 50

int   polygonMode = 1;

float rx = 0, rz = 0; //parametros de rotacao do objeto.

float abertura = 90.0;
float znear  = 1;
float zfar   = 200;
float aspect = 1;





float height_map[SIZE][SIZE];

void setHM() {
   srand(time(NULL));
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
         height_map[i][j] = rand() % 4;
      }
   }
}

void init()
{

   setHM();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluPerspective(abertura, aspect, znear, zfar);
   glMatrixMode(GL_MODELVIEW);

   glClearColor(0, 0, 0, 1);

   //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glEnable(GL_DEPTH_TEST);
}

//imprime as matrizes da pilha do opengl
void printMatrix(GLenum pname)
{
   GLfloat m[16]; //usado para leitura das matrizes
   glGetFloatv (pname, m);
   int l, c;
   printf("\n\n Matriz = %d", pname);
   for(l=0; l<4; l++)
   {
      printf("\n");
      for(c=0; c<4; c++)
      {
         int pos = l * 4 + c;
          printf(" %.2f", m[pos] );
      }
   }
}



void render_surface() {
   for (int i = 0; i < 50 - 1; i++) {
      for (int j = 0; j < 50 - 1; j++) {
         glBegin(GL_QUADS);
         glVertex3f(i - SIZE/2, height_map[i][j], j - SIZE/2);
         glVertex3f(i + 1 - SIZE/2, height_map[i + 1][j], j - SIZE/2);
         glVertex3f(i + 1 - SIZE/2, height_map[i + 1][j + 1], j + 1 - SIZE/2);
         glVertex3f(i - SIZE/2, height_map[i][j + 1], j + 1 - SIZE/2);
         glEnd();

      }
   }

}

////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   printf("\n%f", abertura);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   //glOrtho(-1,1,-1,1,1,-1);

   printMatrix(GL_PROJECTION_MATRIX);

   gluPerspective(abertura, aspect, znear, zfar);


   printMatrix(GL_MODELVIEW_MATRIX);

   glMatrixMode(GL_MODELVIEW);

   glLoadIdentity( );
   gluLookAt(0, 0, -20,  //from. Posicao onde a camera esta posicionada
             0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
             0, 1, 0); //up. Vetor Up.

   glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
   glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);

   //todos os objetos estao definidos na origem do sistema global fixo
   //e sao transladados para a posicao destino.
   /*glColor3f(1, 1, 1);
   glBegin(GL_POLYGON);
      glVertex3f(-1, 0, 1);
      glVertex3f(1, 0, 1);
      glVertex3f(1, 0, -1);
      glVertex3f(-1, 0, -1);
   glEnd();*/

   //bule 1
   /*glPushMatrix();
      glColor3f(1, 0, 1);
      glTranslated(-0.5, 0.15, 0.5);
      glutWireTeapot(0.2);
   glPopMatrix();

   //bule 2
   glPushMatrix();
      glColor3f(0, 1, 0);
      glTranslated(0.5, 0.15, -0.5);
      glRotated(90, 0, 1, 0);
      glutWireTeapot(0.2);
   glPopMatrix();

   //bule 3
   glColor3f(0, 0, 1);
   glutSolidTeapot(1.2);*/


   // drawing surface
   render_surface();

   glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y)
{
   //printf("%c", key);
   key = tolower(key);
   switch(key)
   {
      case 27:
	     exit(0);
	  break;

      case 'w': //wireframe
         if(polygonMode==1)
		 {
		    polygonMode=0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	     }
		 else
		 {
		    polygonMode=1;
		    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		 }
		break;
      case '+':
           abertura+=1;

   }
}

void MotionFunc(int x, int y)
{
//   float dx, dy;
   //printf("\nX = %d Y = %d", x, y);
   rx = x;
   rz = y;
}

void MouseFunc(int botao, int estado, int x, int y)
{
   //printf("\n%d %d %d %d", botao, estado, x, y);
}

////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
   int  argc=0;
   //char *argv[1] = {"teste"};
   glutInit(&argc, NULL);

   //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowSize (SCREEN_X, SCREEN_Y);
   glutInitWindowPosition (450, 10);
   /* create window */
   glutCreateWindow ("GluLookAt Demo");
   init();
   printf("Digite W para mudar o modo de visualizacao: wireframe/fill");

   glutDisplayFunc(display);
   glutMotionFunc(MotionFunc);
   glutMouseFunc(MouseFunc);
   glutIdleFunc(display);
   glutKeyboardFunc(keyboard);




   glutMainLoop();
   return 0;
}
