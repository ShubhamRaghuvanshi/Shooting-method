
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include"ode.h" 

using namespace std;


int main(){

  int ordr=2, findex=0, gindex=0,  mthd=1;
  float a=0, b=3,  h=0.1, y0 =1, z0=1;
  
  mthd=1;
  ode fo(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  fo.evolve();

  mthd=2;
  ode go(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  go.evolve();

  mthd=3;
  ode ko(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  ko.evolve();


//  float k=-2, l=-5, m=1, G=1;


  ofstream output;
  output.open("y_sodewcc.txt");

  float A =2, B=-20, C=1;


  float y, c1, c2, k1, k2, alp;
  if( A*A + 4.0*B > 0  ){
    alp = sqrt( A*A + 4.0*B);
    c1 = y0 + C/B;
    c2 = 2.0*z0 - (y0 + C/B )*A;
    c2 = c2/alp;  
    k1 = (c1+c2)/2.0;
    k2 = (c1-c2)/2.0;
    
    for(float x=0; x<=b+h/2; x = x+h){
      y = k1*exp( (A + alp)*x/2.0  ) + k2*exp( (A - alp)*x/2.0  ) - C/B;
      output<<x<<"    "<<y<<endl; 
    }
    
  }

  else if( A*A + 4.0*B < 0 ){
   
    alp = sqrt( -( A*A + 4.0*B ) ); 
    k1 = y0 + C/B;
    k2 = 2.0*z0 - A*( k1 );
    k2 = k2/alp;
        
    for(float x=0; x<=b+h/2; x = x+h){
      y = k1*cos( alp*x/2.0 )  + k2*sin( alp*x/2.0 );
      y = y*exp(A*x/2.0)  - C/B;
      output<<x<<"    "<<y<<endl; 
    }

  }
  else{}
  
  output.close();

 
  //plotting


  FILE *gnuplot;
  gnuplot = popen("gnuplot -persist", "w");

  if(gnuplot != NULL){
  
  //Uncomment next two lines to get image of the output
  //  fprintf(gnuplot, "set terminal png size 1600,1200\n" );
  //   fprintf(gnuplot, "set output 'plot10000.png' \n" );

    
    fprintf(gnuplot, "set xlabel 'x with h = %0.2f' \n", h );
    fprintf(gnuplot, "set ylabel 'y' \n" );
    fprintf(gnuplot, "set title 'Solution of D^2y = ADy + By + C, for A = %0.2f, B = %0.2f C = %0.2f with y(0) = %0.2f, Dy(0) = %0.2f'\n", A, B, C, y0, z0  );

   
    fprintf(gnuplot, "plot 'y_sodewcc.txt' using 1:2 w l title 'Exact solution', 'y_2_0_0_3.txt' using 1:2 title 'RK4', 'y_2_0_0_2.txt' using 1:2 title 'Heun', 'y_2_0_0_1.txt' using 1:2 title 'Euler' \n");
    
  } 



  return 0;
}






































