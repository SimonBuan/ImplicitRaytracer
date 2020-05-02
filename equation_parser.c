#include <stdio.h>

double quartic_coeff[15], cubic_coeff[10], quad_coeff[6], linear[3], constant;  

void zero_coeff_arrays(){
  //Sets coefficient arrays to be all zeroes
  int i;
  for(i = 0; i < 15; i++){
    quartic_coeff[i] = 0;
  }
  for(i = 0; i < 10; i++){
    cubic_coeff[i] = 0;
  }
  for(i = 0; i < 6; i++){
    quad_coeff[i] = 0;
  }
  for(i = 0; i < 3; i++){
    linear[i] = 0;
  }
  constant = 0;
}

int parse_term(char* term){
  //Returns -1 if it is unable to evaluate the given term
  //Parameter term points to string of form c*x^a*y^b*z^c
  //Changes values of arrays quartic/cubic/quad/linear/constant
  double coeff;
  int x_pow, y_pow, z_pow, temp, num;
  
  //Checks if term has a leading coefficient
  if((term[0] >= '0') && (term[0] <= '9')){
    sscanf(term, "%lf", &coeff);
  }
  else if(term[0] == '-'){
    if((term[1] >= '0') && (term[1] <= '9')){
      sscanf(term, "%lf", &coeff);
    }
    else if(term[1] == '.'){
      if((term[2] >= '0') && (term[2] <= '9')){
	sscanf(term, "%lf", &coeff);
      }
      else{
	printf("Invalid input\n");
	return -1;
      }
    }
    else if((term[1] != 'x') && (term[1] != 'y') && (term[1] != 'z')){
      printf("Invalid input\n");
      return -1;
    }
    else{
      coeff = -1;
    }
  }
  else if(term[0] == '.'){
    if((term[1] >= '0') && (term[1] <= '9')){
      sscanf(term, "%lf", &coeff);
    }
    else{
      printf("Invalid input\n");
      return -1;
    }
  }
  else if((term[0] != 'x') && (term[0] != 'y') && (term[0] != 'z')){
    printf("Invalid input\n");
      return -1;
  }
  else{
    coeff = 1;
  }
  
  x_pow = 0; y_pow = 0; z_pow = 0;

  while((term[0] != ' ') && (term[0] != '\0')){
    if(term[0] == 'x'){
      if(term[1] == '^'){
	term += 2;
	num = sscanf(term, "%d", &temp);
	if(num == 0){
	  printf("Invalid input\n");
	  return -1;
	}
      }
      else{
	temp = 1;
	term++;
      }
      x_pow += temp;
    }
    else if(term[0] == 'y'){
      if(term[1] == '^'){
	term += 2;
	num = sscanf(term, "%d", &temp);
	if(num == 0){
	  printf("Invalid input\n");
	  return -1;
	}
      }
      else{
	temp = 1;
	term++;
      }
      y_pow += temp;
    }
    else if(term[0] == 'z'){
      if(term[1] == '^'){
	term += 2;
	num = sscanf(term, "%d", &temp);
	if(num == 0){
	  printf("Invalid input\n");
	  return -1;
	}
      }
      else{
	temp = 1;
	term++;
      }
      z_pow += temp;
    }
    
    else if((term[0] == '^') || (term[0] == '*') || (term[0] == '-') || (term[0] == '.')){
      term++;
    }
    else if((term[0] >= '0') && (term[0] <= '9')){
      term++;
    }
    else{
      printf("Invalid input\n");
      return -1;
    }
  }
  int degree = x_pow + y_pow + z_pow;

  if(degree > 4){
    printf("Equation is of higher degree than 4\n");
    return -1;
  }
  else{
    int id = x_pow*1 + y_pow*10 + z_pow*100;
    switch(id){
    case 0://Constant
      constant += coeff;
      break;
    case 1://x
      linear[0] += coeff;
      break;
    case 10://y
      linear[1] += coeff;
      break;
    case 100://z
      linear[2] += coeff;
      break;
    case 2://x^2
      quad_coeff[0] += coeff;
      break;
    case 20://y^2
      quad_coeff[1] += coeff;
      break;
    case 200://z^2
      quad_coeff[2] += coeff;
      break;
    case 11://x*y
      quad_coeff[3] += coeff;
      break;
    case 101://x*z
      quad_coeff[4] += coeff;
      break;
    case 110://y*z
      quad_coeff[5] += coeff;
      break;
    case 3://x^3
      cubic_coeff[0] += coeff;
      break;
    case 30://y^3
      cubic_coeff[1] += coeff;
      break;
    case 300://z^3
      cubic_coeff[2] += coeff;
      break;
    case 12://x^2*y
      cubic_coeff[3] += coeff;
      break;
    case 102://x^2*z
      cubic_coeff[4] += coeff;
      break;
    case 21://y^2*x
      cubic_coeff[5] += coeff;
      break;
    case 120://y^2*z
      cubic_coeff[6] += coeff;
      break;
    case 201://z^2*x
      cubic_coeff[7] += coeff;
      break;
    case 210://z^2*y
      cubic_coeff[8] += coeff;
      break;
    case 111://x*y*z
      cubic_coeff[9] += coeff;
      break;
    case 4://x^4
      quartic_coeff[0] += coeff;
      break;
    case 40://y^4
      quartic_coeff[1] += coeff;
      break;
    case 400://z^4
      quartic_coeff[2] += coeff;
      break;
    case 13://x^3*y
      quartic_coeff[3] += coeff;
      break;
    case 103://x^3*z
      quartic_coeff[4] += coeff;
      break;
    case 31://y^3*x
      quartic_coeff[5] += coeff;
      break;
    case 130://y^3*z
      quartic_coeff[6] += coeff;
      break;
    case 301://z^3*x
      quartic_coeff[7] += coeff;
      break;
    case 310://z^3*y
      quartic_coeff[8] += coeff;
      break;
    case 22://x^2*y^2
      quartic_coeff[9] += coeff;
      break;
    case 202://x^2*z^2
      quartic_coeff[10] += coeff;
      break;
    case 220://y^2*z^2
      quartic_coeff[11] += coeff;
      break;
    case 112://x^2*y*z
      quartic_coeff[12] += coeff;
      break;
    case 121://y^2*x*z
      quartic_coeff[13] += coeff;
      break;
    case 211://z^2*x*y
      quartic_coeff[14] += coeff;
      break;
    default:
      printf("Error\n");
      return -1;
    }
  return 0;
  }
}

