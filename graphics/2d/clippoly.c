// clips polygon

#include "FPToolkit.c"
#include "M2d_matrix_toolsS.c"


int numobjects;
int numpoints[10];
double x[10][1500],y[10][1500];
int numpolys[10];
int psize[10][1000];
int con[10][1000][20];
double red[10][1000],grn[10][1000],blu[10][1000];
double center[10][2];
double wcom[2];
double lo[10][2], hi[10][2];
double p[100],q[100];//convex clipping window array;

//find the perimeter of 2 different polygons and determine which one is bigger
int checkClick(double c[]){
  if(c[0]<50&&c[1]<50){
    return 1;
  }else{
    return 0;
  }
}
int clickPolygon(){
  //checks if the click is in the square at the bottom left. If it is, it ends the polygon counting cycle
  
  int n=0;
  double c[2];
  G_wait_click(c);
  while(checkClick(c)==0){
    p[n]=c[0];
    q[n]=c[1];
    G_rgb(1,1,1);
    G_fill_circle(c[0],c[1],2.5);
    G_wait_click(c);
    n++;
  }
  return n;
}


 //finds the center of an object using a bounding box and saves the center in the center array;

void findCenter(int k){
  double xlo, xhi, ylo, yhi;
  int i;
  double j,h;
  xlo = xhi = x[k][0];
  ylo = yhi = y[k][0];
  for(i=0;i<numpoints[k];i++){
    j=x[k][i];
    h=y[k][i];
    if(j<xlo){xlo=j;}
    if(j>xhi){xhi=j;}
    if(h<ylo){ylo=h;}
    if(h>yhi){yhi=h;}
  }
  lo[k][0]=xlo;
  hi[k][0]=xhi;
  lo[k][1]=ylo;
  hi[k][1]=yhi;
  center[k][0]=xlo+((xhi-xlo)/2);
  center[k][1]=ylo+((yhi-ylo)/2);
}

void findWindowCenterOfMass(double wx[], double wy[], int ppoints){
  double xtot=0,ytot=0;
  int i;
  for(i=0;i<ppoints;i++){
    xtot+=wx[i];
    ytot+=wy[i];
  }
  wcom[0]=xtot/ppoints;
  wcom[1]=ytot/ppoints;
}
void intersection(double A[2], double B[2], double C[2], double D[2], double ins[2]){
  double u;
  u=((A[0]*C[1] + C[0]*D[1] + D[0]*A[1]) - (A[1]*C[0] + C[1]*D[0] + D[1]*A[0])) / ((A[0]*C[1] + C[0]*B[1] + B[0]*D[1] + D[0]*A[1]) - (A[1]*C[0] + C[1]*B[0] + B[1]*D[0] + D[1]*A[0]));

  ins[0]=A[0]+u*(B[0]-A[0]);
  ins[1]=A[1]+u*(B[1]-A[1]);
}

int compare(double point, double line){
  if(point*line>=0){  
    return 1;
  }else{
    return 0;
  }
}

//px=object number k's x's : py= object number k's y's
//wx=window w's : wy = window's y's
//find's the slopes of the window edges and compares the points to the center of mass to compute the new polygon

int clip_Poly(double px[], double py[], int pn, double wx[], double wy[],  int wn){
  double A[2],B[2],C[2],D[2],dx,dy,linesine,pointsine1,pointsine2,X,nx[1500],ny[1500],xIntersec,a,b,c,ii,jj,sx[1500],sy[1500];
  int i,j,K,newpts,totalpts,o;
  double ins[2] ;

  totalpts=pn;
  findWindowCenterOfMass(wx,wy,wn);
  for(i=0;i<pn;i++){//initialized temporary new array
    nx[i]=px[i];
    ny[i]=py[i];
  }

  
  for(i=0;i<wn;i++){//goes through every window "line"

    
    A[0]=wx[i];//first point x
    A[1]=wy[i];//first point y
    if(i+1==wn){//A=first point, B=second point fixes the wrap around issue
      B[0]=wx[0];//second point x
      B[1]=wy[0];//second point y
    }else{
      B[0]=wx[i+1];
      B[1]=wy[i+1];
    }
    b=B[0]-A[0];//dx
    a=B[1]-A[1];//dy
    c=(b*A[1])-(a*A[0]);
    linesine=(a*wcom[0])+(-b*wcom[1])+c;
    newpts=0;

    for(int j=0;j<totalpts;j++){
      C[0]=nx[j];//first point x
      C[1]=ny[j];//first point y
      if(j+1==totalpts){//A=first point, B=second point fixes the wrap around issue
	D[0]=nx[0];//second point x
	D[1]=ny[0];//second point y
      }else{
	D[0]=nx[j+1];
	D[1]=ny[j+1];
      }
      pointsine1=(a*C[0])+(-b*C[1])+c;
      pointsine2=(a*D[0])+(-b*D[1])+c;
      ii=compare(pointsine1,linesine);
      jj=compare(pointsine2,linesine);
      if(ii==1 && jj==1){//good->good
	sx[newpts]=D[0];
	sy[newpts]=D[1];
	newpts++;
      }else if(ii==1 && jj==0){//good->bad
	intersection(A,B,C,D,ins);
        sx[newpts]=ins[0] ;
        sy[newpts]=ins[1] ;
	newpts++;
      }else if(ii==0 && jj==1){//bad->good
	intersection(A,B,C,D,ins);
        sx[newpts]=ins[0] ;
        sy[newpts]=ins[1] ;
	newpts++;
	sx[newpts]=D[0];
	sy[newpts]=D[1];
	newpts++;
      }else if(ii==0 && jj==0){//bad->bad
	//do nothing
      }
    } // end for j

    for(o=0;o<newpts;o++){
      nx[o]=sx[o];
      ny[o]=sy[o];
    }
    totalpts=newpts;
  } // end for i
  G_fill_polygon(nx,ny,totalpts);
}


