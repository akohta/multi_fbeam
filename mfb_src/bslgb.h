#if !defined BSLGB_H
#define BSLGB_H

#include <complex.h>

typedef struct bessel_lgb_data_t{
  double ki;              // wave number 
  double E0;              // power coefficient
  double complex ex,ey;   // normalized polarization coefficient
  double complex hx,hy;   // normalized polarization coefficient
  double cos_t,sin_t;     // cos(theta),sin(theta)
  double cos_p,sin_p;     // cos(phi),sin(phi),theta,phi:rotation parameter
  double ct,st;           // cos(theta_d),sin(theta_d),theta_d:deflection angle
  // trapezoidal data
  double *cp,*sp;
  double complex *ph_p;    // phase data
}BsLGbD;

typedef struct bessel_lgb_t{
  double lambda0;          // wavelength of plane wave in vacuum [m]
  double ni;               // reflactive index of surrounding
  double d_angle;          // deflection angle [rad] (axicon prism:=arcsin(n_axi/ni*sin(angle_axi))-angle_axi)
  double power;            // input beam power [W/m^2]
  double complex e0x;      // x-component of polarization coefficient include phase
  double complex e0y;      // y-component of polarization coefficient include phase
  double fx,fy,fz;         // translation vector (fx,fy,fz)
  double theta,phi;        // rotation paramter 
  int    lg_m;             // mode number for spiral phase modulation 
  BsLGbD data;
}BsLGb;

void print_data_bslgb(BsLGb *bsb);
void print_data_bslgb_mksa(BsLGb *bsb);
void setup_BsLGb(BsLGb *bsb);  // calculate coefficient and memory allocation 
void free_BsLGb(BsLGb *bsb);   // memory free 

void calc_bslgb_EH(double _Complex *e,double _Complex *h,double *x,BsLGb *bsb);
void calc_bslgb_EH_dv(double complex *e,double complex *h,double complex *dedv,double complex *dhdv,double *x,double *v,BsLGb *bsb);
// directional devirative ( define : df/dv=df/dx v_x + df/dy v_y + df/fz v_z )
// dedv[0]=dE_x/dv, dedv[1]=dE_y/dv, dedv[2]=dE_z/dv, dhdv[0]=dH_x/dv, dhdv[1]=dH_y/dv, dhdv[2]=dH_z/dv

#endif
