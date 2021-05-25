
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include"ode.h" 

using namespace std;


int main(){



  int ordr=2, findex=0, gindex=0,  mthd=3;

  float x1=0, x2=1,  h=0.1, y1 =0, y2 =0, z11=1, z12=-1, err = 0.001;
 
  int nop  = (x2-x1)/h +1;
 
  ode ko;

  float norm=0;
  for(int itr=0; itr<10; itr++){
  
    ko.Shoot2(findex, mthd, h, x1, y1, x2, y2, z11, z12, err )  ;    

    ko.x  = x1;
    ko.y  = y1;

    for(int i=0; i<nop; i++){
      norm = norm + ko.y*ko.y;
      ko.RK4();

      ko.x = ko.x + h;


    }
    cout<<"k =    "<<ko.l<<"    norm : "<<norm<<endl;
    if(norm < 0.001) {ko.l = ko.l - 0.1;}
    else {break;}
  } 

   
  char filename[100];
  sprintf(filename, "./shoot_%d_%0.2f_%0.2f_%d.txt", findex, x1, x2, mthd );
  ofstream output;
  output.open(filename);

  ko.x  = x1;
  ko.y  = y1;    
  for(int i=0; i<nop; i++){
    output<<ko.x<<"    "<<ko.y<<endl;
    ko.RK4();
    ko.x = ko.x + h;
  }
    
  output.close(); 

 
  //plotting

/*
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

*/


  return 0;
}






































