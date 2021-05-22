
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include"ode.h" 

using namespace std;


int main(){

  int ordr=2, findex=4, gindex=0,  mthd=1;
  float a=0, b=80,  h=0.1, y0 =1.5, z0=-1;
  
  mthd=1;
  ode fo(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  fo.evolve();


  mthd=2;
  ode go(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  go.evolve();

  mthd=3;
  ode ko(ordr, findex,  gindex,  mthd, a, b, h, y0, z0 );
  ko.evolve();

  
  char filename[100];
  float t,r,th,x,y,dr;

  vector<float> R, T;
  for(int i=1;i<=3;i++){
    
    sprintf(filename, "./kep_2_4_0_%d.txt",i );
    ifstream rth(filename);

    sprintf(filename, "./kepxy_2_4_0_%d.txt",i );
    ofstream xy(filename);
  
    th =0;
    float k1, k2;
    while (!rth.eof()){
      rth>>t>>r>>dr;
      R.push_back(r);
      T.push_back(t);
    }  
     
    for(int j=0; j<T.size()-1; j++){
      x = R[j]*cos(th);
      y = R[j]*sin(th);
      xy<<T[j]<<"      "<<x<<"     "<<y<<endl;
      th = th + h*( 1.0/( R[j]*R[j] )  + 1.0/( R[j+1]*R[j+1] ) )/2.0;
    } 
     
    R.clear();
    T.clear();
    rth.close();
    xy.close();
  }


  //plotting


  FILE *gnuplot;
  gnuplot = popen("gnuplot -persist", "w");

  if(gnuplot != NULL){
  
  //Uncomment next two lines to get image of the output
  //  fprintf(gnuplot, "set terminal png size 1600,1200\n" );
  //   fprintf(gnuplot, "set output 'plot10000.png' \n" );

    
    fprintf(gnuplot, "set xlabel 'x' \n" );
    fprintf(gnuplot, "set ylabel 'y' \n" );

//    fprintf(gnuplot, "set title 'E = %0.2f'\n");

  // fprintf(gnuplot, "plot 'kepxy_2_4_0_3.txt' using 2:3 title 'RK4' \n");
   
   
    fprintf(gnuplot, "plot 'kepxy_2_4_0_3.txt' using 2:3 title 'RK4'  \n");
    
  } 



  return 0;
}






