void drawPolygon(int k,int l){
  int i,j;
  double a[1500], b[1500];
  for(i=0;i<numpolys[k];i++){
      for(j=0;j<psize[k][i];j++){
	a[j]=x[k][con[k][i][j]];
	b[j]=y[k][con[k][i][j]];
      }
      G_rgb(red[k][i],grn[k][i],blu[k][i]);
      clip_Poly(a,b,psize[k][i],p,q,l);
    }
}

int main(int argc, char **argv){
  int i,j,k,l;//k is the object number
  int flag=0;
  FILE *fp;
  numobjects=argc-1;
  for(k=0;k<numobjects;k++){
    fp=fopen(argv[k+1], "r");
    if(fp==NULL){
      printf("Cannot read file.");
      exit(0);
    }
    fscanf(fp,"%d",&numpoints[k]);//scans out the number of points
    for(i=0;i<numpoints[k];i++){//saves the points into x,y arrays
      fscanf(fp,"%lf %lf",&x[k][i], &y[k][i]);
    }
    fscanf(fp,"%d",&numpolys[k]);//scans out the number of polygons those points form
    for(i=0;i<numpolys[k];i++){//fills the psize and conuctivity arrays
      fscanf(fp,"%d",&psize[k][i]);
      for(j=0;j<psize[k][i];j++){
	fscanf(fp,"%d",&con[k][i][j]);
      }
    }
    for(i=0;i<numpolys[k];i++){//fills the color arrays
      fscanf(fp, "%lf %lf %lf", &red[k][i], &grn[k][i], &blu[k][i]);
    }


  }
//Drawing Portion of main
   G_choose_repl_display();
    int swidth = 600; int sheight = 600;
    G_init_graphics(600, 600);
  double a[100], b[100],extra,trans[3][3],rot[3][3],scl[3][3],matrix[3][3],scalar[2];
  int v,key;
  for(v=0;v<numobjects;v++){//centers and scales objects before the user first looks at them
    findCenter(v);
    M2d_make_translation(trans,(0-center[v][0]),(0-center[v][1]));//translate(v,0,0);
    M2d_mat_mult_pt(center[v],trans,center[v]);
    scalar[0]=(450/(hi[v][0]-lo[v][0]));
    scalar[1]=(450/(hi[v][1]-lo[v][1]));
    if(scalar[0]<=scalar[1]){//scale(v);
      M2d_make_scaling(scl,scalar[0],scalar[0]);
    }else{
      M2d_make_scaling(scl,scalar[1],scalar[1]);
    }
    M2d_mat_mult(matrix,scl,trans);
    M2d_make_translation(trans,300,300);//translate(v,300,300);
    M2d_mat_mult_pt(center[v],trans,center[v]);
    M2d_mat_mult(matrix,trans,matrix);
    M2d_mat_mult_points(x[v],y[v],matrix,x[v],y[v],numpoints[v]);
  }
  k=0;
  M2d_make_translation(trans,-300,-300);
    M2d_make_rotation_degrees(rot,1);
    M2d_mat_mult(matrix,rot,trans);
    M2d_make_translation(trans,300,300);
    M2d_mat_mult(matrix,trans,matrix);
  do{
    G_rgb(0,0,0);
    G_clear();
    if(flag==0){
      G_rgb(0,1,0);
      G_fill_rectangle(0.5, 0,0 ,0.3);//bottom left stop clicking box
      l=clickPolygon();
      G_rgb(1,1,1);
      G_polygon(p,q,l);
      flag=1;
    }
    G_rgb(0,0,0);
    G_clear();
    drawPolygon(k,l);
    G_rgb(1,1,1);
    G_polygon(p,q,l);//clipping window
    M2d_mat_mult_points(x[k],y[k],matrix,x[k],y[k],numpoints[k]);
    key = G_wait_key() ;
    if(key=='q'){break;}
    else if ('0' <= key && key <= '9') {
      v = key -48 ;//subtract 48 b/c of ASCII
      if (v < numobjects) { k = v ; }//check if the number is one of the objects
    }
  } while (0==0) ;
  G_close();
}
