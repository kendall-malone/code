/*
what percent of time is there a shared birthday
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
  int day;
  int k;
  int l;
  int birthdays[366];
  int percent;
  int total;
  double count;
  srand48(time(NULL));

// run a million times
for(l=1; l<=1000000; l++)
{

//fill arrays with 0's
 for (k=0; k<= 365; k++)
  {
   birthdays[k]=0;
  }

//generate birthdays
  for(k=1; k<=28; k++)
  {
    day = floor(365*drand48()+1);
    birthdays[day] = birthdays[day]+1;
    day = (int)floor(day); // convert floor of double to int
  }

  // check for shared birthdays - use 0 slot as an idicator
  for(k=1; k<=365; k++)
  {
    if (birthdays[k]>1)
      birthdays[0]=1;
  }

  if (birthdays[0]=1)
    total++;
}

// find percent
count = birthdays[0] = 1;
percent = ((double)count)/total;

 // print outlet
 printf("%d \n", percent);


}
