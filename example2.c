// calculation example for electric field intensity distribution 
#include "mfb_src/multi_fbeam.h"

int main()
{
  Bobj bm;
  FILE *fp;
  double complex e[3],h[3];
  double x[3],rang,dr;
  int max,i,j;
  
  init_mfb(&bm);
  read_data_mfb(&bm);
  print_data_mfb(&bm); 
  setup_mfb(&bm);     
  
  max=100;
  rang=4.0*bm.lambda_0;
  dr=rang*2/(double)max;
  
  // x=0 plane
  if((fp=fopen("Ie_yz.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  x[0]=0.0;
  for(i=0;i<max;i++){
    x[1]=-rang+(double)i*dr;
    for(j=0;j<max;j++){
      x[2]=-rang+(double)j*dr;
      calc_mfb_EH(e,h,x,&bm);
      fprintf(fp,"%g %g %15.14e\n",x[1],x[2],creal(e[0]*conj(e[0]))+creal(e[1]*conj(e[1]))+creal(e[2]*conj(e[2])));
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  
  // y=0 plane
  if((fp=fopen("Ie_xz.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  x[1]=0.0;
  for(i=0;i<max;i++){
    x[0]=-rang+(double)i*dr;
    for(j=0;j<max;j++){
      x[2]=-rang+(double)j*dr;
      calc_mfb_EH(e,h,x,&bm);
      fprintf(fp,"%g %g %15.14e\n",x[0],x[2],creal(e[0]*conj(e[0]))+creal(e[1]*conj(e[1]))+creal(e[2]*conj(e[2])));
    }
    fprintf(fp,"\n");
  }
  fclose(fp);

  // z=0 plane  
  if((fp=fopen("Ie_xy.txt","wt"))==NULL){    printf("Can not open the file.\n");    exit(1);  }
  x[2]=0.0;
  for(i=0;i<max;i++){
    x[0]=-rang+(double)i*dr;
    for(j=0;j<max;j++){
      x[1]=-rang+(double)j*dr;
      calc_mfb_EH(e,h,x,&bm);
      fprintf(fp,"%g %g %15.14e\n",x[0],x[1],creal(e[0]*conj(e[0]))+creal(e[1]*conj(e[1]))+creal(e[2]*conj(e[2])));
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  
  free_mfb(&bm);
  return 0;
}
