# ImplicitRaytracer
This program renders implicit algebraic surfaces of up to degree by using raytracing. The images are rendered using an X11 environment, as well as being saved to a series of .xwd files. 

Uses a simple equation parser to allow for users to enter their own arbitrary surface equations. Equations are solved by solving the roots of quadratic, cubic, and quartic equations.

The code requires an underlying X11 environment, which can be installed on Ubuntu systems using:
  >sudo  apt-get  install  libx11-dev     
  >sudo  apt-get  install  xorg-dev

The program is compiled by doing:
  >cc renderer.c -lm -lX11
 
 # Examples of surfaces that can be rendered 
 ![alt text](https://i.imgur.com/rlY3oqY.png)
 Tanglecube: x^4-5x^2+y^4-5y^2+z^4-5z^2+11.8=0
 
 ![alt text](https://i.imgur.com/rlY3oqY.png)
 Torus: x^4+2x^2y^2+2x^2z^2-52*x^2+y^4+2y^2z^2+48y^2+z^4-52z^2+575=0
 
  
 ![alt text](https://i.imgur.com/0MUS24b.png)
 Quadrifolia: x^4+y^4+z^4+16*x^2*y^2+16*x^2*z^2+16*y^2*z^2-20*y*x^2-20*y*z^2=0
 
 
 ![alt text](https://i.imgur.com/Mz4zVnI.png)
 Dome-like wheel: x^4-18*x^2+y^4-18*y^2+z^4-18*z^2+3*x^2y^2+3*x^2z^2+3*y^2z^2+6*xyz+70=0
 
 
 ![alt text](https://i.imgur.com/M5MCtnD.png)
 Q2: -x^4+y^4-z^4+4.6666666666*x^2+4.6666666666*y^2*z^2-8.3366*y^2+8.3366*z^2*x^2+4.6666666666*z^2+4.6666666666*x^2*y^2-25.2673*x*y*z+1=0
 
 
 
