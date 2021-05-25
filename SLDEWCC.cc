
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include"ode.h" 

using namespace std;


int main(){

  int ordr=2, findex=0, gindex=0,  mthd=1;
  float a=0, b=5,  h=0.1, y0 =0, z0=1;
  float A = 0, B=-1, C=-1;
  
 
  ode fo(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  fo.k = -B;
  fo.l = -A;
  fo.m = -C;

  for(int i=1; i<=3; i++){

    fo.x = a;
    fo.y = y0;
    fo.z = z0;
    fo.method = i;
    fo.write();
  }
  
  
  

  ofstream output;
  output.open("y_exact.txt");


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

  ifstream input1, input2, input3, input4;
  input1.open("y_exact.txt");
  input2.open("y_2_0_1.txt");
  input3.open("y_2_0_2.txt");
  input4.open("y_2_0_3.txt");

  float erk4=0 , eh=0, ee=0, y1, y2, y3, y4, ex , zd;

  while ( !input1.eof() ){
    input1>>ex>>y1;
    input2>>ex>>y2>>zd;
    input3>>ex>>y3>>zd;
    input4>>ex>>y4>>zd;
    if(y1*y1 !=0){
      ee =( y1 - y2)*( y1 - y2)/(y1*y1) + ee;
      eh =( y1 - y3)*( y1 - y3)/(y1*y1) + eh;
      erk4 =( y1 - y4)*( y1 - y4)/(y1*y1) + erk4 ;    
    }
  }
  cout<<"Error in Euler : "<<sqrt(ee)<<endl;
  cout<<"Error in Huen : "<<sqrt(eh)<<endl;
  cout<<"Error in RK4 : "<<sqrt(erk4)<<endl;
 
  input1.close();
  input2.close();
  input3.close();
  input4.close();
 
 
  //plotting


  FILE *gnuplot;
  gnuplot = popen("gnuplot -persist", "w");

  if(gnuplot != NULL){
  
  //Uncomment next two lines to get image of the output
  //  fprintf(gnuplot, "set terminal png size 1600,1200\n" );
  //   fprintf(gnuplot, "set output 'plot10000.png' \n" );

    
    fprintf(gnuplot, "set xlabel 'x with h = %0.2f' \n", h );
    fprintf(gnuplot, "set ylabel 'y' \n" );
    fprintf(gnuplot, "set title 'Solution of D^2y + ADy + By + C =0, for A = %0.2f, B = %0.2f C = %0.2f with y(0) = %0.2f, Dy(0) = %0.2f'\n", fo.l, fo.k, fo.m, y0, z0  );

    fprintf(gnuplot, "plot 'y_exact.txt' using 1:2 w l title 'Exact solution', 'y_2_0_3.txt' using 1:2 title 'RK4', 'y_2_0_2.txt' using 1:2 title 'Heun', 'y_2_0_1.txt' using 1:2 title 'Euler' \n");
    
  } 



  return 0;
}






































