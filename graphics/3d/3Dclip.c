#include "FPToolkit.c"
#include "M3d_matrix_tools.c"

int numpoints[10];
double x[10][5000], y[10][5000], z[10][5000]; //all x&ys
int numpolys[10]; //now many polygons
int psize[10][5000]; //how big each polygon is
int con[10][5000][20]; //which points make it up
double H, light[3], specpow, hither = 1, yon = 100;
int numobjects, totalp=0;
double Carray[10][3];


void readxy(FILE *fp, int numim);
void projectxyz(double px[100], double py[100], double pz[100], int numim);
void resizexy(int numim);
void draw3d();
void showIm(int numim);
int sortpoly();
int compare (const void *p, const void *q);
void init_array();
void colors();
double lightme(double px[], double py[], double pz[], int onum, int pnum, double c[]);
double dotprod(double a[], double b[], int num);
double clip(double px[], double py[], double pz[0], int np);
double Clip_Polygon_Against_Plane(double a, double b, double c, double d, double px[], double py[],double pz[], int np, double nx[] , double ny[], double nz[]);

typedef
struct {
  int objnum ;
  int polynum ;
  double dist ;
}
THING;

THING sorty[9000];


int main(int argc, char **argv){
  FILE *fp;
  int q, onum, sign, action, k, n, i;
  double V[4][4], change[4][4], rsin, rcos;

  H = tan(M_PI/4);

  for(int i = 1; i< argc; i++){
    fp = fopen(argv[i], "r");
    if(fp == NULL){
      printf("can't open %s\n", argv[i]);
      exit(0);
      } 
    readxy(fp, i-1);
    showIm(i - 1);
  }

  printf("lightsource (X,Y,Z): \n");
  scanf("%lf %lf %lf", &light[0], &light[1], &light[2]);
  specpow = 50;


  numobjects = argc - 1;

  for(i =0 ; i<numobjects; i++){
    totalp = totalp + numpolys[i];
  }


  G_choose_repl_display();
  G_init_graphics(600, 600);
  G_rgb(0,0,0);
  G_clear();

  colors();
  draw3d();

  onum = 0 ; 
  n = numpoints[onum];

  sign = 1 ;
  rsin = sin(M_PI/45);
  rcos = cos(M_PI/45);
  action = 't' ;
  n = numpoints[onum];

  

  while (1) {

    M3d_make_identity (V);

    q = G_wait_key() ;
    
    if (q == 'q') {
      exit(0) ;
    }

    else if (q == 'c') {
      sign = -sign ;
    } 

    else if (q == 't') {
      action = q ;
    } 

    else if (q == 'r') {
      action = q ;
    } 

    else if (('0' <= q) && (q <= '9')) {
      k = q - '0' ;  
      if (k < numobjects) { onum = k ; 
      n = numpoints[onum];}
    }

    else if ((q == 'x') && (action == 't')) {
      M3d_make_translation(change, sign , 0, 0);
      M3d_mat_mult(V, change, V);
    } 

    else if ((q == 'y') && (action == 't')) {
      M3d_make_translation(change, 0 , sign, 0);
      M3d_mat_mult(V, change, V);

    } 

    else if ((q == 'z') && (action == 't')) {
      M3d_make_translation(change, 0 , 0, sign);
      M3d_mat_mult(V, change, V);
    } 

    else if(q == 'h'){
      hither = hither + sign;
    }

    else if ((q == 'x') && (action == 'r')) {
      M3d_make_translation(V, -x[onum][n], -y[onum][n], -z[onum][n]);
      M3d_make_x_rotation_cs(change, rcos, sign*rsin);
      M3d_mat_mult(V, change, V);
      M3d_make_translation(change, x[onum][n], y[onum][n], z[onum][n]);
      M3d_mat_mult(V, change, V);
    } 

    else if ((q == 'y') && (action == 'r')) {
      M3d_make_translation(V, -x[onum][n], -y[onum][n], -z[onum][n]);
      M3d_make_y_rotation_cs(change, rcos, sign*rsin);
      M3d_mat_mult(V, change, V);
      M3d_make_translation(change, x[onum][n], y[onum][n], z[onum][n]);
      M3d_mat_mult(V, change, V);
    } 

    else if ((q == 'z') && (action == 'r')) {
      M3d_make_translation(V, -x[onum][n], -y[onum][n], -z[onum][n]);
      M3d_make_z_rotation_cs(change, rcos, sign*rsin);
      M3d_mat_mult(V, change, V);
      M3d_make_translation(change, x[onum][n], y[onum][n], z[onum][n]);
      M3d_mat_mult(V, change, V);

    } 
    /*
    else {
      printf("no action\n") ;
    }*/




    M3d_mat_mult_points (x[onum],y[onum],z[onum],  V,
       x[onum],y[onum],z[onum], numpoints[onum]+1) ;
      // the numpoints[onum]+1 is because we have stored the center
      // of the object at the arrays' end

    G_rgb(0,0,0) ; 
    G_clear() ;
    draw3d(); //replace with sorted objects and draw
  }
}

