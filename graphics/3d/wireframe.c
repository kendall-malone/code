// wireframe for 3d objects with rotating and translating 

#include "FPToolkit.c"
#include "M3d_matrix_tools.c"

 int numpoints[10];
 double x[10][15000], y[10][15000], z[10][15000];
double xx[10][15000], yy[10][15000]; //zz[10][15000];
 int numobjects;
 int i,j,k;
 int numpolys[10];
 int psize[10][14000];
 int con[10][14000][8];
 double ha=20;
 double H;
 double screenScale;
double centerobj[2];

void centerObj(int obnum){
 
  double xl,xh,yl,yh,zl,zh;
  int i;
  double xlow,xhi,ylow,yhi,zlow,zhi;
 
  double cx, cy, cz;
  xlow=x[obnum][0];
  xhi=x[obnum][0];
  
  ylow=y[obnum][0];
  yhi=y[obnum][0];
  
  zlow=z[obnum][0];
  zhi=z[obnum][0];
  
  for(i=1;i<numpoints[obnum];i++){
    xl=x[obnum][i];
    xh=x[obnum][i];
    
    yl=y[obnum][i];
    yh=y[obnum][i];
    
    zl=z[obnum][i];
    zh=z[obnum][i];

    if(xl<xlow){
      xlow=xl;
    }
    if(xh>xhi){
      xhi=xh;
    }
    if(yl<ylow){
      ylow=yl;
    }if(yh>yhi){
      yhi=yh;
    }
    if(zl<zlow){
      zlow=zl;
    }if(zh>zhi){
      zhi=zh;
    }
  }

  cx=(xlow+xhi)/2;
  cy=(ylow+yhi)/2;
  cz=(zlow+zhi)/2;
  centerobj[0]=cx;
  centerobj[1]=cy;
  centerobj[2]=cz;
 
}





void moveToScreen(int k){
  H=tan(ha*(M_PI/180));
  screenScale=400/H;
     for(i=0;i<numpoints[k];i++){
      
       xx[k][i]=((x[k][i]/z[k][i])*screenScale)+400;
       yy[k][i]=((y[k][i]/z[k][i])*screenScale)+400;
      
      
     }
}

int draw(int k){
  
  double a[15000], b[15000];
  G_rgb(1,1,1);
  G_clear();
  moveToScreen(k);
  for(i=0;i<numpolys[k];i++){
      for(j=0;j<psize[k][i];j++){
	a[j]=xx[k][con[k][i][j]];
	b[j]=yy[k][con[k][i][j]];
      }
      G_rgb(1,0,0);
      G_polygon(a,b,psize[k][i]);
  }
}



  

int main(int argc, char **argv){

  
  FILE *fp;
  double transToCntr[4][4];
  numobjects=argc-1;
  for(k=0;k<numobjects;k++){
    fp=fopen(argv[k+1],"r");
    if(fp==NULL){
      printf("can't open file %s \n",argv[k]);
      exit(0);
    }

    fscanf(fp,"%d",&numpoints[k]);
    for(i=0;i<numpoints[k];i++){
      fscanf(fp,"%lf %lf %lf",&x[k][i],&y[k][i],&z[k][i]);
    }
    fscanf(fp,"%d",&numpolys[k]);
    for(i=0;i<numpolys[k];i++){
      fscanf(fp,"%d",&psize[k][i]);
      for(j=0;j<psize[k][i];j++){
	fscanf(fp,"%d",&con[k][i][j]);
      }
    }
    centerObj(k);
     M3d_make_translation(transToCntr,-centerobj[0],-centerobj[1],-centerobj[2]);
     M3d_mat_mult_points(x[k],y[k],z[k],transToCntr,x[k],y[k],z[k],numpoints[k]);
     x[k][numpoints[k]+1]=0;
     y[k][numpoints[k]+1]=0;
     z[k][numpoints[k]+1]=0;
  }
  
  int k=0;
  int v=0;
  int key;
  double transx[4][4],transy[4][4],transz[4][4],rotx[4][4],roty[4][4],rotz[4][4],m[4][4],cs,sn,matrixx[4][4],matrixy[4][4],matrixz[4][4]; 
  


   G_choose_repl_display();
    int swidth = 400; int sheight = 600;
    G_init_graphics(600, 600);

  int onum;
  int n;
  int sign;
  char action;
  char q;
 onum = 0 ; // onum marks the current object
 n = numpoints[onum] ; // other else ifs need this
  sign = 1 ;
  action = 't' ;
  cs=cos(.01);
  sn=sin(.01);

   while (1) {

    q = G_wait_key() ;
    
    if (q == 'q') {
      exit(0) ;

    } else if (q == 'c') {
      sign = -sign ;
      cs=cos(.01*sign);
      sn=sin(.01*sign);

    } else if (q == 't') {
      action = q ;

    } else if (q == 'r') {
      action = q ;

    } else if (('0' <= q) && (q <= '9')) {
      k = q - '0' ;  
      if (k < numobjects) { onum = k ; }

    } else if ((q == 'x') && (action == 't')) {
      
      M3d_make_translation(transx,sign,0,0);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],  transx,
			 x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'y') && (action == 't')) {

       M3d_make_translation(transy,0,sign,0);
       M3d_mat_mult_points (x[onum],y[onum],z[onum],  transy,
			 x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'z') && (action == 't')) {
       
       M3d_make_translation(transz,0,0,sign);
       M3d_mat_mult_points (x[onum],y[onum],z[onum],  transz,
			 x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'x') && (action == 'r')) {

      M3d_make_translation(matrixx,-x[onum][numpoints[onum]],-y[onum][numpoints[onum]],-z[onum][numpoints[onum]]);
      M3d_make_x_rotation_cs(rotx,cs,sn);
      M3d_mat_mult(m,rotx,matrixx);
      M3d_make_translation(matrixx,x[onum][numpoints[onum]],y[onum][numpoints[onum]],z[onum][numpoints[onum]]);
      M3d_mat_mult(m,matrixx,m);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],m, x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } else if ((q == 'y') && (action == 'r')) {

      M3d_make_translation(matrixy,-x[onum][numpoints[onum]],-y[onum][numpoints[onum]],-z[onum][numpoints[onum]]);
      M3d_make_y_rotation_cs(roty,cs,sn);
      M3d_mat_mult(m,roty,matrixy);
      M3d_make_translation(matrixy,x[onum][numpoints[onum]],y[onum][numpoints[onum]],z[onum][numpoints[onum]]);
      M3d_mat_mult(m,matrixy,m);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],m, x[onum],y[onum],z[onum],numpoints[onum]+1) ;
      

    } else if ((q == 'z') && (action == 'r')) {
      M3d_make_translation(matrixz,-x[onum][numpoints[onum]],-y[onum][numpoints[onum]],-z[onum][numpoints[onum]]);
      M3d_make_z_rotation_cs(rotz,cs,sn);
      M3d_mat_mult(m,rotz,matrixz);
      M3d_make_translation(matrixz,x[onum][numpoints[onum]],y[onum][numpoints[onum]],z[onum][numpoints[onum]]);
      M3d_mat_mult(m,matrixz,m);
      M3d_mat_mult_points (x[onum],y[onum],z[onum],m, x[onum],y[onum],z[onum],numpoints[onum]+1) ;

    } 
 


  

    G_rgb(0,0,0) ; 
    G_clear() ;
    G_rgb(0,0,1) ;
     
    draw(onum) ;
  
    }


}
