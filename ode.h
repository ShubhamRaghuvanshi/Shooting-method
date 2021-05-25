#ifndef ODE_H
#define ODE_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class ode{



  public:

        int f_i, g_i, order,  method;                
        double a, b, h;

        long int nop ;
  
        double k1, k2, k3, k4 ;
        double l1, l2, l3, l4 ;  

        double x , y, z;

        double k=-1, l=0, m=0;
 
        ode();        
        ode(int ordr,  int f_indx, int g_indx,  int mth, double A, double B, double H, double y0, double z0); 
        void reset(int mth, double A, double B, double H, double y0, double z0);
        
        void Euler();
  
        
        void Heun();
        void RK4();

        void Euler1();
        void Heun1();
        void RK41();

        double f(double x, double y, double z);
        double g(double x, double y, double z);


        void evolve();
        void write();
        void Shoot2(int f_indx, int mth, double H, double x1, double y1, double x2, double y2, double y11, double y12,  double err )  ;    
        void ShootEnergy(int f_indx, int mth, double H, double x1, double y1, double x2, double y2, double z1, double e1, double e2, double err );

        ~ode();
        
};

#endif




