//Takes equation of form x^n*y^m*z^o+
void parse_equation(){
  char terms[30][50];
  char c;
  double rhs; //Right hand side of equation (only expects a constant value)
  int t = 0;  //Counter for number of term
  int i = 0;  //Counter for char in term
  printf("Enter equation: \n");
  scanf("%c", &c);
  while(c != '='){
    if(c == '+'){
      terms[t][i] = '\0';
      t++;
      i= 0;
    }
    else if(c == '-'){
      terms[t][i] = '\0';
      t++;
      i = 0;
      terms[t][i] = '-';
      i++;
    }
    else{
      terms[t][i] = c;
      i++;
    }
    scanf("%c", &c);
  }
  terms[t][i] = '\0';
  t++;

  for(i = 0; i < t; i++){
    parse_term(terms[i]);
  }
  scanf("%lf", &rhs);
  constant -= rhs;
}

void find_coeff(double s[3], double v[3], double coeff[5]){
  //Finds coefficient needed to solve quartic/cubic/quadratic equation
  //Based on implicit algebraic surface equation
  //And ray formula
  //x = s[0] + t*v[0]
  //y = s[1] + t*v[1]
  //z = s[2] + t*v[2]
  //Result stored in coeff
  //coeff[0]*t^4 + coeff[1]*t^3... = 0

  coeff[0] = coeff[1] = coeff[2] = coeff[3] = coeff[4] = 0;

  if(quartic_coeff[0] != 0){//x^4
    coeff[0] += quartic_coeff[0]*(v[0]*v[0]*v[0]*v[0]);
    coeff[1] += quartic_coeff[0]*(4*s[0]*v[0]*v[0]*v[0]);
    coeff[2] += quartic_coeff[0]*(6*s[0]*s[0]*v[0]*v[0]);
    coeff[3] += quartic_coeff[0]*(4*s[0]*s[0]*s[0]*v[0]);
    coeff[4] += quartic_coeff[0]*(s[0]*s[0]*s[0]*s[0]);
  }
  if(quartic_coeff[1] != 0){//y^4
    coeff[0] += quartic_coeff[1]*(v[1]*v[1]*v[1]*v[1]);
    coeff[1] += quartic_coeff[1]*(4*s[1]*v[1]*v[1]*v[1]);
    coeff[2] += quartic_coeff[1]*(6*s[1]*s[1]*v[1]*v[1]);
    coeff[3] += quartic_coeff[1]*(4*s[1]*s[1]*s[1]*v[1]);
    coeff[4] += quartic_coeff[1]*(s[1]*s[1]*s[1]*s[1]);
  }
  if(quartic_coeff[2] != 0){//z^4
    coeff[0] += quartic_coeff[2]*(v[2]*v[2]*v[2]*v[2]);
    coeff[1] += quartic_coeff[2]*(4*s[2]*v[2]*v[2]*v[2]);
    coeff[2] += quartic_coeff[2]*(6*s[2]*s[2]*v[2]*v[2]);
    coeff[3] += quartic_coeff[2]*(4*s[2]*s[2]*s[2]*v[2]);
    coeff[4] += quartic_coeff[2]*(s[2]*s[2]*s[2]*s[2]);
  }
  if(quartic_coeff[3] != 0){//x^3*y
    coeff[0] += quartic_coeff[3]*(v[0]*v[0]*v[0]*v[1]);
    coeff[1] += quartic_coeff[3]*(s[1]*v[0]*v[0]*v[0] + 3*s[0]*v[0]*v[0]*v[1]);
    coeff[2] += quartic_coeff[3]*(3*s[0]*s[1]*v[0]*v[0] + 3*s[0]*s[0]*v[0]*v[1]);
    coeff[3] += quartic_coeff[3]*(3*s[0]*s[0]*s[1]*v[0] + s[0]*s[0]*s[0]*v[1]);
    coeff[4] += quartic_coeff[3]*(s[0]*s[0]*s[0]*s[1]);
  }
  if(quartic_coeff[4] != 0){//x^3*z
    coeff[0] += quartic_coeff[4]*(v[0]*v[0]*v[0]*v[2]);
    coeff[1] += quartic_coeff[4]*(s[2]*v[0]*v[0]*v[0] + 3*s[0]*v[0]*v[0]*v[2]);
    coeff[2] += quartic_coeff[4]*(3*s[0]*s[2]*v[0]*v[0] + 3*s[0]*s[0]*v[0]*v[2]);
    coeff[3] += quartic_coeff[4]*(3*s[0]*s[0]*s[2]*v[0] + s[0]*s[0]*s[0]*v[2]);
    coeff[4] += quartic_coeff[4]*(s[0]*s[0]*s[0]*s[2]);
  }
  if(quartic_coeff[5] != 0){//y^3*x
    coeff[0] += quartic_coeff[5]*(v[1]*v[1]*v[1]*v[0]);
    coeff[1] += quartic_coeff[5]*(s[0]*v[1]*v[1]*v[1] + 3*s[1]*v[1]*v[1]*v[0]);
    coeff[2] += quartic_coeff[5]*(3*s[1]*s[0]*v[1]*v[1] + 3*s[1]*s[1]*v[1]*v[0]);
    coeff[3] += quartic_coeff[5]*(3*s[1]*s[1]*s[0]*v[1] + s[1]*s[1]*s[1]*v[0]);
    coeff[4] += quartic_coeff[5]*(s[1]*s[1]*s[1]*s[0]);
  }
  if(quartic_coeff[6] != 0){//y^3*z
    coeff[0] += quartic_coeff[6]*(v[1]*v[1]*v[1]*v[2]);
    coeff[1] += quartic_coeff[6]*(s[2]*v[1]*v[1]*v[1] + 3*s[1]*v[1]*v[1]*v[2]);
    coeff[2] += quartic_coeff[6]*(3*s[1]*s[2]*v[1]*v[1] + 3*s[1]*s[1]*v[1]*v[2]);
    coeff[3] += quartic_coeff[6]*(3*s[1]*s[1]*s[2]*v[1] + s[1]*s[1]*s[1]*v[2]);
    coeff[4] += quartic_coeff[6]*(s[1]*s[1]*s[1]*s[2]);
  }
  if(quartic_coeff[7] != 0){//z^3*x
    coeff[0] += quartic_coeff[7]*(v[2]*v[2]*v[2]*v[0]);
    coeff[1] += quartic_coeff[7]*(s[0]*v[2]*v[2]*v[2] + 3*s[2]*v[2]*v[2]*v[0]);
    coeff[2] += quartic_coeff[7]*(3*s[2]*s[0]*v[2]*v[2] + 3*s[2]*s[2]*v[2]*v[0]);
    coeff[3] += quartic_coeff[7]*(3*s[2]*s[2]*s[0]*v[2] + s[2]*s[2]*s[2]*v[0]);
    coeff[4] += quartic_coeff[7]*(s[2]*s[2]*s[2]*s[0]);
  }
  if(quartic_coeff[8] != 0){//z^3*y
    coeff[0] += quartic_coeff[8]*(v[2]*v[2]*v[2]*v[1]);
    coeff[1] += quartic_coeff[8]*(s[1]*v[2]*v[2]*v[2] + 3*s[2]*v[2]*v[2]*v[1]);
    coeff[2] += quartic_coeff[8]*(3*s[2]*s[1]*v[2]*v[2] + 3*s[2]*s[2]*v[2]*v[1]);
    coeff[3] += quartic_coeff[8]*(3*s[2]*s[2]*s[1]*v[2] + s[2]*s[2]*s[2]*v[1]);
    coeff[4] += quartic_coeff[8]*(s[2]*s[2]*s[2]*s[1]);
  }
  if(quartic_coeff[9] != 0){//x^2*y^2
    coeff[0] += quartic_coeff[9]*(v[0]*v[0]*v[1]*v[1]);
    coeff[1] += quartic_coeff[9]*(2*s[0]*v[0]*v[1]*v[1] + 2*s[1]*v[0]*v[0]*v[1]);
    coeff[2] += quartic_coeff[9]*(s[0]*s[0]*v[1]*v[1] + 4*s[0]*s[1]*v[0]*v[1] + s[1]*s[1]*v[0]*v[0]);
    coeff[3] += quartic_coeff[9]*(2*s[0]*s[0]*s[1]*v[1] + 2*s[0]*s[1]*s[1]*v[0]);
    coeff[4] += quartic_coeff[9]*(s[0]*s[0]*s[1]*s[1]);
  }
  if(quartic_coeff[10] != 0){//x^2*z^2
    coeff[0] += quartic_coeff[10]*(v[0]*v[0]*v[2]*v[2]);
    coeff[1] += quartic_coeff[10]*(2*s[0]*v[0]*v[2]*v[2] + 2*s[2]*v[0]*v[0]*v[2]);
    coeff[2] += quartic_coeff[10]*(s[0]*s[0]*v[2]*v[2] + 4*s[0]*s[2]*v[0]*v[2] + s[2]*s[2]*v[0]*v[0]);
    coeff[3] += quartic_coeff[10]*(2*s[0]*s[0]*s[2]*v[2] + 2*s[0]*s[2]*s[2]*v[0]);
    coeff[4] += quartic_coeff[10]*(s[0]*s[0]*s[2]*s[2]);
  }
  if(quartic_coeff[11] != 0){//y^2*z^2
    coeff[0] += quartic_coeff[11]*(v[1]*v[1]*v[2]*v[2]);
    coeff[1] += quartic_coeff[11]*(2*s[1]*v[1]*v[2]*v[2] + 2*s[2]*v[1]*v[1]*v[2]);
    coeff[2] += quartic_coeff[11]*(s[1]*s[1]*v[2]*v[2] + 4*s[1]*s[2]*v[1]*v[2] + s[2]*s[2]*v[1]*v[1]);
    coeff[3] += quartic_coeff[11]*(2*s[1]*s[1]*s[2]*v[2] + 2*s[1]*s[2]*s[2]*v[1]);
    coeff[4] += quartic_coeff[11]*(s[1]*s[1]*s[2]*s[2]);
  }
  if(quartic_coeff[12] != 0){//x^2*y*z
    coeff[0] += quartic_coeff[12]*(v[0]*v[0]*v[1]*v[2]);
    coeff[1] += quartic_coeff[12]*(s[2]*v[0]*v[0]*v[1] + s[1]*v[0]*v[0]*v[2] + 2*s[0]*v[0]*v[1]*v[2]);
    coeff[2] += quartic_coeff[12]*(s[1]*s[2]*v[0] + 2*s[0]*s[2]*v[0]*v[1] + 2*s[0]*s[1]*v[0]*v[2] + s[0]*s[0]*v[1]*v[2]);
    coeff[3] += quartic_coeff[12]*(2*s[0]*s[1]*s[2]*v[0] + s[0]*s[0]*s[2]*v[1] + s[0]*s[0]*s[1]*s[2]);
    coeff[4] += quartic_coeff[12]*(s[0]*s[0]*s[1]*s[2]);
  }
  if(quartic_coeff[13] != 0){//y^2*x*z
    coeff[0] += quartic_coeff[13]*(v[1]*v[1]*v[0]*v[2]);
    coeff[1] += quartic_coeff[13]*(s[2]*v[1]*v[1]*v[0] + s[0]*v[1]*v[1]*v[2] + 2*s[1]*v[1]*v[0]*v[2]);
    coeff[2] += quartic_coeff[13]*(s[0]*s[2]*v[1] + 2*s[1]*s[2]*v[1]*v[0] + 2*s[1]*s[0]*v[1]*v[2] + s[1]*s[1]*v[0]*v[2]);
    coeff[3] += quartic_coeff[13]*(2*s[1]*s[0]*s[2]*v[1] + s[1]*s[1]*s[2]*v[0] + s[1]*s[1]*s[0]*s[2]);
    coeff[4] += quartic_coeff[13]*(s[1]*s[1]*s[0]*s[2]);
  }
  if(quartic_coeff[14] != 0){//z^2*x*y
    coeff[0] += quartic_coeff[14]*(v[2]*v[2]*v[0]*v[1]);
    coeff[1] += quartic_coeff[14]*(s[1]*v[2]*v[2]*v[0] + s[0]*v[2]*v[2]*v[1] + 2*s[2]*v[2]*v[0]*v[1]);
    coeff[2] += quartic_coeff[14]*(s[0]*s[1]*v[2] + 2*s[2]*s[1]*v[2]*v[0] + 2*s[2]*s[0]*v[2]*v[1] + s[2]*s[2]*v[0]*v[1]);
    coeff[3] += quartic_coeff[14]*(2*s[2]*s[0]*s[1]*v[2] + s[2]*s[2]*s[1]*v[0] + s[2]*s[2]*s[0]*s[1]);
    coeff[4] += quartic_coeff[14]*(s[2]*s[2]*s[0]*s[1]);
  }

  if(cubic_coeff[0] != 0){//x^3
    coeff[1] += cubic_coeff[0]*(v[0]*v[0]*v[0]);
    coeff[2] += cubic_coeff[0]*(3*s[0]*v[0]*v[0]);
    coeff[3] += cubic_coeff[0]*(3*s[0]*s[0]*v[0]);
    coeff[4] += cubic_coeff[0]*(s[0]*s[0]*s[0]);
  }
  if(cubic_coeff[1] != 0){//y^3
    coeff[1] += cubic_coeff[1]*(v[1]*v[1]*v[1]);
    coeff[2] += cubic_coeff[1]*(3*s[1]*v[1]*v[1]);
    coeff[3] += cubic_coeff[1]*(3*s[1]*s[1]*v[1]);
    coeff[4] += cubic_coeff[1]*(s[1]*s[1]*s[1]);
  }
  if(cubic_coeff[2] != 0){//z^3
    coeff[1] += cubic_coeff[2]*(v[2]*v[2]*v[2]);
    coeff[2] += cubic_coeff[2]*(3*s[2]*v[2]*v[2]);
    coeff[3] += cubic_coeff[2]*(3*s[2]*s[2]*v[2]);
    coeff[4] += cubic_coeff[2]*(s[2]*s[2]*s[2]);
  }
  if(cubic_coeff[3] != 0){//x^2*y
    coeff[1] += cubic_coeff[3]*(v[0]*v[0]*v[1]);
    coeff[2] += cubic_coeff[3]*(s[1]*v[0]*v[0] + 2*s[0]*v[0]*v[1]);
    coeff[3] += cubic_coeff[3]*(2*s[0]*s[1]*v[0] + s[0]*s[0]*v[1]);
    coeff[4] += cubic_coeff[3]*(s[0]*s[0]*s[1]);
  }
  if(cubic_coeff[4] != 0){//x^2*z
    coeff[1] += cubic_coeff[4]*(v[0]*v[0]*v[2]);
    coeff[2] += cubic_coeff[4]*(s[2]*v[0]*v[0] + 2*s[0]*v[0]*v[2]);
    coeff[3] += cubic_coeff[4]*(2*s[0]*s[2]*v[0] + s[0]*s[0]*v[2]);
    coeff[4] += cubic_coeff[4]*(s[0]*s[0]*s[2]);
  }
  if(cubic_coeff[5] != 0){//y^2*x
    coeff[1] += cubic_coeff[5]*(v[1]*v[1]*v[0]);
    coeff[2] += cubic_coeff[5]*(s[0]*v[1]*v[1] + 2*s[1]*v[1]*v[0]);
    coeff[3] += cubic_coeff[5]*(2*s[1]*s[0]*v[1] + s[1]*s[1]*v[0]);
    coeff[4] += cubic_coeff[5]*(s[1]*s[1]*s[0]);
  }
  if(cubic_coeff[6] != 0){//y^2*z
    coeff[1] += cubic_coeff[6]*(v[1]*v[1]*v[2]);
    coeff[2] += cubic_coeff[6]*(s[2]*v[1]*v[1] + 2*s[1]*v[1]*v[2]);
    coeff[3] += cubic_coeff[6]*(2*s[1]*s[2]*v[1] + s[1]*s[1]*v[2]);
    coeff[4] += cubic_coeff[6]*(s[1]*s[1]*s[2]);
  }
  if(cubic_coeff[7] != 0){//z^2*x
    coeff[1] += cubic_coeff[7]*(v[2]*v[2]*v[0]);
    coeff[2] += cubic_coeff[7]*(s[0]*v[2]*v[2] + 2*s[2]*v[2]*v[0]);
    coeff[3] += cubic_coeff[7]*(2*s[2]*s[0]*v[2] + s[2]*s[2]*v[0]);
    coeff[4] += cubic_coeff[7]*(s[2]*s[2]*s[0]);
  }
  if(cubic_coeff[8] != 0){//z^2*y
    coeff[1] += cubic_coeff[8]*(v[2]*v[2]*v[1]);
    coeff[2] += cubic_coeff[8]*(s[1]*v[2]*v[2] + 2*s[2]*v[2]*v[1]);
    coeff[3] += cubic_coeff[8]*(2*s[2]*s[1]*v[2] + s[2]*s[2]*v[1]);
    coeff[4] += cubic_coeff[8]*(s[2]*s[2]*s[1]);
  }
  if(cubic_coeff[9] != 0){//x*y*z
    coeff[1] += cubic_coeff[9]*(v[0]*v[1]*v[2]);
    coeff[2] += cubic_coeff[9]*(s[2]*v[0]*v[1] + s[0]*v[1]*v[2] + s[1]*v[0]*v[2]);
    coeff[3] += cubic_coeff[9]*(s[0]*s[2]*v[1] + s[1]*s[2]*v[0] + s[0]*s[1]*v[2]);
    coeff[4] += cubic_coeff[9]*(s[0]*s[1]*s[2]);
  }

  if(quad_coeff[0] != 0){//x^2
    coeff[2] += quad_coeff[0]*(v[0]*v[0]);
    coeff[3] += quad_coeff[0]*(2*s[0]*v[0]);
    coeff[4] += quad_coeff[0]*(s[0]*s[0]);
  }
  if(quad_coeff[1] != 0){//y^2
    coeff[2] += quad_coeff[1]*(v[1]*v[1]);
    coeff[3] += quad_coeff[1]*(2*s[1]*v[1]);
    coeff[4] += quad_coeff[1]*(s[1]*s[1]);
  }
  if(quad_coeff[2] != 0){//z^2
    coeff[2] += quad_coeff[2]*(v[2]*v[2]);
    coeff[3] += quad_coeff[2]*(2*s[2]*v[2]);
    coeff[4] += quad_coeff[2]*(s[2]*s[2]);
  }
  if(quad_coeff[3] != 0){//x*y
    coeff[2] += quad_coeff[3]*(v[0]*v[1]);
    coeff[3] += quad_coeff[3]*(s[0]*v[1] + s[1]*v[0]);
    coeff[4] += quad_coeff[3]*(s[0]*s[1]);
  }
  if(quad_coeff[4] != 0){//x*z
    coeff[2] += quad_coeff[4]*(v[0]*v[2]);
    coeff[3] += quad_coeff[4]*(s[0]*v[2] + s[2]*v[0]);
    coeff[4] += quad_coeff[4]*(s[0]*s[2]);
  }
  if(quad_coeff[5] != 0){//y*z
    coeff[2] += quad_coeff[5]*(v[1]*v[2]);
    coeff[3] += quad_coeff[5]*(s[1]*v[2] + s[2]*v[1]);
    coeff[4] += quad_coeff[5]*(s[1]*s[2]);
  }

  if(linear[0] != 0){//x
    coeff[3] += linear[0]*v[0];
    coeff[4] += linear[0]*s[0];
  }
  if(linear[1] != 0){//y
    coeff[3] += linear[1]*v[1];
    coeff[4] += linear[1]*s[1];
  }
  if(linear[2] != 0){//z
    coeff[3] += linear[2]*v[2];
    coeff[4] += linear[2]*s[2];
  }

  if(constant != 0){
    coeff[4] += constant;
  }
}

