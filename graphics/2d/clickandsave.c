 // simply click and save, does nothing else, creates points and puts in an array

#include "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int click_and_save(double x[], double y[]){ 
  // makes array for points 
  
  double p[2];
  int r=0;
  G_wait_click(p); // allows user to click point and then put x y in array
  G_rgb(.5,.5,.5);
  while(p[0]>50 || p[1]>50) // loop makes sure points are clicked outside rectangle 
  {
    x[r]=p[0]; 
    y[r]=p[1];
    G_fill_circle(x[r],y[r],4); //point
   r++;
    G_wait_click(p); //reruns loop
  }
  
  return r; // returns number of points clicked
    
  }