void readxy(FILE *fp, int numim){
//read the file struture and arrange it into the global arrays 
double avgX, avgY, avgZ;

  avgX=0;
  avgY=0;
  avgZ=0;

  fscanf(fp, "%d", &numpoints[numim]);
  for(int i =0; i < numpoints[numim]; i++){
    fscanf(fp, "%lf %lf %lf", &x[numim][i], &y[numim][i], &z[numim][i]);
    avgX = avgX + x[numim][i];
    avgY = avgY + y[numim][i];
    avgZ = avgZ + z[numim][i];
  }
  fscanf(fp, "%d", &numpolys[numim]);
  for(int i = 0; i<numpolys[numim]; i++){
    fscanf(fp, "%d", &psize[numim][i]);
    for(int j = 0; j<psize[numim][i]; j++){
      fscanf(fp, "%d", &con[numim][i][j]);
    }
  }

  x[numim][numpoints[numim]] = avgX/numpoints[numim];
  y[numim][numpoints[numim]] = avgY/numpoints[numim];
  z[numim][numpoints[numim]] = avgZ/numpoints[numim];
}

void projectxyz(double px[100], double py[100], double pz[100], int np){
  int i; 

  for(i = 0; i< np; i++){
    px[i] = ((px[i]/pz[i]) * (300/H) ) + 300;
    py[i] = ((py[i]/pz[i]) * (300/H)) + 300;
  }
  

}

void draw3d(){
//take all the global variables and draw them 
  int i, j, k, pnum, numim, nump;
  double polyx[100], polyy[100], polyz[100];
  double color[3];

  init_array();

  qsort (sorty, totalp, sizeof(THING), compare);

  for(i = totalp -1; i>-1; i--){
    numim = sorty[i].objnum;
    pnum = sorty[i].polynum;
    for(j=0; j<psize[numim][pnum]; j++){
      polyx[j] = x[numim][con[numim][pnum][j]];
      polyy[j] = y[numim][con[numim][pnum][j]];
      polyz[j] = z[numim][con[numim][pnum][j]];
    }

    color[0] = Carray[numim][0]; 
    color[1] = Carray[numim][1]; 
    color[2] = Carray[numim][2]; 
    lightme(polyx, polyy, polyz, numim, pnum, color);

    nump = clip(polyx, polyy, polyz, psize[numim][pnum]);
    
    projectxyz(polyx, polyy, polyz, nump);

    G_rgb(color[0], color[1], color[2]);
    G_fill_polygon(polyx, polyy, nump);
    //G_rgb(0,0,0);
    //G_polygon(polyx, polyy, psize[numim][pnum]);
  }

}

