/*
approximate the area of the unit circle
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
  double k=1, x, y, in=0, circ, area;

  while(k<1000000)
  {
    x=drand48();
    y=drand48();
    circ = (x*x)+(y*y);
    k++;
    if(circ<=1)
      in++;
  }
area= in/1000000;
area= area*4;

printf("The approximation of the unit circle is %lf \n", area);  
}
