// verification of focused plane wave.
#include <stdio.h>
#include <math.h>
#include "multi_fbeam.h"
#include "fpw.h"
#include "gauleg.h"

void verification_1(); // using analytical solutions
void verification_2(); // using Fraunhofer diffraction theory

int main()
{
  verification_1();
  verification_2();
  
  return 0;
}

void verification_1()
{
  void fpw_f0(double complex *e,Fpw *fpw);
  void fpw_f1(double complex *e,double z,Fpw *fpw);
  
  Bobj bm;
  double complex e[3],h[3];
  double r[3];
  
  printf("----- verification 1 ------\n");
  
  init_mfb(&bm);
  read_data_mfb_fpw("fpw_verification1.txt",&bm);
  print_data_mfb(&bm);
  setup_mfb(&bm);
    
  r[0]=0.0;
  r[1]=0.0;
  r[2]=0.0;
  calc_mfb_EH(e,h,r,&bm);
  
  printf("Electric field at origin\n");
  printf("Ex=% 15.14e %+15.14e I\n",creal(e[0]),cimag(e[0]));
  printf("Ey=% 15.14e %+15.14e I\n",creal(e[1]),cimag(e[1]));
  printf("Ez=% 15.14e %+15.14e I\n",creal(e[2]),cimag(e[2]));
  printf("Analytical result\n");
  fpw_f0(e,&(bm.bd.fpw[0]));
  printf("Ex=% 15.14e %+15.14e I\n",creal(e[0]),cimag(e[0]));
  printf("Ey=% 15.14e %+15.14e I\n",creal(e[1]),cimag(e[1]));
  printf("Ez=% 15.14e %+15.14e I\n\n",creal(e[2]),cimag(e[2]));
  
  r[2]=1.2;  
  calc_mfb_EH(e,h,r,&bm);
  printf("Electric field at (0,0,%g)\n",r[2]);
  printf("Ex=% 15.14e %+15.14e I\n",creal(e[0]),cimag(e[0]));
  printf("Ey=% 15.14e %+15.14e I\n",creal(e[1]),cimag(e[1]));
  printf("Ez=% 15.14e %+15.14e I\n",creal(e[2]),cimag(e[2]));
  printf("Analytical result\n");
  fpw_f1(e,r[2],&(bm.bd.fpw[0]));
  printf("Ex=% 15.14e %+15.14e I\n",creal(e[0]),cimag(e[0]));
  printf("Ey=% 15.14e %+15.14e I\n",creal(e[1]),cimag(e[1]));
  printf("Ez=% 15.14e %+15.14e I\n",creal(e[2]),cimag(e[2]));
  printf("\n");
  
  free_mfb(&bm);
}

void fpw_f0(double complex *e,Fpw *fpw)
{
  double sin_t,cos_t,ef;
  
  sin_t=fpw->NA/fpw->ni;
  cos_t=sqrt(1.0-sin_t*sin_t);
  ef=M_PI/6.0*(2.0*sin_t*sin_t*cos_t+3.0*sin_t*sin_t-2.0*cos_t+2.0);
  
  e[0]=fpw->data.E0*fpw->data.ex*ef;
  e[1]=fpw->data.E0*fpw->data.ey*ef;
  e[2]=0.0;
}

void fpw_f1(double complex *e,double z,Fpw *fpw)
{
  double complex cf;
  double k,sin_t,cos_t;
  
  k=fpw->data.ki;
  sin_t=fpw->NA/fpw->ni;
  cos_t=sqrt(1.0-sin_t*sin_t);

  if(z==0.0) fpw_f0(e,fpw);
  else{
    cf=M_PI/(pow(k,3)*pow(z,3))*(cexp(I*k*cos_t*z)*(I*k*k*z*z*cos_t*(cos_t+1.0)-k*z*(2.0*cos_t+1.0)-2.0*I)
          +cexp(I*k*z)*(-2.0*I*k*k*z*z+3.0*k*z+2.0*I));
  e[0]=fpw->data.E0*fpw->data.ex*cf;
  e[1]=fpw->data.E0*fpw->data.ey*cf;
  e[2]=0.0;
  }
}

void verification_2()
{
  Bobj bm;
  double complex e[3],h[3];
  double r[3],R,epsilon,mu,cc,tu,ts,U,S;
  int i,j;
  
  printf("----- verification 2 ------\n");
  
  init_mfb(&bm);
  read_data_mfb_fpw("fpw_verification2.txt",&bm);
  print_data_mfb(&bm);
  setup_mfb(&bm);
  
  R=0.60983494563325*bm.bd.fpw[0].lambda0/(bm.bd.fpw[0].NA); // radius of beam spot ( radius of airy disk )
  epsilon=bm.bd.fpw[0].ni*bm.bd.fpw[0].ni; // permittivity
  mu=1.0; // permeability
  cc=1.0/bm.bd.fpw[0].ni; // speed of light

  int nc=80;
  double xt[nc];
  double wt[nc];
  double xr[nc];
  double wr[nc];
  
  gauleg(0.0,2.0*M_PI,xt,wt,nc); // circumferential
  gauleg(0.0,R,xr,wr,nc); // radial

  r[2]=0.0;
  U=0.0;
  S=0.0;
  for(i=0;i<nc;i++){//radial
    tu=0.0;
    ts=0.0;
    for(j=0;j<nc;j++){//circumferential
      r[0]=xr[i]*cos(xt[j]);
      r[1]=xr[i]*sin(xt[j]);
      calc_mfb_EH(e,h,r,&bm);
      tu+=creal( epsilon*(e[0]*conj(e[0])+e[1]*conj(e[1])+e[2]*conj(e[2]) )
                     +mu*(h[0]*conj(h[0])+h[1]*conj(h[1])+h[2]*conj(h[2]) ))*wt[j];
      ts+=creal(e[0]*conj(h[1])-e[1]*conj(h[0]))*wt[j];
    }
    U+=tu*xr[i]*wr[i];
    S+=ts*xr[i]*wr[i];
  }
  
  printf("P_airy/P_total = 0.8378 ( Fraunhofer diffraction theory )\n");
  printf("Pu = %15.14g, Pu/P = %g\n",0.25*cc*U,0.25*cc*U/bm.bd.fpw[0].power);
  printf("Ps = %15.14g, Ps/P = %g\n",0.5*S,0.5*S/bm.bd.fpw[0].power);  
  
  free_mfb(&bm);
}