double lightme(double px[], double py[], double pz[], int onum, int pnum, double c[]){
  double amb = 0.2, difu = 0.5, spec=0.3, intensity;
  double n[3], l[3], e[3], r[3];
  double ln, le, ndot, div, ll, lr;
  int i;

  div = amb+difu;

  //light[0] = 100; light[1] = 200; light[2] = -50;
  l[0] = (light[0] - px[0]);
  l[1] = (light[1] - py[0]);
  l[2] = (light[2] - pz[0]);
  

  n[0] = (py[1]-py[0])*(pz[2]-pz[1]) - (pz[1]-pz[0])*(py[2]-py[1]);
  n[1] = -((px[1]-px[0])*(pz[2]-pz[1]) - (pz[1]-pz[0])*(px[2]-px[1]));
  n[2] = (px[1]-px[0])*(py[2]-py[1]) - (py[1]-py[0])*(px[2]-px[1]);

  e[0] = -px[0]; e[1] = -py[0]; e[2]= -pz[0];

  ln = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
  le = sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
  ll = sqrt(l[0]*l[0]+ l[1]*l[1]+ l[2]*l[2]);

  for(i = 0; i<3; i++){
    e[i] = e[i]/le;
    n[i] = n[i]/ln;
    l[i] = l[i]/ll;
  }

  ndot = dotprod(n, l, 3);
  if(ndot < 0){
    n[0] = -n[0];
    n[1] = -n[1];
    n[2] = -n[2];
    ndot = -1*ndot;
  }
  if(dotprod(n, e, 3)< 0){
    c[0] = c[0]*(amb/div);
    c[1] = c[1]*(amb/div);
    c[2] = c[2]*(amb/div);

    return 1;
  }

  difu = ndot*difu;

  for(i=0; i<3; i++){
    r[i] = (2*ndot * n[i]) - l[i];
  }

  lr = sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);


  for(i=0; i<3; i++){
    r[i] = r[i]/lr;
  }

  spec = spec* (pow(dotprod(e, r, 3), specpow));


  intensity = amb + difu + spec;
  if(intensity <= div){
    c[0] = c[0]*(intensity/div);
    c[1] = c[1]*(intensity/div);
    c[2] = c[2]*(intensity/div);
  }
  else{
    c[0] = c[0] + ((intensity-div)/(1-div))*(1-c[0]);
    c[1] = c[1] + ((intensity-div)/(1-div))*(1-c[1]);
    c[2] = c[2] + ((intensity-div)/(1-div))*(1-c[2]);
  }

}

void showIm(int numim){
  double T[4][4], minz;
  int i;

  minz=z[numim][0];

  for(i = 0; i< numpoints[numim]; i++){
    if(minz > z[numim][i]){
      minz = z[numim][i];
    }
  }

  M3d_make_translation(T, -x[numim][numpoints[numim]], -y[numim][numpoints[numim]], 2-minz);
  M3d_mat_mult_points(x[numim], y[numim], z[numim], T, x[numim], y[numim], z[numim], numpoints[numim]+1);
}

double clip(double px[], double py[], double pz[0], int np){

  double nx[100],ny[100], nz[100],  a,b,c,d, cwx,cwy ;
  int i,k,m ;

    a= 0; b=0; c=-1; d=hither; //front
    np = Clip_Polygon_Against_Plane(a,b,c, d, px,py,pz, np, nx ,ny, nz) ;
    for (i = 0 ; i < np; i++) {
      px[i] = nx[i] ;   py[i] = ny[i] ;  pz[i] = nz[i];
    }

    a= 0; b=0; c=1; d=-yon; //back
    np = Clip_Polygon_Against_Plane(a,b,c, d, px,py,pz, np, nx ,ny, nz) ;
    for (i = 0 ; i < np; i++) {
      px[i] = nx[i] ;   py[i] = ny[i] ; pz[i] = nz[i];  
    }

    a= 0; b=1; c=-H; d=0; //top
    np = Clip_Polygon_Against_Plane(a,b,c, d, px,py,pz, np, nx ,ny, nz) ;
    for (i = 0 ; i < np; i++) {
      px[i] = nx[i] ;   py[i] = ny[i] ; pz[i] = nz[i]; 
    }

    a= 0; b=-1; c=-H; d=0; //bottom
    np = Clip_Polygon_Against_Plane(a,b,c, d, px,py,pz, np, nx ,ny, nz) ;
    for (i = 0 ; i < np; i++) {
      px[i] = nx[i] ;   py[i] = ny[i] ;  pz[i] = nz[i];
    }

    a= 1; b=0; c=-H; d=0; //side
    np = Clip_Polygon_Against_Plane(a,b,c, d, px,py,pz, np, nx ,ny, nz) ;
    for (i = 0 ; i < np; i++) {
      px[i] = nx[i] ;   py[i] = ny[i] ; pz[i] = nz[i]; 
    }

    a= -1; b=0; c=-H; d=0; //other side
    np = Clip_Polygon_Against_Plane(a,b,c, d, px,py,pz, np, nx ,ny, nz) ;
    for (i = 0 ; i < np; i++) {
      px[i] = nx[i] ;   py[i] = ny[i] ; pz[i] = nz[i]; 
    }

   return np ;
}

