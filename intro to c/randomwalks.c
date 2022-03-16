/*
  program to compute the average distance between two random creatures
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
  //functions being called
  int askSteps();
  double askSize();
  int askWalks();
  void arrayInt(double array[], int size);
  void randStep(double location[], double stepSize);
  void randWalk(double location[], int numberSteps, double stepSize);
  double computeDistance(double location1[], double location2[]);
  double trial(int numberSteps, double stepSize);

  //variables
  int numberSteps;
  int walks;
  int k;
  double stepSize;
  double average = 0;

  //actual program that runs
  srand48(time(NULL));
  numberSteps = askSteps();
  stepSize = askSize();
  walks = askWalks();

  for(k=0; k<walks; k++)
  {
    average = average + trial(numberSteps, stepSize);
  }
  average = average / ((double)walks);
  printf("The average distance between the two walkers is %g. \n", average);
}

//fill array with 0's
void arrayInt(double array[], int size)
{
  int k;
  for(k=0; k<size; k++)
  {
    array[k]=0;
  }
}

//function to ask for steps
int askSteps()
{
  int numberSteps;
  printf("How many steps? \n");
  scanf("%d", &numberSteps);
  return numberSteps;
}

//function to ask for step size
double askSize()
{
  double stepSize;
  printf("How big is each step? \n");
  scanf("%lf", &stepSize);
  return stepSize;
}

//function to ask for number of walks
int askWalks()
{
  int trial;
  printf("How many walks? \n");
  scanf("%d", &trial);
  return trial;
}

//function to find a single random step
void randStep(double location[], double stepSize)
{
  location[0] = location[0] + drand48() * 2 * stepSize - stepSize;
  location[1] = location[1] + drand48() * 2 * stepSize - stepSize;
}

//function for a single random walk
void randWalk(double location[], int numberSteps, double stepSize)
{
  int k;
  for(k=0; k<numberSteps; k++)
  {
    randStep(location, stepSize);
  }
}

//function to compute Distance
double computeDistance(double location1[], double location2[])
{
  return sqrt((location1[0]-location2[0])*(location1[0]-location2[0])+(location1[1]-location2[1])*(location1[0]-location2[0]));
}

double trial(int numberSteps, double stepSize)
{
  double locA[2];
  double locB[2];
  arrayInt(locA, 2);
  arrayInt(locB, 2);
  randWalk(locA, numberSteps, stepSize);
  randWalk(locB, numberSteps, stepSize);
  return computeDistance(locA, locB);
}