void find_normal(double n[3], double x, double y, double z){
  //Takes partial derivative w.r.t x,y,z of object equation
  //Stores result in n

  n[0] = n[1] = n[2] = 0;
  
  if(quartic_coeff[0] != 0){//x^4
    n[0] += quartic_coeff[0]*4*x*x*x;
  }
  if(quartic_coeff[1] != 0){//y^4
    n[1] += quartic_coeff[1]*4*y*y*y;
  }
  if(quartic_coeff[2] != 0){//z^4
    n[2] += quartic_coeff[2]*4*z*z*z;
  }
  if(quartic_coeff[3] != 0){//x^3*y
    n[0] += quartic_coeff[3]*3*x*x*y;
    n[1] += quartic_coeff[3]*x*x*x;
  }
  if(quartic_coeff[4] != 0){//x^3*z
    n[0] += quartic_coeff[4]*3*x*x*z;
    n[2] += quartic_coeff[4]*x*x*x;
  }
  if(quartic_coeff[5] != 0){//y^3*x
    n[0] += quartic_coeff[5]*y*y*y;
    n[1] += quartic_coeff[5]*3*y*y*x;
  }
  if(quartic_coeff[6] != 0){//y^3*z
    n[1] += quartic_coeff[6]*3*y*y*z;
    n[2] += quartic_coeff[6]*y*y*y;
  }
  if(quartic_coeff[7] != 0){//z^3*x
    n[0] += quartic_coeff[7]*z*z*z;
    n[2] += quartic_coeff[7]*3*z*z*x;
  }
  if(quartic_coeff[8] != 0){//z^3*y
    n[1] += quartic_coeff[8]*z*z*z;
    n[2] += quartic_coeff[8]*3*z*z*y;
  }
  if(quartic_coeff[9] != 0){//x^2*y^2
    n[0] += quartic_coeff[9]*2*x*y*y;
    n[1] += quartic_coeff[9]*2*x*x*y;
  }
  if(quartic_coeff[10] != 0){//x^2*z^2
    n[0] += quartic_coeff[10]*2*x*z*z;
    n[2] += quartic_coeff[10]*2*x*x*z;
  }
  if(quartic_coeff[11] != 0){//y^2*z^2
    n[1] += quartic_coeff[11]*2*y*z*z;
    n[2] += quartic_coeff[11]*2*y*y*z;
  }
  if(quartic_coeff[12] != 0){//x^2*y*z
    n[0] += quartic_coeff[12]*2*x*y*z;
    n[1] += quartic_coeff[12]*x*x*z;
    n[2] += quartic_coeff[12]*x*x*y;
  }
  if(quartic_coeff[13] != 0){//y^2*x*z
    n[0] += quartic_coeff[13]*y*y*z;
    n[1] += quartic_coeff[13]*2*y*x*z;
    n[2] += quartic_coeff[13]*y*y*x;
  }
  if(quartic_coeff[14] != 0){//z^2*x*y
    n[0] += quartic_coeff[14]*z*z*y;
    n[1] += quartic_coeff[14]*z*z*x;
    n[2] += quartic_coeff[14]*2*z*x*y;
  }

  if(cubic_coeff[0] != 0){//x^3
    n[0] += cubic_coeff[0]*3*x*x;
  }
  if(cubic_coeff[1] != 0){//y^3
    n[1] += cubic_coeff[1]*3*y*y;
  }
  if(cubic_coeff[2] != 0){//z^3
    n[2] += cubic_coeff[2]*3*z*z;
  }
  if(cubic_coeff[3] != 0){//x^2*y
    n[0] += cubic_coeff[3]*2*x*y;
    n[1] += cubic_coeff[3]*x*x;
  }
  if(cubic_coeff[4] != 0){//x^2*z
    n[0] += cubic_coeff[4]*2*x*z;
    n[2] += cubic_coeff[4]*x*x;
  }
  if(cubic_coeff[5] != 0){//y^2*x
    n[0] += cubic_coeff[5]*y*y;
    n[1] += cubic_coeff[5]*2*y*x;
  }
  if(cubic_coeff[6] != 0){//y^2*z
    n[1] += cubic_coeff[6]*2*y*z;
    n[2] += cubic_coeff[6]*y*y;
  }
  if(cubic_coeff[7] != 0){//z^2*x
    n[0] += cubic_coeff[7]*z*z;
    n[2] += cubic_coeff[7]*2*z*x;
  }
  if(cubic_coeff[8] != 0){//z^2*y
    n[1] += cubic_coeff[8]*z*z;
    n[2] += cubic_coeff[8]*2*z*y;
  }
  if(cubic_coeff[9] != 0){//x*y*z
    n[0] += cubic_coeff[9]*y*z;
    n[1] += cubic_coeff[9]*x*z;
    n[2] += cubic_coeff[9]*x*y;
  }

  if(quad_coeff[0] != 0){//x^2
    n[0] += quad_coeff[0]*2*x;
  }
  if(quad_coeff[1] != 0){//y^2
    n[1] += quad_coeff[1]*2*y;
  }
  if(quad_coeff[2] != 0){//z^2
    n[2] += quad_coeff[2]*2*z;
  }
  if(quad_coeff[3] != 0){//x*y
    n[0] += quad_coeff[3]*y;
    n[1] += quad_coeff[3]*x;
  }
  if(quad_coeff[4] != 0){//x*z
    n[0] += quad_coeff[4]*z;
    n[1] += quad_coeff[4]*x;
  }
  if(quad_coeff[5] != 0){//y*z
    n[1] += quad_coeff[5]*z;
    n[2] += quad_coeff[5]*y;
  }

  if(linear[0] != 0){//x
    n[0] += linear[0];
  }
  if(linear[1] != 0){//y
    n[1] += linear[1];
  }
  if(linear[2] != 0){//z
    n[2] += linear[2];
  }
}

