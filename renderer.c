#include "FPToolkit.c"
#include "M3d_matrix_tools.c"
#include "root_solver.c"
#include "equation_parser.c"

double light_in_eye_space[3] ;

double AMBIENT      = 0.2 ;
double MAX_DIFFUSE  = 0.5 ;
double SPECPOW      = 80 ;

double tan_half;

double obmat[4][4] ;
double obinv[4][4] ;
double color[3] ;
double reflectivity;

int    q ;

int compare (const void * a, const void * b)
{
  if (*(double*)a > *(double*)b) return 1;
  else if (*(double*)a < *(double*)b) return -1;
  else return 0;
}

int Light_Model (double irgb[3],
		 double s[3],
		 double p[3],
		 double n[3],
		 double argb[3])
// s,p,n in eyespace

// irgb == inherent color of object (input to this function)
// s = location of start of ray (probably the eye)
// p = point on object (input to this function)
// n = normal to the object at p (input to this function)
// argb == actual color of object (output of this function)
// globals : AMBIENT, MAX_DIFFUSE, SPECPOW, light_in_eye_space[3]

// return 1 if successful, 0 if error
{

  double len ;
  double N[3] ;
  len = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]) ;
  if (len == 0) return 0 ;
  N[0] = n[0]/len ;  N[1] = n[1]/len ;  N[2] = n[2]/len ;

  double E[3] ;
  E[0] = s[0] - p[0] ;
  E[1] = s[1] - p[1] ;
  E[2] = s[2] - p[2] ;
  len = sqrt(E[0]*E[0] + E[1]*E[1] + E[2]*E[2]) ;
  if (len == 0) return 0 ;
  E[0] /= len ;  E[1] /= len ;  E[2] /= len ;
  double NdotE = N[0]*E[0] + N[1]*E[1] + N[2]*E[2] ;

  double L[3] ;
  L[0] = light_in_eye_space[0] - p[0] ;
  L[1] = light_in_eye_space[1] - p[1] ;
  L[2] = light_in_eye_space[2] - p[2] ;
  len = sqrt(L[0]*L[0] + L[1]*L[1] + L[2]*L[2]) ;
  if (len == 0) return 0 ;
  L[0] /= len ;  L[1] /= len ;  L[2] /= len ;
  double NdotL = N[0]*L[0] + N[1]*L[1] + N[2]*L[2] ;





  double max_ambient_and_diffuse = AMBIENT + MAX_DIFFUSE ;
  // this needs to occur BEFORE you possibly jump to LLL below




  double intensity ;
  if (NdotL*NdotE < 0) {
    // eye and light are on opposite sides of polygon
    intensity = AMBIENT ;
    goto LLL ;
  } else if ((NdotL < 0) && (NdotE < 0)) {
    // eye and light on same side but normal pointing "wrong" way
    N[0] *= (-1.0) ;    N[1] *= (-1.0) ;    N[2] *= (-1.0) ;
    NdotL *= (-1.0) ;
    NdotE *= (-1.0) ;   // don't use NdotE below, probably should eliminate this
  }


  // ignore Blinn's variant
  double R[3] ; // Reflection vector of incoming light
  R[0] = 2*NdotL*N[0] - L[0] ;
  R[1] = 2*NdotL*N[1] - L[1] ;
  R[2] = 2*NdotL*N[2] - L[2] ;

  double EdotR = E[0]*R[0] + E[1]*R[1] + E[2]*R[2] ;

  double diffuse ;
  if (NdotL <= 0.0) { diffuse = 0.0 ; }
  else { diffuse = MAX_DIFFUSE*NdotL ; }

  double specular ;
  if (EdotR <= 0.0) { specular = 0.0 ; }
  else { specular = (1.0 - max_ambient_and_diffuse)*pow(EdotR,SPECPOW) ;}

  // printf("%lf %lf\n",diffuse,specular) ;
  intensity = AMBIENT + diffuse + specular ;



 LLL : ;

  double f,g ;
  if (intensity <= max_ambient_and_diffuse) {
    f = intensity / max_ambient_and_diffuse ;
    argb[0] = f * irgb[0] ;
    argb[1] = f * irgb[1] ;
    argb[2] = f * irgb[2] ;
  } else {
    f = (intensity - max_ambient_and_diffuse) /
      (1.0 - max_ambient_and_diffuse) ;
    g = 1.0 - f ;
    argb[0] = g * irgb[0] + f ;
    argb[1] = g * irgb[1] + f ;
    argb[2] = g * irgb[2] + f ;
  }

  return 1 ;
}




