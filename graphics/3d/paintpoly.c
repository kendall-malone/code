// painters algorithm

#include "FPToolkit.c"
#include "M3d_matrix_tools.c"


typedef
struct{
  int objnum;
  int polynum;
  double dist;
}POLYGON;

int numobjects;
int numpoints[10];
double x[10][15000],y[10][15000],z[10][15000];
int numpolys[10];
int psize[10][14000];
int con[10][14000][8];
double xbar[10][15000],ybar[10][15000];
double H,ha;
double color[10][3];
POLYGON shape[15000];



int compare (const void *p, const void *q)
{
  POLYGON *a, *b ;

  a = (POLYGON*)p ;
  b = (POLYGON*)q ;

  if  (((*a).dist) < ((*b).dist)) return -1 ;
  else if (((*a).dist) > ((*b).dist)) return 1 ;
  else return 0 ;
}


void makeColors(){
  color[0][0]=1; color[0][1]=1; color[0][2]=1;//white
  color[1][0]=1; color[1][1]=0; color[1][2]=0;//red
  color[2][0]=0; color[2][1]=1; color[2][2]=0;//green
  color[3][0]=0; color[3][1]=0; color[3][2]=1;//blue
  color[4][0]=1; color[4][1]=0; color[4][2]=1;//purple
  color[5][0]=1; color[5][1]=1; color[5][2]=0;//yellow
  color[6][0]=0; color[6][1]=1; color[6][2]=1;//cyan
  color[7][0]=.5; color[7][1]=1; color[7][2]=.5;//light green
  color[8][0]=1; color[8][1]=.5; color[8][2]=.5;//pink
  color[9][0]=.5; color[9][1]=.5; color[9][2]=1;//purple-blue
}


void findCenter(int k){
  int i;
  double sumx,sumy,sumz;
  sumx=0;
  sumy=0;
  sumz=0;
  for(i=0;i<numpoints[k];i++){
    sumx+=x[k][i];
    sumy+=y[k][i];
    sumz+=z[k][i];
  }
  x[k][numpoints[k]+1]=sumx/numpoints[k];
  y[k][numpoints[k]+1]=sumy/numpoints[k];
  z[k][numpoints[k]+1]=sumz/numpoints[k];
}


int makeObjects(){
  int i,j,k,r,t;
  r=0; t=0;
  for(i=0;i<numobjects;i++){
    for(j=0;j<numpolys[i];j++){
      if(z[i][con[i][j][0]]>0){
	shape[r].objnum=i;
	shape[r].polynum=j;
	shape[r].dist = z[i][con[i][j][0]];
	r++;
      }
    }
	
  }
  return r;
}

void moveToScreen(int k){
  int i,j;
  H=tan(ha*(M_PI/180));
  for(i=0;i<numpoints[k];i++){
    xbar[k][i]=((x[k][i]/z[k][i])*(400/H))+400;
    ybar[k][i]=((y[k][i]/z[k][i])*(400/H))+400;
  }
}



void drawPoly(int ii, int wire[10]){
  int i,p,size,onum;
  double a[10],b[10],dist;
  onum=shape[ii].objnum;
  p=shape[ii].polynum;
  size=psize[onum][p];
  dist=shape[ii].dist;
  G_rgb(color[onum][0],color[onum][1],color[onum][2]);
  for(i=0;i<size;i++){
    a[i]=xbar[onum][con[onum][p][i]];
    b[i]=ybar[onum][con[onum][p][i]];
  }
  G_fill_polygon(a,b,size);
  if(wire[onum]>0){
    G_rgb(0,0,0);
    G_polygon(a,b,size);
  }
}




void drawAllObjects(int hide[10],int wire[10], int np){
  int i=0;
  for(i=0;i<numobjects;i++){
      moveToScreen(i);
  }
  for(i=np-1;i>= 0;i--){
    if(hide[shape[i].objnum]>0){
      drawPoly(i,wire);
    }    
  }
}

