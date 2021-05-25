
 
#include"ode.h" 
#include <iostream>
#include<iomanip>
#include <fstream>
#include <math.h>

using namespace std;


int main(){


  double yy1=1, yy2=0, z1 =0, h=0.001, e1=1.5, e2= 1, err = 0.0001, norm=0; 
  
 // float x1=0, x2=1;
 
  int ordr=2, findex=1, gindex=0,  mthd=3, nop;

//  cout<<"Initial guesses for energy"<<endl;
//  cin>>e1>>e2;
  int par=0;
  cout<<"Enter 1 for even -1 for odd :  ";
  cin>>par;

  if(par == 1){
    yy1 = 1;
    z1 = 0 ;
  }

  else if(par == -1){
    yy1 = 0;
    z1 = 1 ;
  }
  else{
    cout<<"Constructing even solution by default"<<endl;
  }


  cout<<"Initial guess for energy : ";
  cin>>e1;
  e2 = e1;
  double x1= 0 , x2= round(sqrt(e1))+4;
  nop = (x2-x1)/h +1;


  ofstream output;
  char filename[100];
  sprintf(filename, "energyshootsho_%d_%d_%0.2f_%0.2f.txt", findex, mthd, x1, x2);
  output.open(filename);


  // guess initial energies 
  ode guess(2, findex, 0, mthd, x1, x2, h, yy1, z1);
  guess.k = e1;
  guess.evolve();
  
  
  double y21 = guess.y, step = 0.3;

  bool opp=0;
  for(int itr=0; itr<20; itr++){
    guess.reset(mthd, x1, x2, h, yy1, z1);
    guess.k = e2 + double(itr)*step;
    guess.evolve();

  //    cout<<" Initial guess for e1 and e2 : "<<setw(15)<<e1<<setw(15)<<guess.k<<setw(15)<<guess.y<<setw(15)<<y21<<endl; 


    if( (guess.y > 0 && y21 < 0) || (guess.y < 0 && y21 > 0)){
      cout<<" Initial guess for e1 and e2 : "<<setw(15)<<e1<<setw(15)<<guess.k<<setw(15)<<guess.y<<setw(15)<<y21<<endl; 
      opp = 1;
      break; 
    }
  }
  e2 = guess.k;
  if(!opp) { 
    cout<<"Initial guesses not correct"<<endl; 
    cout<<" Initial guess for e1 and e2 : "<<setw(15)<<e1<<setw(15)<<e2<<setw(15)<<guess.y<<setw(15)<<y21<<endl; 
  }

  // shoot for correct energy
  
  ode shoot;

  shoot.ShootEnergy(findex, mthd, h, x1, yy1, x2, yy2, z1, e1, e2, err );

  cout<<"Eigen energy : "<<shoot.k<<"   n : "<<(shoot.k -1)/2<<endl;
  shoot.x = x1;
  shoot.y = yy1;
  shoot.z = z1;
  for(int i=0; i<nop; i++){
    norm  = norm + shoot.y*shoot.y;
    shoot.RK4();
    shoot.x = shoot.x+ h;      
  }    
  norm = sqrt(norm);

  shoot.x = x1;
  shoot.y = yy1;
  shoot.z = z1;
  for(int i=0; i<nop; i++){
    output<<shoot.x<<"       "<<shoot.y/norm<<endl;
    output<<-shoot.x<<"       "<<par*shoot.y/norm<<endl;

    shoot.RK4();
    shoot.x = shoot.x+ h;      
  }    
 
  output.close();


 //plotting

  
  FILE *gnuplot;
  gnuplot = popen("gnuplot -persist", "w");

  if(gnuplot != NULL){
  
  //Uncomment next two lines to get image of the output
  //  fprintf(gnuplot, "set terminal png size 1600,1200\n" );
  //   fprintf(gnuplot, "set output 'plot10000.png' \n" );

    
    fprintf(gnuplot, "set xlabel 'x with h = %0.3f' \n", h );
    fprintf(gnuplot, "set ylabel 'y' \n" );
    fprintf(gnuplot, "set title 'Eigen vector corresponding to the Eigen energy'\n" );

    fprintf(gnuplot, "plot 'energyshootsho_%d_%d_%0.2f_%0.2f.txt' using 1:2 with dots title ' y_{%0.2f} '\n", findex, mthd, x1, x2, (shoot.k -1)/2);
    
  } 

 
    return 0;
}






















































