#include <stdio.h>
#include <math.h>
#include "multi_fbeam.h"

// verification function for directional derivative using central difference
void veri_dderv(Bobj *bm,double *r,double *v);

int main()
{
  Bobj bm;
  double complex e[3],h[3],dedv[3],dhdv[3],cet;
  double r[3],t,v[3],theta,phi;
  
  init_mfb(&bm);           // initialize
  read_data_mfb(&bm);      // search and read beam datafile
  print_data_mfb(&bm);     // print defined beam data
  print_data_mfb_mksa(&bm);// print defined beam data using MKSA system of units
  setup_mfb(&bm);          // memory allocation and calculation of coefficients
  
  r[0]= 2.5; // set x-coordinate
  r[1]=-3.0; // set y-coordinate
  r[2]=10.0; // set z-coordinate
  
  calc_mfb_EH(e,h,r,&bm);
  printf("Electromagnetic field at r=(% g,% g,% g)\n",r[0],r[1],r[2]);
  printf("Ex=% 15.14e %+15.14e I\n",creal(e[0]),cimag(e[0]));
  printf("Ey=% 15.14e %+15.14e I\n",creal(e[1]),cimag(e[1]));
  printf("Ez=% 15.14e %+15.14e I\n",creal(e[2]),cimag(e[2]));
  printf("Hx=% 15.14e %+15.14e I\n",creal(h[0]),cimag(h[0]));
  printf("Hy=% 15.14e %+15.14e I\n",creal(h[1]),cimag(h[1]));
  printf("Hz=% 15.14e %+15.14e I\n",creal(h[2]),cimag(h[2]));
  
  t=0.1; // set time
  cet=cexp(-I*bm.omega*t);
  printf("Real electromagnetic field at r=(% g,% g,% g), t=%g \n",r[0],r[1],r[2],t);
  printf("Ex=% 15.14e\n",creal(e[0]*cet));
  printf("Ey=% 15.14e\n",creal(e[1]*cet));
  printf("Ez=% 15.14e\n",creal(e[2]*cet));
  printf("Hx=% 15.14e\n",creal(h[0]*cet));
  printf("Hy=% 15.14e\n",creal(h[1]*cet));
  printf("Hz=% 15.14e\n\n",creal(h[2]*cet));

  theta=0.3;
  phi=1.2;  // theta,phi are parameter for unit vector v
  v[0]=sin(theta)*cos(phi);
  v[1]=sin(theta)*sin(phi);
  v[2]=cos(theta);
  calc_mfb_EH_dv(e,h,dedv,dhdv,r,v,&bm);
  printf("Directional derivative of electromagnetic field at r=(% g,% g,% g)\n",r[0],r[1],r[2]);
  printf("v=(% g,% g,% g),|v|=1\n",v[0],v[1],v[2]);
  printf("dEx/dv=% 15.14e %+15.14e I\n",creal(dedv[0]),cimag(dedv[0]));
  printf("dEy/dv=% 15.14e %+15.14e I\n",creal(dedv[1]),cimag(dedv[1]));
  printf("dEz/dv=% 15.14e %+15.14e I\n",creal(dedv[2]),cimag(dedv[2]));
  printf("dHx/dv=% 15.14e %+15.14e I\n",creal(dhdv[0]),cimag(dhdv[0]));
  printf("dHy/dv=% 15.14e %+15.14e I\n",creal(dhdv[1]),cimag(dhdv[1]));
  printf("dHz/dv=% 15.14e %+15.14e I\n",creal(dhdv[2]),cimag(dhdv[2]));
  
  veri_dderv(&bm,r,v); // verification function for directinal derivative
  
  free_mfb(&bm); // free allocated memory

  return 0;
}

void veri_dderv(Bobj *bm,double *r,double *v)
{
  double complex e0[3],e1[3],h0[3],h1[3],tz;
  double h,tr[3];  
 
  h=1.0e-7*bm->lambda_0;
  
  tr[0]=r[0]-h*v[0];
  tr[1]=r[1]-h*v[1];
  tr[2]=r[2]-h*v[2];
  calc_mfb_EH(e0,h0,tr,bm);
  
  tr[0]=r[0]+h*v[0];
  tr[1]=r[1]+h*v[1];
  tr[2]=r[2]+h*v[2];
  calc_mfb_EH(e1,h1,tr,bm);
  
  printf("Directional derivative using central difference. h=%g\n",h);
  tz=(e1[0]-e0[0])/(2.0*h);
  printf("dEx/dv=% 15.14e %+15.14e I\n",creal(tz),cimag(tz));
  tz=(e1[1]-e0[1])/(2.0*h);
  printf("dEy/dv=% 15.14e %+15.14e I\n",creal(tz),cimag(tz));
  tz=(e1[2]-e0[2])/(2.0*h);
  printf("dEz/dv=% 15.14e %+15.14e I\n",creal(tz),cimag(tz));
  tz=(h1[0]-h0[0])/(2.0*h);
  printf("dHx/dv=% 15.14e %+15.14e I\n",creal(tz),cimag(tz));
  tz=(h1[1]-h0[1])/(2.0*h);
  printf("dHy/dv=% 15.14e %+15.14e I\n",creal(tz),cimag(tz));
  tz=(h1[2]-h0[2])/(2.0*h);
  printf("dHz/dv=% 15.14e %+15.14e I\n",creal(tz),cimag(tz));
}
