
 
#include <GL/glut.h>
#include"ode.h" 
#include <iostream>
#include<iomanip>
#include <math.h>

using namespace std;

const float framerate = 1000/3; //milisecond

const int n=256, m=256, scale=3;

float d_max = 5;



ode ko;

int ordr=2, findex=0, gindex=0,  mthd=3;

float x1=0, y1 =0, x2=3,  y2 =0, z1 =1, e1=0, e2= -30, h=0.1, err = 0.001;

int nop  = (x2-x1)/h +1;

int itr=0;


void init(){
  glClearColor(0,0,0,1);

}


void display(){ 
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
    
//drawing begin


  glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    for(int i=0; i<nop-1; i++){
        glVertex2f(x_trace[i + (nop-1)*itr ],y_trace[i + (nop-1)*itr]);
    }
  glEnd();
  itr++;


    glutSwapBuffers();

} //display


void reshape(int w, int h){

  glViewport(0,0,(GLsizei) w, (GLsizei) h );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(x1, x2, -d_max , d_max);
  glMatrixMode(GL_MODELVIEW);

}


void timer(int){
    glutPostRedisplay();
    glutTimerFunc(framerate,timer, 0);
}


int main(int argc, char** argv)
{
 
  ko.ShootEnergy(findex, mthd, h, x1, y1, x2, y2, z1, e1, e2, err );

  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   
  glutInitWindowPosition(20, 20);
  glutInitWindowSize(n*scale, m*scale );
  glutCreateWindow("Hello world!");

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
//   glClearColor(1.0,1.0,0.0,0.0);
  

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0,timer,0);    
  
  init();
  glutMainLoop();


    return 0;
}






















