int main(int argc, char **argv){
  int i,j,k;//k is the object number
  FILE *fp;
  int v,key,n;
  int sign = 1 ;
  int wire[10];
  int action = 't' ;
  double transa[4][4],transb[4][4],matrixx[4][4],matrixy[4][4],matrixz[4][4],rotx[4][4],roty[4][4],rotz[4][4],transx[4][4],transy[4][4],transz[4][4],trans[4][4],matrix[4][4],rot[4][4];
  double cs,sn;
  int onum,q,np;
  int change=1;
  int hide[10];
  numobjects=argc-1;
  for(k=0;k<numobjects;k++){
    fp=fopen(argv[k+1], "r");
    if(fp==NULL){
      printf("Can't open file %s\n",argv[k+1]);
      exit(0);
    }
    fscanf(fp,"%d",&numpoints[k]);//scans out the number of points
    for(i=0;i<numpoints[k];i++){//saves the points into x,y,z arrays
      fscanf(fp,"%lf %lf %lf",&x[k][i], &y[k][i], &z[k][i]);
    }
    fscanf(fp,"%d",&numpolys[k]);//scans out the number of polygons those points form
    for(i=0;i<numpolys[k];i++){//fills the psize and conuctivity arrays
      fscanf(fp,"%d",&psize[k][i]);
      for(j=0;j<psize[k][i];j++){
	fscanf(fp,"%d",&con[k][i][j]);
      }
    }
    
    findCenter(k);
    double du[4][4];
    M3d_make_translation(du, -x[k][numpoints[k]],  -y[k][numpoints[k]], -z[k][numpoints[k]]);
    M3d_mat_mult_points(x[k],y[k],z[k],du,x[k],y[k],z[k],numpoints[k]+1);


  }
  makeColors();
  np=makeObjects();
  qsort (shape, np, sizeof(POLYGON), compare) ;
  
  /*************************
   *Drawing Portion of Main*
   *************************/
  for(i=0;i<10;i++){
    hide[i]=1;
    wire[i]=-1;
  }
  printf("Please enter your viewing angle\n");
  scanf("%lf",&ha);
   G_choose_repl_display();
    int swidth = 600; int sheight = 600;
    G_init_graphics(600, 600);
  G_rgb(0,0,0);
  G_clear();
  cs=cos(.01);
  sn=sin(.01);
  onum = 0 ; // onum marks the current object
  n = numpoints[onum] ; // other else ifs need this
  drawAllObjects(hide,wire,np);
  while (1) {

    q = G_wait_key() ;
    
    if (q == 'q') {
      exit(0) ;

    }else if (q == 's'){//switch backface
      change=-change;
      
    } else if (q == 'c') {//zoom in or out
      sign = -sign ;
      cs=cos(sign*.01);
      sn=sin(sign*.01);

    } else if (q == 't') {//translate
      action = q ;

    }else if(q=='h'){
      hide[onum] = -hide[onum];

    }else if(q=='w'){
      wire[onum]=-wire[onum];
     
    } else if (q == 'r') {//rotate
      action = q ;

    }else if (('0' <= q) && (q <= '9')) {
      k = q - '0' ;  
      if (k < numobjects) { onum = k ; }
    } else if ((q == 'x') && (action == 't')) {
        M3d_make_translation(transx,sign,0,0);
        M3d_mat_mult_points (x[onum],y[onum],z[onum],  transx,x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'y') && (action == 't')) {
       M3d_make_translation(transy,0,sign,0);
       M3d_mat_mult_points (x[onum],y[onum],z[onum],  transy,x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'z') && (action == 't')) {
        M3d_make_translation(transz,0,0,sign);
        M3d_mat_mult_points (x[onum],y[onum],z[onum],transz,x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'x') && (action == 'r')) {
      M3d_make_translation(transa,-x[onum][numpoints[onum]],-y[onum][numpoints[onum]],-z[onum][numpoints[onum]]);
      M3d_make_x_rotation_cs(rotx,cs,sn);
      M3d_mat_mult(matrixx,rotx,transa);
      M3d_make_translation(transb,x[onum][numpoints[onum]],y[onum][numpoints[onum]],z[onum][numpoints[onum]]);
      M3d_mat_mult(matrixx,transb,matrixx);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],  matrixx,x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'y') && (action == 'r')) {
      M3d_make_translation(transa,-x[onum][numpoints[onum]],-y[onum][numpoints[onum]],-z[onum][numpoints[onum]]);
      M3d_make_y_rotation_cs(roty,cs,sn);
      M3d_mat_mult(matrixy,roty,transa);
      M3d_make_translation(transb,x[onum][numpoints[onum]],y[onum][numpoints[onum]],z[onum][numpoints[onum]]);
      M3d_mat_mult(matrixy,transb,matrixy);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],  matrixy,x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'z') && (action == 'r')) {
      M3d_make_translation(transa,-x[onum][numpoints[onum]],-y[onum][numpoints[onum]],-z[onum][numpoints[onum]]);
      M3d_make_z_rotation_cs(rotz,cs,sn);
      M3d_mat_mult(matrixz,rotz,transa);
      M3d_make_translation(transb,x[onum][numpoints[onum]],y[onum][numpoints[onum]],z[onum][numpoints[onum]]);
      M3d_mat_mult(matrixz,transb,matrixz);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],  matrixz,x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else {
      
      
    }
    G_rgb(0,0,0) ; 
    G_clear() ;
    G_rgb(0,0,1) ;
    np=makeObjects();
    qsort(shape, np, sizeof(POLYGON),compare);
    drawAllObjects(hide,wire,np) ;
    //draw(onum) ;
  }
}
