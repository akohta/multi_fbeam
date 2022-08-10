// verification of focused Gaussian beam.
#include <stdio.h>
#include <math.h>
#include "multi_fbeam.h"
#include "fgb.h"
#include "gauleg.h"

void verification();

int main()
{
  
  verification();
  
  return 0;
}
  
void verification()
{
  Bobj bm;
  double complex e[3],h[3];
  double r[3],R,ts,S,rpw;
  int i,j;
  
  printf("----- verification of focused Gaussian beam ------\n");
  
  init_mfb(&bm);
  read_data_mfb_fgb("fgb_verification.txt",&bm);
  print_data_mfb(&bm);
  setup_mfb(&bm);
  
  int nc=80;
  double xt[nc];
  double wt[nc];
  double xr[nc];
  double wr[nc];
  
  gauleg(0.0,2.0*M_PI,xt,wt,nc); // circumferential
  
  R=bm.bd.fgb[0].omega0; // set spot radius   
  gauleg(0.0,R,xr,wr,nc); // radial

  r[2]=0.0;
  S=0.0;
  for(i=0;i<nc;i++){//radial
    ts=0.0;
    for(j=0;j<nc;j++){//circumferential
      r[0]=xr[i]*cos(xt[j]);
      r[1]=xr[i]*sin(xt[j]);
      calc_mfb_EH(e,h,r,&bm);
      ts+=creal(e[0]*conj(h[1])-e[1]*conj(h[0]))*wt[j];
    }
    S+=ts*xr[i]*wr[i];
  }
  S*=0.5;
  
  printf("P_spot  : the fraction of power transmitted through the spot\n");
  printf("P_total : the total power (incident beam power)\n\n"); 
  printf("r = omega0 (spot radius = beam waist radius)\n");
  printf("P_spot/P_total = %15.14g (Analytical solution)\n",1.0-exp(-2.0));
  printf("P_spot/P_total = %15.14g (Numerical result)\n\n",S/bm.bd.fgb[0].power);  

  rpw=1.52; // 
  R=bm.bd.fgb[0].omega0*rpw;
  gauleg(0.0,R,xr,wr,nc); // radial

  r[2]=0.0;
  S=0.0;
  for(i=0;i<nc;i++){//radial
    ts=0.0;
    for(j=0;j<nc;j++){//circumferential
      r[0]=xr[i]*cos(xt[j]);
      r[1]=xr[i]*sin(xt[j]);
      calc_mfb_EH(e,h,r,&bm);
      ts+=creal(e[0]*conj(h[1])-e[1]*conj(h[0]))*wt[j];
    }
    S+=ts*xr[i]*wr[i];
  }
  S*=0.5;

  printf("r = %g * omega0\n",rpw);
  printf("P_spot/P_total = %15.14g (Analytical solution)\n",1.0-exp(-2.0*rpw*rpw));
  printf("P_spot/P_total = %15.14g (Numerical result)\n",S/bm.bd.fgb[0].power);  
  
  free_mfb(&bm);
}
