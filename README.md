# multi_fb
This is the electromagnetic field analysis program for focused beams.
This program can analyze plane wave, focused plane wave, focused radial-azimuthal polarization beam.
In additon, spiral phase modulated beam ( like a Laguerre Gaussian beam ), and Bessel beam can be analyzed. 
This program also supports superposition of these beams. The analysis method used here based on Fourier optics.

## Formulae
Electromagnetic wave is assumed monochromatic wave. 
The surroundings is assumed nonmagnetic.  
The elementary formula is <img src="https://latex.codecogs.com/gif.latex?u(\mathbf{r},t)=u(\mathbf{r})\exp(-i{\omega}t)">.    
The time related complex exponential is dropped form all subsequent expressions.  
Z-axis is selected as optic axis.

- Plane wave  

  <img src="https://latex.codecogs.com/gif.latex?\mathbf{E}(x,y,z)=E_0\mathbf{e}_0\exp(ik_zz)">,  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{H}(x,y,z)=H_0\mathbf{h}_0\exp(ik_zz)">,  
  <img src="https://latex.codecogs.com/gif.latex?E_0=\sqrt{2ZS}">,  
  <img src="https://latex.codecogs.com/gif.latex?H_0=\frac{E_0}{Z}">,  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{h}_0=\left(-e_{0y},e_{0x},0\right)">.
  
  <img src="https://latex.codecogs.com/gif.latex?E_0"> is a power coefficient.
  <img src="https://latex.codecogs.com/gif.latex?Z"> is a wave impedance.
  <img src="https://latex.codecogs.com/gif.latex?S"> is a power per unit square metre.  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_0"> is a polarization coefficient include initial phase,
  <img src="https://latex.codecogs.com/gif.latex?|\mathbf{e}_0|=1">. For example   
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_0=(1,0,0)"> for x polarization,
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_0=(0,1,0)"> for y polarization,
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_0=\left(\frac{1}{\sqrt{2}},\pm\frac{i}{\sqrt{2}},0\right)"> for circular polarization.  


- Focused plane wave  

  <img src="https://latex.codecogs.com/gif.latex?\mathbf{E}(x,y,z)=E_0\int\!\!\!\int_{\Omega}\mathbf{e}(\theta,\phi)\exp\left(ik(x\sin\theta\cos\phi+y\sin\theta\sin\phi+z\cos\theta)\right)\sin\theta\,d(\sin\theta)d\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?\Omega=\left\{(\sin\theta,\phi):0\le\sin\theta\le\frac{\mathrm{NA}}{n},-\pi<\phi\le\pi\right\}">,  
  <img src="https://latex.codecogs.com/gif.latex?e_{x}(\theta,\phi)=e_{px}(\sin^2\phi+\cos\theta\cos^2\phi)+e_{py}\sin\phi\cos\phi(\cos\theta-1)">,  
  <img src="https://latex.codecogs.com/gif.latex?e_{y}(\theta,\phi)=e_{px}(\sin\phi\cos\phi(\cos\theta-1)+e_{py}(\cos\theta\sin^2\phi+\cos^2\phi)">,  
  <img src="https://latex.codecogs.com/gif.latex?e_{z}(\theta,\phi)=-e_{px}\sin\theta\cos\phi-e_{py}\sin\theta\sin\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?E_0=\sqrt{2ZP}\frac{1}{\lambda}">,  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_p=\sqrt{\frac{1}{\pi}}\frac{n}{\mathrm{NA}}\mathbf{p}_f">.  
  <img src="https://latex.codecogs.com/gif.latex?P"> is a power passing through the plane orthogonal to z-axis, or passing through the pupil plane.
  <img src="https://latex.codecogs.com/gif.latex?\lambda"> is a wavelength.  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_p"> is a normalized coefficient,
  <img src="https://latex.codecogs.com/gif.latex?\mathrm{NA}"> is a numerical aperture, 
  <img src="https://latex.codecogs.com/gif.latex?n"> is a refractive index of surroundings, 
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{p}_f"> is a polarization coefficient incluse initial phase, same as
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_0">.  
  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{H}(x,y,z)=H_0\int\!\!\!\int_{\Omega}\mathbf{h}(\theta,\phi)\exp\left(ik(x\sin\theta\cos\phi+y\sin\theta\sin\phi+z\cos\theta)\right)\sin\theta\,d(\sin\theta)d\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?h_x(\theta,\phi)=e_{px}\sin\phi\cos\phi(\cos\theta-1)-e_{py}(\sin^2\phi+\cos\theta\cos^2\phi)">,  
  <img src="https://latex.codecogs.com/gif.latex?h_y(\theta,\phi)=e_{px}(\cos\theta\sin^2\phi+\cos^2\phi)-e_{py}\sin\phi\cos\phi(\cos\theta-1)">,  
  <img src="https://latex.codecogs.com/gif.latex?h_z(\theta,\phi)=-e_{px}\sin\theta\sin\phi+e_{py}\sin\theta\cos\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?H_0=\frac{E_0}{Z}">.  
  