double Clip_Polygon_Against_Plane(double a, double b, double c, double d, double px[], double py[],double pz[], int np, double nx[] , double ny[], double nz[]){
int num,i,j ;
  double x1,y1,x2,y2,z1, z2,x21,y21, z21, den,t,xintsct,yintsct, zintsct ;
  double v1,v2 ;
  
  num = 0 ;
  for (i = 0 ; i < np ; i++) {
     j = (i + 1) % np ;

     // load up segment to be clipped
     x1 = px[i] ; y1 = py[i] ; z1=pz[i];
     x2 = px[j] ; y2 = py[j] ; z2 = pz[j];

     // clip line segment (x1,y1, z1)-(x2,y2, z2) against line
     v1 = a*x1 + b*y1 + c*z1 + d ;
     v2 = a*x2 + b*y2 + c*z2 + d ;
     
     if (v1 >= 0 && v2 >= 0) {
        // out to out, do nothing
     } else if (v1 < 0 && v2 < 0) {
        // in to in
        nx[num] = x2 ; ny[num] = y2 ; nz[num] = z2; num++ ;
     } else {
        // one is in, the other out, so find the intersection

        x21 = x2 - x1 ; y21 = y2 - y1 ; z21 = z2-z1;
        den = a*x21 + b*y21 + c*z21 ;
        if (den == 0) continue ; // do nothing-should never happen
        t = -(a*x1 + b*y1 + c*z1 + d)/den ;
        xintsct = x1 + t*x21 ;
        yintsct = y1 + t*y21 ;
        zintsct = z1 + t*z21;

        if (v1 < 0) { 
          // in to out
          nx[num] = xintsct ; ny[num] = yintsct ; 
          nz[num]= zintsct; num++ ;
        } else  {
          // out to in
          nx[num] = xintsct ; ny[num] = yintsct ; 
          nz[num]= zintsct; num++ ;
          nx[num] = x2 ; ny[num] = y2 ; nz[num] = z2; num++ ;
        }

     }


  } // end for i

  return num ;  // return size of the result poly
}

double dotprod(double a[], double b[], int num){
  double answer = 0;
  int i;

  for(i=0; i<num; i++){
    answer = answer + a[i]*b[i]; 
  }

  return answer;

}

int compare (const void *p, const void *q)
{
  THING *a, *b ;

  a = (THING*)p ;
  b = (THING*)q ;

  if  (((*a).dist) < ((*b).dist)) return -1 ;
  else if (((*a).dist) > ((*b).dist)) return 1 ;
  else return 0 ;
}

int sortpoly(){
  init_array();

  qsort (sorty, totalp, sizeof(THING), compare);

}

void init_array(){
  int i, j, count=0;

  for(i=0; i<numobjects; i++){
    for(j = 0; j<numpolys[i]; j++){
      sorty[count].objnum = i;
      sorty[count].polynum = j;
      sorty[count].dist = z[i][con[i][j][0]];
      count++;
    }
  }
}

void colors(){
  Carray[0][0] = .5; Carray[0][1] = .5; Carray[0][2] = 1;
  Carray[1][0] = 1; Carray[1][1] = 1; Carray[1][2]=1;
  Carray[2][0] = 0; Carray[2][1] = 0; Carray[2][2]=1;
  Carray[3][0] = 1; Carray[3][1] = 1; Carray[3][2]=0;
  Carray[4][0] = 0; Carray[4][1] = 1; Carray[4][2]=1;
  Carray[5][0] = 1; Carray[5][1] = 0; Carray[5][2]=1;
  Carray[6][0] = 0.5; Carray[6][1] =0.5; Carray[6][2]=0.5;
  Carray[7][0] = 0.25; Carray[7][1] = 1; Carray[7][2]=1;
}
