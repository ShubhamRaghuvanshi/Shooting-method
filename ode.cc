
#include <iostream>
#include <iomanip> 
#include <fstream>
#include <math.h>
#include <vector>

#include "ode.h"

using namespace std;

//constructor
ode::ode(){
}

//distructor
ode::~ode(){}

//constructor with arguments
ode::ode(int ordr,  int f_indx, int g_indx,  int mth, float A, float B, float H, float y0, float z0 ){
    
    order = ordr;
    f_i = f_indx;
    g_i = g_indx;
    
    method = mth;
    a = A;
    b = B;
    h = H;
    y = y0;
    z = z0;
    x=a;
}


//float k=2, l=-20, m=1, G=1;

float k=2, l=1, m=1, G=1, E= -0.4 ;



float ode::g(float x, float y, float z){

  if(g_i ==0){
    return z;
  }

  else if (g_i ==4 ){
    return (1.0/(z*z));
  }

  
  else{}

  return 0;
}


float ode::f(float x, float y, float z){

  // first order ode with constant coefficients
  if(f_i==0){
 //   cout<<"here"<<a<<endl;
    return (   k*z + l*y + m );   
  }
  else if (f_i ==1){
    return ( x*x - m ); 
  }
  else if (f_i ==2){
    return (x*z*z - y*y);
  }
  else if (f_i == 3){ 
    return (-y +1  );
  }

  else if (f_i == 4){
    return ( 1.0/(y*y*y)  - 1.0/(y*y)) ;
  }    
    
  else{
    return 0;
  }

}

void ode::Euler(){
  k1 = f(x,y,z);
  l1 = g(x,y,z);
  
  z = z + h*k1;
  y = y + h*l1;

}



void ode::Heun(){

  k1 = f(x,y,z);
  l1 = g(x,y,z);
  
  k2 = f(x+h, y+l1*h, z+k1*h );
  l2 = g(x+h, y+l1*h, z+k1*h );

  z = z + h*( k1 + k2   )/2.0;
  y = y + h*( l1 + l2   )/2.0;

}


void ode::RK4(){

  k1 = f(x,y,z);
  l1 = g(x,y,z);

  k2 = f(x+ h/2.0, y + l1*h/2.0, z + k1*h/2.0 );
  l2 = g(x+ h/2.0, y + l1*h/2.0, z + k1*h/2.0 );
  
  k3 = f(x+ h/2.0,y + l2*h/2.0,  z + k2*h/2.0   );
  l3 = g(x+ h/2.0,y + l2*h/2.0,  z + k2*h/2.0   );

  k4 = f(x+h, y+l3*h, z+k3*h ) ; 
  l4 = g(x+h, y+l3*h, z+k3*h ) ; 

  z = z + (k1 + 2.0*k2 + 2.0*k3 + k4)*h/6.0; 
  y = y + (l1 + 2.0*l2 + 2.0*l3 + l4)*h/6.0; 


//cout<<setw(15)<<k1<<setw(15)<<l1<<setw(15)<<k2<<setw(15)<<l2<<endl;
//cout<<setw(15)<<k3<<setw(15)<<l3<<setw(15)<<k4<<setw(15)<<l4<<endl;

}


void ode::Euler1(){
  y = y + h*f(x, y, 0);
}



void ode::Heun1(){
  
  k1 = f(x,y,0);  
  k2 = f(x+h, y + k1*h, 0) ;

  y = y + h*( k1 + k2   )/2.0;
}


void ode::RK41(){
 
  k1 = f(x,y,0);  
  k2 = f(x+ h/2.0, y + k1*h/2.0, 0 );  
  k3 = f(x+ h/2.0,y + k2*h/2.0,  0   );
  k4 = f(x+h, y+k3*h, 0 ) ; 
  y = y + (k1 + 2.0*k2 + 2.0*k3 + k4)*h/6.0; 
}





void ode::evolve(){

  char filename[100];
  sprintf(filename, "./kep_%d_%d_%d_%d.txt",order, f_i, g_i, method );

  ofstream output;
  output.open(filename);


  long int nop = (b-a)/h + 1;

  cout<<setw(15)<<"order : "<<order<<setw(15)<<"method : "<<method<<endl;

  if(order ==1 ){
    
    if(method == 1){
      for(int i=0; i<nop; i++){
        output<<x<<"    "<<y<<endl; 
        Euler1();
        x = x+h;      
      }    
    }  // euler

    else if(method == 2){
      for(int i=0; i<nop; i++){
        output<<x<<"    "<<y<<endl; 
        Heun1();
        x = x+h;      
      }    
    }  // Heun

    else if(method == 3){
      for(int i=0; i<nop; i++){
        output<<x<<"    "<<y<<endl; 
        RK41();
        x = x+h;      
      }    
    }  // Heun
  } // 1st order


  else if(order ==2 ){
    
    if(method == 1){
      for(int i=0; i<nop; i++){
        output<<x<<"    "<<y<<"   "<<z<<endl; 
        Euler();
        x = x+h;      
      }    
    }  // euler

    else if(method == 2){
      for(int i=0; i<nop; i++){
        output<<x<<"    "<<y<<"   "<<z<<endl; 
        Heun();
        x = x+h;      
      }    
    }  // Heun

    else if(method == 3){
      for(int i=0; i<nop; i++){
        output<<x<<"    "<<y<<"   "<<z<<endl; 
        RK4();
        x = x+h;      
      }    
    }  // Heun
  } // 1st order
  
  else{}


  output.close();

 
}//evolve






























