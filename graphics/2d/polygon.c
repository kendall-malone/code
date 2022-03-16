// user generated polygon that fills once completed


#include "FPToolkit.c"

double x[100], y[100], v[100];
int n, t, j;
//selection sort - sorts given array in order from least to greatest
void selection_sort(double x[], int n)
{
  int i = 0;
  int t;
  while(i<n){
    int k = i + 1;
    int m = i;
    while (k < n){
      if(x[k]<x[m]){ m = k;}
     k++; 
    }
    t = x[i];
    x[i] = x[m];
    x[m] = t;
    i++;
  }
}


//draws polygon and saves number of times you clicked in array
int click_and_save(double x[],double y[]){
  double p[2];
  G_wait_click(p);
  int r=0;
  G_rgb(.5,0,.3);
  while(p[1]>50 || p[0]>50){ 
    x[r]=p[0];
    y[r]=p[1];
    G_fill_circle(x[r],y[r],2);
    if(r>0){ G_line(x[r-1],y[r-1],x[r],y[r]);}
    r++;
   
    G_wait_click(p);
    
  }

  if(r>=1){G_line(x[0],y[0],x[r-1],y[r-1]);}
  return r;  
}



void intercepts(double x[], double y[], int z, double h)
//finds intersection points
//h is y value for where to draw lines from bottom to top
{
  double m, X; // X = x value of intersection
  int i;
  x[z + 1] = x[0]; //c is number of points in array, last point
  y[z + 1] = y[0];
  j = 0; //total number of intersection points
  for (i = 0; i <= z; i++) {
    if (x[i] == x[i + 1]) { // looks for vertical line
      if (y[i] < y[i + 1]) { //
	if ((h >= y[i]) && (h <= y[i + 1])) { // creates intersection point
	  v[j] = x[i];
	  j++;
	}
    } else {
	if ((h <= y[i]) && (h >= y[i + 1])) {
	  v[j] = x[i];
	  j++;
	}
      }

    } else if ((x[i] != x[i + 1]) && (y[i] != y[i + 1])) {
      m = (y[i + 1] - y[i])/(x[i + 1] - x[i]); // if two points are not equal then solve for slope
      if (m > 0) { //positive slope
	if (x[i] < x[i + 1]) {
	  X = ((x[i + 1] - x[i])*(h - y[i])/(y[i + 1] - y[i])) + x[i];
	  if ((X >= x[i]) && (X <= x[i + 1])) {
	    v[j] = X;
	    j++;
	  }
	} else { //negative slope 
	  X = ((x[i] - x[i + 1])*(h - y[i + 1])/(y[i] - y[i + 1])) + x[i + 1];
	  if ((X <= x[i]) && (X >= x[i + 1])) {
	    v[j] = X;
	    j++;
	  }
	}
      } else { //finds intercept when x is same but y is different
	if (x[i] < x[i + 1]) {
	  X = x[i + 1] - ((x[i + 1] - x[i])*(h - y[i + 1])/(y[i] - y[i + 1]));
	  if ((X >= x[i]) && (X <= x[i + 1])) {
	    v[j] = X;
	    j++;
	  }
	} else { // similar triangle to find intercept
	  X = x[i] - ((x[i] - x[i + 1])*(h - y[i])/(y[i + 1] - y[i]));
	  if ((X <= x[i]) && (X >= x[i + 1])) {
	    v[j] = X;
	    j++;
	  }
	}
      }
    } else { // horizontal line since y's are equal
      if ((h == y[i]) && (h == y[i + 1])) {
	v[j] = x[i];
	j++;
	v[j] = x[i + 1];
	j++;
      }
    }
  }
} 

void my_G_fill_polygon(double x[100],double y[100],int n){
   int i;
  double h ;
  for (h = 0.1; h < 600; h++) { //h is y value for intersection lines
    intercepts(x, y, n, h); // puts intersections in new array v
    if (j > 1) {
      selection_sort(v, j); //least to greatest
      v[j] = 0;
      for (i = 0; i < j; i = i + 2) { //draws lines from point to point
	if (v[i + 1] != 0) {
	  G_line(v[i], h, v[i + 1], h);
	}
      }
    }
  }
      
      
      
 
 }
  

int main(){
  int r;

  //initializes window and makes rectangle in corner of screen
  G_choose_repl_display();
  G_init_graphics(600, 600);
  G_rgb(0,0,0);
  G_clear();
  G_rgb(1,1,1);
  G_fill_rectangle(0,0,50,50);

  //saves number of points you click and draws the polygon
  r=click_and_save(x,y);
  
  my_G_fill_polygon(x,y,r-1);
  
  G_wait_key();
}
