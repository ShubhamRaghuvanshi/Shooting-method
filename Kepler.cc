
#include <GL/glut.h>
#include"ode.h" 
#include <iostream>
#include<iomanip>
#include <math.h>

using namespace std;


const float framerate = 1000/60; //milisecond

const int n=256, m=256, scale=3;
float t=0, th=0, dt=0.04;
float xp, yp;
float k1,k2;


float M=1  , L=1, G=1;
float sqa = L/M;

float r0 = 1 , vr0 = 0  , t0=0; 

float d_max = 1.5*r0;


vector<float> x_trace, y_trace;

ode kp;


void init(){
  glClearColor(0,0,0,1);

}


void display(){ 
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
    
//drawing begin

  if( xp < d_max && yp< d_max && kp.y > 0){  
    //trace
    x_trace.push_back(xp);
    y_trace.push_back(yp);
    if(x_trace.size() > 5000){
        x_trace.erase(x_trace.begin());
        y_trace.erase(y_trace.begin() );
    }
    // end trace

//    kp.Euler();  
    kp.RK4();
    kp.x = kp.x +dt;

    k1 = kp.y;
    k2 = kp.y + kp.z*dt;
    k1 = 1.0/(k1*k1);
    k2 = 1.0/(k2*k2);

    th = th + (sqa*dt)/2.0*(k1+k2);
    xp = kp.y * cos(th);
    yp = kp.y * sin(th);

  } //endif 

//display functions
    glPointSize(5*scale); 
    glBegin(GL_POINTS);
        glColor3f(1,1 ,0 );
        glVertex2f(0,0);
    glEnd();
    glPointSize(3*scale); 
    glBegin(GL_POINTS);
        glColor3f(0,0 ,1 );
        glVertex2f(xp,yp);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glColor3f(1, 1, 1);
      for(unsigned int i=0; i<x_trace.size(); i++){
          glVertex2f(x_trace[i],y_trace[i]);
      }
    glEnd();


    glutSwapBuffers();

} //display


void reshape(int w, int h){

  glViewport(0,0,(GLsizei) w, (GLsizei) h );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-d_max, d_max, -d_max , d_max);
  glMatrixMode(GL_MODELVIEW);

}


void timer(int){
    glutPostRedisplay();
    glutTimerFunc(framerate,timer, 0);
}


int main(int argc, char** argv)
{
 
 
  kp.f_i = 4;
  kp.g_i = 0;
  kp.x = t0;
  kp.y = r0;
  kp.z = vr0;
  kp.l = L*L/(M*M);
  kp.k = G/M;
  kp.h = dt;  
  xp = kp.y * cos(th);
  yp = kp.y * sin(th);
  
  float energy = M*vr0*vr0/2.0 + L*L/(2.0*M*r0*r0) - G/r0;   

  cout<<" r(0) = "<<r0<<endl;
  cout<<" vr(0) = "<<vr0<<endl;
  cout<<" L = "<<L<<endl;
  cout<<" Energy = "<<energy<<endl;
  cout<<" Energy for circular orbit = "<<-0.5*M*G*G/(L*L)<<endl;

  
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



















