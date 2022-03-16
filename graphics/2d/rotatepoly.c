//displays image on screen then rotates, can switch through multiple images

#include "FPToolkit.c"
#include "M2d_matrix_toolsS.c"

int numpoints[10];
  double x[10][1500], y[10][1500];
  int numobjects;
  int i,j,k;
  int numpolys[10];
  int psize[10][1000];
  int con[10][1000][20];
  double red[10][1000], grn[10][1000], blu[10][1000];
  double centerpoly[2];
 double xlow, xhi, ylow, yhi;
 int swidth, sheight;

//draws the polygons
void draw(int k){
  double a[20], b[20];
  int v, key;

 G_rgb(1,1,1);
    G_clear();
    for(i=0;i<numpolys[k];i++){
      for(j=0;j<psize[k][i];j++){
	a[j]=x[k][con[k][i][j]];
	b[j]=y[k][con[k][i][j]];
      }
      G_rgb(red[k][i],grn[k][i],blu[k][i]);
      G_fill_polygon(a,b,psize[k][i]);
    }

}
  void centerObj(int obnum){
    //finds highest/smallest y & x, makes "box" around shape to find center
 
  double xl,xh,yl,yh;
  int i;
 
  double cx, cy;
  xlow=x[obnum][0];
  xhi=x[obnum][0];
  ylow=y[obnum][0];
  yhi=y[obnum][0];
  for(i=1;i<numpoints[obnum];i++){
    xl=x[obnum][i];
    xh=x[obnum][i];
    yl=y[obnum][i];
    yh=y[obnum][i];

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
  }

  cx=(xlow+xhi)/2;
  cy=(ylow+yhi)/2;
  centerpoly[0]=cx;
  centerpoly[1]=cy;
 
}
  //reads in files, shifts points so object is in middle of screen
  int main(int argc, char **argv){
  FILE *fp;
  numobjects=argc-1;
  for(k=0;k<numobjects;k++){
    fp=fopen(argv[k+1],"r");
    if(fp==NULL){
      printf("can't open file %s\n",argv[k+1]);
      exit(0);
    }

    fscanf(fp,"%d",&numpoints[k]);
    for(i=0;i<numpoints[k];i++){
      fscanf(fp,"%lf %lf",&x[k][i],&y[k][i]);
    }
    fscanf(fp,"%d",&numpolys[k]);
    for(i=0;i<numpolys[k];i++){
      fscanf(fp,"%d",&psize[k][i]);
      for(j=0;j<psize[k][i];j++){
	      fscanf(fp,"%d",&con[k][i][j]);
      }
    }

    for(i=0;i<numpolys[k];i++){
      fscanf(fp,"%lf %lf %lf",&red[k][i],&grn[k][i],&blu[k][i]);
    }
    
    
  } 

  
   G_choose_repl_display();
    swidth = 400; sheight = 600;
    G_init_graphics(600, 600);
    
    
    

  double trans[3][3],rot[3][3],scl[3][3],m[3][3],s;
  int v,key;

  //centering every object, then scaling to fit screen
  for(v=0; v<numobjects;v++){
   centerObj(v);
   M2d_make_translation(trans,-1*centerpoly[0],-1*centerpoly[1]);
    //determines scaling factor
    if((xhi-xlow)>(yhi-ylow)){
      s=(600/(xhi-xlow))*.9;
    }else if((xhi-xlow)<=(yhi-ylow)){
      s=(600/(yhi-ylow))*.9;
    }
    M2d_make_scaling(scl,s,s); // matrix for scaling
    M2d_mat_mult(m,scl,trans);
    M2d_make_translation(trans,300,300);
    M2d_mat_mult_pt(centerpoly,trans,centerpoly);
    M2d_mat_mult(m,trans,m);
    M2d_mat_mult_points(x[v],y[v],m,x[v],y[v],numpoints[v]);
  }
  int k=0;

  //finds rotation/translation matrix one time
  //multiplies matrices to make master matrix "m" to then
  //multiply with given points
    M2d_make_translation(trans,-300,-300); //moves center of object to origin 
    M2d_make_rotation_degrees(rot,3); //rotates
    M2d_mat_mult(m,rot,trans);
    M2d_make_translation(trans,300,300); // moves newly rotated object to middle of screen
    M2d_mat_mult(m,trans,m);


  do{ //multiplies points by master matrix "m" everytime a key is pressed
    draw(k);
    M2d_mat_mult_points(x[v],y[v],m,x[v],y[v],numpoints[v]); 
    G_rgb(1,0,1) ;
    G_rgb(0,0,0);
    key = G_wait_key() ;
    if(key=='q'){break;} // ends loop
    else if ('0' <= key && key <= '9') {
      v = key -48 ;//subtract 48 b/c of ASCII
      if (v < numobjects) { k = v ; }//check if the number is one of the objects
    }
    
} while (0==0) ;
  
  G_close();

  }