int ray_to_rgb(double ray_start[3], double ray_end[3],  double argb[3])
{
  double v[3], s[3], end[3], res[4], ref_rgb[3], obj_argb[3], new_start[3], new_end[3];
  double intersec[3], intersec_world[3], ref[3], p[3];
  double  x,  y, z;
  double n_obj[3], n_eye[3];
  double a,b,c, d,e,t;
  double dis = 1e50; //Big value
  double mag;
  int numt;
  double reflection = 0;

  //Transforming ray into object space for the object
  M3d_mat_mult_pt(s, obinv, ray_start);
  M3d_mat_mult_pt(end, obinv, ray_end);
  v[0] = end[0] - s[0];
  v[1] = end[1] - s[1];
  v[2] = end[2] - s[2];

           
	    
  double coeff[5];
  find_coeff(s,v,coeff);
  a = coeff[0]; b = coeff[1]; c = coeff[2]; d = coeff[3]; e = coeff[4];
	      
  numt = quartic(a,b,c,d,e,res);
  t = -1;

  if(numt > 1){
    qsort(res, numt, sizeof(double), compare);
  }

  if((numt > 0) && (res[0] > 0)){
    t = res[0];
  }
  else if((numt > 1) && (res[1] > 0)){
    t = res[1];
  }
  else if((numt > 2) && (res[2] > 0)){
    t = res[2];
  }
  else if((numt > 3) && (res[3] > 0)){
    t = res[3];
  }

  if(t != -1){ //Found a valid intersection point
    intersec[0] = s[0] + t*v[0];
    intersec[1] = s[1] + t*v[1];
    intersec[2] = s[2] + t*v[2];

            
    x = intersec[0]; y = intersec[1]; z = intersec[2];
    find_normal(n_obj, x,y,z);
	      

    M3d_mat_mult_pt(intersec_world, obmat, intersec); //Bringing intersection back into world space
    v[0] = intersec_world[0] - ray_start[0];
    v[1] = intersec_world[1] - ray_start[1];
    v[2] = intersec_world[2] - ray_start[2];

    mag = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

    if(mag < dis){
      p[0] = intersec_world[0];
      p[1] = intersec_world[1];
      p[2] = intersec_world[2];
      dis = mag;

      n_eye[0] = obinv[0][0] * n_obj[0] + obinv[1][0] * n_obj[1] + obinv[2][0] * n_obj[2];
      n_eye[1] = obinv[0][1] * n_obj[0] + obinv[1][1] * n_obj[1] + obinv[2][1] * n_obj[2];
      n_eye[2] = obinv[0][2] * n_obj[0] + obinv[1][2] * n_obj[1] + obinv[2][2] * n_obj[2];

      mag = sqrt(n_eye[0]*n_eye[0] + n_eye[1]*n_eye[1] + n_eye[2]*n_eye[2]);
      n_eye[0] /= mag; n_eye[1] /= mag; n_eye[2] /= mag;

      mag = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
      v[0] /= mag; v[1] /= mag; v[2] /= mag;

               
              
    }
  }
  
  Light_Model(color, ray_start, p, n_eye, obj_argb);

  if(dis == 1e50){ //No intersection found
    argb[0] = 0; argb[1] = 0; argb[2] = 0;
  }
  else{
    argb[0] = obj_argb[0];
    argb[1] = obj_argb[1];
    argb[2] = obj_argb[2];
  }
}
	





int main()
{
	 
  int s,e;
  int frame_number ;
  double eangle ;

  double degrees_of_half_angle ;
  double eye[3],coi[3],up[3] ;
  double light_in_world_space[3] ;

  double vm[4][4], vi[4][4];

  double Tvlist[100];
  int Tn, Ttypelist[100];

  int x_pix, y_pix;
  double screen_pt[3];
  double origin[3];

  double m[4][4], mi[4][4];
  double argb[3] ;
  char fname[100] ;

  zero_coeff_arrays();
  parse_equation();
	
  int WinSize = 800 ;

  G_init_graphics(WinSize,WinSize) ;

  s = 0 ; e = 359 ;

  for(frame_number = s; frame_number <= e; frame_number++){

    G_rgb(0,0,0); G_clear();

    printf("frame = %d\n", frame_number);
    degrees_of_half_angle = 45 ;
    tan_half = tan(degrees_of_half_angle*M_PI/180);

    eangle = 3*frame_number*M_PI/180 ;

    eye[0] =  5  ;
    eye[1] =  5  ;        
    eye[2] =  1  ;

    coi[0] = 0 ;
    coi[1] = 0 ;
    coi[2] = 0 ;

    up[0] = eye[0] ;
    up[1] = eye[1] ;
    up[2] = eye[2] + 1 ;


    light_in_world_space[0] =  20 ;
    light_in_world_space[1] = 100 ;
    light_in_world_space[2] = 100 ;


    // overwrite default values :
    AMBIENT      = 0.1 ;
    MAX_DIFFUSE  = 0.3 ;
    SPECPOW      = 80 ;



    M3d_view(vm,vi,  eye,coi,up) ;

    M3d_mat_mult_pt(light_in_eye_space, vm, light_in_world_space) ;
	  

    //////////////////////////////////////////////////////////////
    // Object equation entered through input
	  
    color[0] = 1.0 ;
    color[1] = 0.8 ; 
    color[2] = 0.0 ;
	
    Tn = 0 ;
    Ttypelist[Tn] = RY ; Tvlist[Tn] = frame_number; Tn++;
    Ttypelist[Tn] = RX ; Tvlist[Tn] = frame_number*2; Tn++;
    
    M3d_make_movement_sequence_matrix(m, mi, Tn, Ttypelist, Tvlist);
    M3d_mat_mult(obmat, vm, m) ;
    M3d_mat_mult(obinv, mi, vi) ;
    
    reflectivity = 0.0 ;
    

	  
    
	  
    for(x_pix = 0; x_pix < WinSize; x_pix++){
      for(y_pix = 0; y_pix < WinSize; y_pix++){


	screen_pt[0] = x_pix - 0.5*WinSize;
	screen_pt[1] = y_pix - 0.5*WinSize;
	screen_pt[2] = 0.5*WinSize / tan_half;

	ray_to_rgb(origin, screen_pt, argb) ; 

	G_rgb(argb[0], argb[1], argb[2]) ;
	G_point(x_pix, y_pix) ;

      } // end for y_pix

    } // end for x_pix



    G_display_image() ;

    sprintf(fname, "pic%04d.xwd",frame_number) ;
    G_save_image_to_file(fname) ;
  } // end for frame_number



  while (q != 'q') { q = G_wait_key();  }


}
