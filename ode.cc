
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


ode::ode(int ordr,  int f_indx, int g_indx,  int mth, double A, double B, double H, double y0, double z0){

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
    nop = (b-a)/h + 1;
}


//distructor
ode::~ode(){
}

void ode::reset(int mth, double A, double B, double H, double y0, double z0){
    method = mth;
    a = A;
    b = B;
    h = H;
    y = y0;
    z = z0;
    x=a;
}


double ode::g(double x, double y, double z){

  if(g_i ==0){
    return z;
  }

  else if (g_i ==4 ){
    return (1.0/(z*z));
  }

  
  else{}

  return 0;
}


double ode::f(double x, double y, double z){

  // first order ode with constant coefficients
  if(f_i==0){
 //   cout<<"here"<<a<<endl;
    return (   -l*z - k*y -m );   
  }
  else if (f_i ==1){
    return ( (x*x - k)*y ); 

  }
  else if (f_i ==2){
    return (x*z*z - y*y);
  }
  else if (f_i == 3){ 
    return (-y +1  );
  }

  else if (f_i == 4){
    return ( l/(y*y*y)  - k/(y*y)) ;
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

 // cout<<setw(15)<<x<<setw(15)<<y<<setw(15)<<k<<setw(15)<<z<<setw(15)<<x*x - k <<endl;


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

 // cout<<setw(15)<<"order : "<<order<<setw(15)<<"method : "<<method<<endl;

  if(order ==1 ){
    
    if(method == 1){
      for(int i=0; i<nop; i++){
        Euler1();
        x = x+h;      
      }    
    }  // euler

    else if(method == 2){
      for(int i=0; i<nop; i++){
        Heun1();
        x = x+h;      
      }    
    }  // Heun

    else if(method == 3){
      for(int i=0; i<nop; i++){
        RK41();
        x = x+h;      
      }    
    }  // Heun
  } // 1st order


  else if(order ==2 ){
    
    if(method == 1){
      for(int i=0; i<nop-1; i++){
        Euler();
        x = x+h;      
      }    
    }  // euler

    else if(method == 2){
      for(int i=0; i<nop-1; i++){
        Heun();
        x = x+h;      
      }    
    }  // Heun

    else if(method == 3){
      for(int i=0; i<nop-1; i++){
        RK4();
        x = x+h;      
      }    
    }  // RK4
  } // 1st order
  
  else{}
 
}//evolve


void ode::write(){

  char filename[100]; //order fi m
  sprintf(filename, "y_%d_%d_%d.txt", order, f_i, method  );
  
  ofstream output;
  output.open(filename);


  if(order ==1 ){
    
    if(method == 1){
      for(int i=0; i<nop; i++){
        output<<x<<"      "<<y<<endl;
        Euler1();
        x = x+h;      
      }    
    }  // euler

    else if(method == 2){
      for(int i=0; i<nop; i++){
        output<<x<<"      "<<y<<endl;
        Heun1();
        x = x+h;      
      }    
    }  // Heun

    else if(method == 3){
      for(int i=0; i<nop; i++){
        output<<x<<"      "<<y<<endl;
        RK41();
        x = x+h;      
      }    
    }  // Heun
  } // 1st order


  else if(order ==2 ){
    
    if(method == 1){
      for(int i=0; i<nop; i++){
        output<<x<<"      "<<y<<"   "<<z<<endl;
        Euler();
        x = x+h;      
      }    
    }  // euler

    else if(method == 2){
      for(int i=0; i<nop; i++){
        output<<x<<"      "<<y<<"   "<<z<<endl;
        Heun();
        x = x+h;      
      }    
    }  // Heun

    else if(method == 3){
      for(int i=0; i<nop; i++){
        output<<x<<"      "<<y<<"   "<<z<<endl;
        RK4();
        x = x+h;      
      }    
    }  // RK4
  } // 1st order
  
  else{}
  
  output.close();
 
}//evolve




double secant( double x0, double f0, double x1 , double f1 ){
  return (  x1 - f1*(x1 - x0)/(f1 - f0)   );
}



void ode::Shoot2(int f_indx, int mth, double H, double x1, double y1, double x2, double y2, double z11, double z12,  double err ){

  order = 2;
  f_i = f_indx;
  g_i = 0;

  method = mth;
  a = x1;
  b = x2;
  h = H;
  nop = (b-a)/h + 1;
    
  cout<<setw(15)<<"order : "<<order<<setw(15)<<"method : "<<method<<endl;

  double F1, F2, DF;    

  x = x1;
  y = y1;
  z = z11;
  evolve();
  F1 = y - y2;


  x = x1;
  y = y1;
  z = z12;
  evolve();
  F2 = y - y2;

//cout<<"F1 = "<<F1<<"    F2 = "<<F2<<endl;

  for(int itr=0; itr<10; itr++ ){
    
    if( abs(F2) < err) {break;}
    
    x = x1;
    y = y1;
    z = secant(z11, F1, z12, F2 );

   // cout<<"iteration : "<<itr<<"    "<<z<<endl; 

    evolve();
    
    z11 = z12;
    F1 = F2;
  
    z12 = z;   
    F2 = y - y2;   
           
  } // shoot for z0

  z = z12; 

}  //

 
void ode::ShootEnergy(int f_indx, int mth, double H, double x1, double y1, double x2, double y2, double z1, double e1, double e2, double err ){

  order = 2;
  f_i = f_indx;
  g_i = 0;

  method = mth;
  a = x1;
  b = x2;
  h = H;
  nop = (b-a)/h + 1;
    
  cout<<setw(15)<<"order : "<<order<<setw(15)<<"method : "<<method<<endl;

  double F1, F2, F,  midpoint ;    

  for(int itr=0; itr<100; itr++ ){

    x = x1;
    y = y1;
    z = z1;
    k = e1;
    evolve();
    F1 = y - y2;

    x = x1;
    y = y1;
    z = z1;
    k = e2;
    evolve();
    F2 = y - y2;

    midpoint = (e1+e2)/2.0;
    x = x1;
    y = y1;
    z = z1;
    k = midpoint;
    evolve();
    F = y - y2;

 //   cout<<setprecision(8)<<setw(15)<<itr<<setw(15)<<e1<<setw(15)<<e2<<setw(15)<<F1<<setw(15)<<F2<<setw(15)<<F<<setw(15)<<midpoint<<endl;

    if( (F1>0 && F2>0) || (F1<0 && F2<0) ){
      cout<<"Iteration Cannot converge: No Eigen energy in the given limits "<<endl;
      break;  
    }

    if( (F>0 && F1 >0) || (F <0 && F1 < 0) ) { e1 = midpoint; }
    else if( (F>0 && F2 >0) || (F <0 && F2 < 0) ) { e2 = midpoint; }
    else { cout<<"Neither"<<endl;}

    if(F1 == 0){
      k =e1;
      break;
    }
  
    if(F2 == 0){
      k =e2;
      break;
    }
  
    if(abs(F) < err) {
      cout<<"Energy converged "<<endl;   
      break; 
    } 
  } //itr

    k = midpoint;


}
 
 




























