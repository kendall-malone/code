// click points that create a polygon, lines are drawn as points are clicked (user generated polygon)

#include "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>




int click_and_save(double x[], double y[]){ 
  // makes array for points 
  
  double p[2];
  int r=0;
  G_wait_click(p); // allows user to click point and then put x y in array
  G_rgb(1,1,1);
  while(p[0]>50 || p[1]>50) // loop makes sure points are clicked outside rectangle 
  {
    x[r]=p[0]; 
    y[r]=p[1];
    G_fill_circle(x[r],y[r],4); //point
    if (r>0){
      G_line(x[r-1], y[r-1], x[r], y[r]);
    }
   r++;
    G_wait_click(p); //reruns loop
  }
  if (r>=1){
    G_line(x[0], y[0], x[r-1], y[r-1]);
  }
  return r; 
  }
  

  
  



void rectangle(){ // draws rectangle
  G_rgb(1,0,0);
  G_fill_rectangle(0,0,50,50);
}

/*void my_polygon(double x[], double y[], int p){
   int i = 0; // loop connects the points , starts with x0 to x(n-1)
  while(i<p-1) // connects last point to first point
  {
    G_line( x[i], y[i], x[i+1], y[i+1]); // connects point a to point b
    i++; // goes to point c from b
  }
  
  G_line(x[i], y[i], x[0], y[0]);
}*/

  int main(){
    double x[10]; //= {100, 200, 300, 400};
    double y[10]; //= {300, 270, 420, 140};
    int i=0;
    double p[2];
    int swidth, sheight;

    G_choose_repl_display();
    swidth = 400; sheight = 600;
    G_init_graphics(600, 600);
    G_rgb(0,0,0);
    G_clear();
    //G_rgb(1,0,1);
   // my_polygon (x,y,4,4);
    rectangle(); // stops points at rectangle 
    int b= click_and_save(x,y);
    G_rgb(1,0,0);
    //my_polygon(x,y, b);
    G_display_image();
    G_wait_key();
    
  } 
