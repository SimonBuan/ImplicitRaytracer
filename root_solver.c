#include <stdio.h>
#include <math.h>
#include <complex.h>

int quad(double a, double b, double c, double result[2])
// return number of solutions
{
  int n ;
  double d,ta ;

  // assumption is that a != 0, i.e. we have a genuine quadratic

  d = b*b - 4*a*c ;


  if (d < 0) {
     n = 0 ;  // no REAL solutions (they are complex)
  } else if (d == 0) {
     ta = 2*a ;
     result[0] = -b / ta ;
     n = 1 ;
  } else {
     d = sqrt(d) ;
     ta = 2*a ;
     result[0] = (-b + d) / ta ;
     result[1] = (-b - d) / ta ;
     n = 2 ;
  }

  return n ;
}

void complex_quad(double a, double b, double c, double complex result[2]){
  //solves quadratic equation when we know there are only complex solutions
  double complex d = csqrt(b*b - 4*a*c);

  result[0] = (-b + d)/(2*a);
  result[1] = (-b - d)/(2*a);
}

int cubic(double a, double b, double c, double d, double result[3]){
  //return number of solutions
  double real, imag;
  double b2, c2, d2, b3, c3, b4, b5, c5;
  double x[2], y, z, w[2];
  double complex cw[2], u[2], cresult[3], cz[3], cy[3], cx[3];
  int quad_solutions;
  int num_solutions = 0;

  if(a == 0){
    num_solutions = quad(b, c, d, result);
    return num_solutions;
  }
  
  b2 = b/a; c2 = c/a; d2 = d/a;

  b3 = c2 - (b2*b2)/3;
  c3 = d2 + (b2*b2*b2)/9 - (b2*b2*b2)/27 - (c2*b2)/3;

  b4 = -(b3*b3*b3)/27;

  quad_solutions = quad(1, c3, b4, w);

  if(quad_solutions == 0){
    //no real solutions to the quadratic
    //might still get real solution to the cubic
    complex_quad(1, c3, b4, cw);
    u[0] = -1.0/2 - sqrt(3)/2 * I;
    u[1] = -1.0/2 + sqrt(3)/2 * I;

    cz[0] = cpow(cw[0], 1.0/3);
    cz[1] = cz[0] * u[0];
    cz[2] = cz[0] * u[1];

    cy[0] = cz[0] - b3/(3*cz[0]);
    cy[1] = cz[1] - b3/(3*cz[1]);
    cy[2] = cz[2] - b3/(3*cz[2]);

    cx[0] = cy[0] - b2/3;
    cx[1] = cy[1] - b2/3;
    cx[2] = cy[2] - b2/3;


    for(int i = 0; i < 3; i++){
      if(fabs(cimag(cx[i])) < 0.0001){
        result[num_solutions] = creal(cx[i]);
        num_solutions++;
      }
    }
    
    return num_solutions;
  }
  else{
    z = cbrt(w[0]);
    num_solutions++;
  }

  y = z - b3/(3*z);
  result[0] = y - b2/3;

  b5 = b2 + result[0];
  c5 = -d2/result[0];


  num_solutions = 1 + quad(1, b5, c5, x);
  result[1] = x[0]; result[2] = x[1];

  return num_solutions;
}

int quartic(double A, double B, double C, double D,  double E, double result[4]){
  double b,c,d,e; 
  double m,n,p;
  double cubic_A, cubic_B, cubic_C, cubic_D;
  double cubic_res[3];
  double h,i,j,k;
  int num_solutions;
  double *second_res;

  if(A == 0){
    num_solutions = cubic(B,C,D,E, result);
    return num_solutions;
  }
  b  = B/A; c = C/A; d = D/A; e = E/A;

  m = -6*b*b/16 + 3*b*b/4 - c;
  n = -b*b*b/8 + 2*b*c/4 - d;
  p = -b*b*b*b/256 + b*b*b*b/64 - b*b*c/16 + b*d/4 - e;

  cubic_A = 1;
  cubic_B = -2*m;
  cubic_C = m*m + 4*p;
  cubic_D = -n*n;

  num_solutions = cubic(cubic_A, cubic_B, cubic_C, cubic_D, cubic_res);

  h = sqrt(cubic_res[0]);
  j = -h;
  i = (h*h - m + (n/h))/2;
  k = -p/i;


  //(y^2 + hy + i)(y^2+ jy + k) = 0
  num_solutions = quad(1, h, i, result);
  second_res = &result[num_solutions];
  num_solutions += quad(1, j, k, second_res);

  //Results we just got solved for y
  //x = y -b/4
  for(int i = 0; i < num_solutions; i++){
    result[i] -= b/4; 
  }
  return num_solutions;
}


