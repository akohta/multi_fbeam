// calculation example for electromagnetic field
#include "mfb_src/multi_fbeam.h"

int main()
{
  Bobj bm;
  double complex e[3],h[3],cet;
  double r[3],t;
  
  init_mfb(&bm);       // initialize
  read_data_mfb(&bm);  // search and read beam datafile
  print_data_mfb(&bm); // print defined beam data
  setup_mfb(&bm);      // memory allocation and calculation of coefficients
  
  r[0]=2.5e-6;  // set x-coordinate
  r[1]=-3.0e-6; // set y-coordinate
  r[2]=10.0e-6; // set z-coordinate
  
  calc_mfb_EH(e,h,r,&bm);
  printf("Returned value r=(% g,% g,% g)\n",r[0],r[1],r[2]);
  printf("Ex=% 15.14e %+15.14e I\n",creal(e[0]),cimag(e[0]));
  printf("Ey=% 15.14e %+15.14e I\n",creal(e[1]),cimag(e[1]));
  printf("Ez=% 15.14e %+15.14e I\n",creal(e[2]),cimag(e[2]));
  printf("Hx=% 15.14e %+15.14e I\n",creal(h[0]),cimag(h[0]));
  printf("Hy=% 15.14e %+15.14e I\n",creal(h[1]),cimag(h[1]));
  printf("Hz=% 15.14e %+15.14e I\n\n",creal(h[2]),cimag(h[2]));
  
  t=1.0e-8; // set time
  cet=cexp(-I*bm.omega*t);
  printf("Real electromagnetic field at t=%g [sec]\n",t);
  printf("Ex=% 15.14e\n",creal(e[0]*cet));
  printf("Ey=% 15.14e\n",creal(e[1]*cet));
  printf("Ez=% 15.14e\n",creal(e[2]*cet));
  printf("Hx=% 15.14e\n",creal(h[0]*cet));
  printf("Hy=% 15.14e\n",creal(h[1]*cet));
  printf("Hz=% 15.14e\n",creal(h[2]*cet));
  
  free_mfb(&bm); // fee allocated memory

  return 0;
}
