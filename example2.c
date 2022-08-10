// calculation example for electromagnetic field intensity distribution 
#include <stdio.h>
#include <stdlib.h>
#include "multi_fbeam.h"
#include "my_utils.h"

int main()
{
  Bobj bm;
  FILE *fp1,*fp2;
  double complex e[3],h[3];
  double x[3],rang,dr,*ie,*ih;
  int max,i,j;
  
  init_mfb(&bm);
  read_data_mfb(&bm);
  print_data_mfb(&bm); 
  setup_mfb(&bm);     
  
  max=200;
  rang=4.0*bm.lambda_0;
  dr=rang*2/(double)(max-1);
  
  ie=(double *)m_alloc2(max,sizeof(double),"example2.c,ie");
  ih=(double *)m_alloc2(max,sizeof(double),"example2.c,ih");

  
  // x=0 plane
  if((fp1=fopen("Ie_yz.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  fprintf(fp1,"%s\n","# y z electric_field_intensity");
  if((fp2=fopen("Ih_yz.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  fprintf(fp2,"%s\n","# y z magnetic_field_intensity");
  x[0]=0.0;
  for(i=0;i<max;i++){
    x[1]=-rang+(double)i*dr;
    #pragma omp parallel for schedule(dynamic) firstprivate(x) private(e,h) // omp parallel
    for(j=0;j<max;j++){
      x[2]=-rang+(double)j*dr;
      calc_mfb_EH(e,h,x,&bm);
      ie[j]=creal(e[0]*conj(e[0]))+creal(e[1]*conj(e[1]))+creal(e[2]*conj(e[2]));
      ih[j]=creal(h[0]*conj(h[0]))+creal(h[1]*conj(h[1]))+creal(h[2]*conj(h[2]));
    }
    for(j=0;j<max;j++){
      x[2]=-rang+(double)j*dr;
      fprintf(fp1,"%g %g %15.14e\n",x[1],x[2],ie[j]);
      fprintf(fp2,"%g %g %15.14e\n",x[1],x[2],ih[j]);
    }
    fprintf(fp1,"\n");
    fprintf(fp2,"\n");
  }
  fclose(fp1);
  fclose(fp2);

  // y=0 plane
  if((fp1=fopen("Ie_xz.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  fprintf(fp1,"%s\n","# x z electric_field_intensity");
  if((fp2=fopen("Ih_xz.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  fprintf(fp2,"%s\n","# x z magnetic_field_intensity");
  x[1]=0.0;
  for(i=0;i<max;i++){
    x[0]=-rang+(double)i*dr;
    #pragma omp parallel for schedule(dynamic) firstprivate(x) private(e,h) // omp parallel
    for(j=0;j<max;j++){
      x[2]=-rang+(double)j*dr;
      calc_mfb_EH(e,h,x,&bm);
      ie[j]=creal(e[0]*conj(e[0]))+creal(e[1]*conj(e[1]))+creal(e[2]*conj(e[2]));
      ih[j]=creal(h[0]*conj(h[0]))+creal(h[1]*conj(h[1]))+creal(h[2]*conj(h[2]));
    }// end parallel
    for(j=0;j<max;j++){
      x[2]=-rang+(double)j*dr;
      fprintf(fp1,"%g %g %15.14e\n",x[0],x[2],ie[j]);
      fprintf(fp2,"%g %g %15.14e\n",x[0],x[2],ih[j]);
    }
    fprintf(fp1,"\n");
    fprintf(fp2,"\n");
  }
  fclose(fp1);
  fclose(fp2);

  // z=0 plane  
  if((fp1=fopen("Ie_xy.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  fprintf(fp1,"%s\n","# x y electric_field_intensity");
  if((fp2=fopen("Ih_xy.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  fprintf(fp2,"%s\n","# x y electric_field_intensity");
  x[2]=0.0;
  for(i=0;i<max;i++){
    x[0]=-rang+(double)i*dr;
    #pragma omp parallel for schedule(dynamic) firstprivate(x) private(e,h) // omp parallel
    for(j=0;j<max;j++){
      x[1]=-rang+(double)j*dr;
      calc_mfb_EH(e,h,x,&bm);
      ie[j]=creal(e[0]*conj(e[0]))+creal(e[1]*conj(e[1]))+creal(e[2]*conj(e[2]));
      ih[j]=creal(h[0]*conj(h[0]))+creal(h[1]*conj(h[1]))+creal(h[2]*conj(h[2]));
    }
    for(j=0;j<max;j++){
      x[1]=-rang+(double)j*dr;
      fprintf(fp1,"%g %g %15.14e\n",x[0],x[1],ie[j]);
      fprintf(fp2,"%g %g %15.14e\n",x[0],x[1],ih[j]);
    }
    fprintf(fp1,"\n");
    fprintf(fp2,"\n");
  }
  fclose(fp1);
  fclose(fp2);
  
  printf("intensity plot is finished\n");

  free(ie);
  free(ih);
  free_mfb(&bm);
  return 0;
}
