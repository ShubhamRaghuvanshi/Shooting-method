#ifndef ODE_H
#define ODE_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class ode{



  public:

        int f_i, g_i, order,  method;
                
        float a, b, h;
        float k1, k2, k3, k4 ;
        float l1, l2, l3, l4 ;  

        float x , y, z;


        ode();        

        ode(int ordr,  int f_indx, int g_indx,  int mth, float A, float B, float H, float y0, float z0 );
        
        void Euler();
        void Heun();
        void RK4();

        void Euler1();
        void Heun1();
        void RK41();

        float f(float x, float y, float z);
        float g(float x, float y, float z);


        void evolve();
      
      

        ~ode();
        
};

#endif