- Focused plane wave with spiral phase modulation

  <img src="https://latex.codecogs.com/gif.latex?\mathbf{E}(x,y,z)=E_0\int\!\!\!\int_{\Omega}\mathbf{e}(\theta,\phi)\exp\left(ik(x\sin\theta\cos\phi+y\sin\theta\sin\phi+z\cos\theta)+im\phi\right)\sin\theta\,d(\sin\theta)d\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{H}(x,y,z)=H_0\int\!\!\!\int_{\Omega}\mathbf{h}(\theta,\phi)\exp\left(ik(x\sin\theta\cos\phi+y\sin\theta\sin\phi+z\cos\theta)+im\phi\right)\sin\theta\,d(\sin\theta)d\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?m"> is a mode number, must be integer ( m=0 is focused plane wave ).  
  Others are the same as focused plane wave.

- Focused radial-azimuthal polarization beam  

  <img src="https://latex.codecogs.com/gif.latex?\mathbf{E}(x,y,z)=E_0\int\!\!\!\int_{\Omega}\mathbf{e}(\theta,\phi)\exp\left(ik(x\sin\theta\cos\phi+y\sin\theta\sin\phi+z\cos\theta)\right)\sin\theta\,d(\sin\theta)d\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?\Omega=\left\{(\sin\theta,\phi):0\le\sin\theta\le\frac{\mathrm{NA}}{n},-\pi<\phi\le\pi\right\}">,  
  <img src="https://latex.codecogs.com/gif.latex?e_x(\theta,\phi)=e_{vr}\cos\theta\cos\phi-e_{va}\sin\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?e_y(\theta,\phi)=e_{vr}\cos\theta\sin\phi+e_{va}\cos\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?e_z(\theta,\phi)=-e_{vr}\sin\theta">,  
  <img src="https://latex.codecogs.com/gif.latex?E_0=\sqrt{2ZP}\frac{1}{\lambda}">,  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{e}_v=(e_{vr},e_{va})=\sqrt{\frac{1}{\pi}}\frac{n}{\mathrm{NA}}\mathbf{p}_v">.  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{p}_v"> is a polarization coefficient, 
  <img src="https://latex.codecogs.com/gif.latex?|\mathbf{p}_v|=1">. For example  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{p}_v=(1,0)"> for radial-polarization, 
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{p}_v=(0,1)"> for azimuthal-polarization, 
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{p}_v=\left(\frac{1}{\sqrt{2}},\frac{1}{\sqrt{2}}\right)"> for combined-polarization.  
  
  <img src="https://latex.codecogs.com/gif.latex?\mathbf{H}(x,y,z)=H_0\int\!\!\!\int_{\Omega}\mathbf{h}(\theta,\phi)\exp\left(ik(x\sin\theta\cos\phi+y\sin\theta\sin\phi+z\cos\theta)\right)\sin\theta\,d(\sin\theta)d\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?h_x(\theta,\phi)=-e_{va}\cos\theta\cos\phi-e_{vr}\sin\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?h_y(\theta,\phi)=-e_{va}\cos\theta\sin\phi+e_{vr}\cos\phi">,  
  <img src="https://latex.codecogs.com/gif.latex?h_z(\theta,\phi)=e_{va}\sin\theta">,  
  <img src="https://latex.codecogs.com/gif.latex?H_0=\frac{E_0}{Z}">.  

- Bessel beam  

  
