/*
find mean median mode of a set of 100 numbers
mean = average
median = middle number
mode = most often
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

  int main()
  {
    int size =100;
    int k;
    int count[size+1];
    double sum = 0;
    double mean;
    double median;
    int x; // used for mean
    double temp;
    int i, j, a, n, m; // used for median
    int total;
    int min = 0;
    int mod[size+1]; // mode
    int counter = 0; //counter

    //get inputs from user
    for (k=0; k<size; k++)
    {
      scanf("%d", &x);
      count[k]=x;
    }

    // find mean
    for(k=0; k<size; k++)
    {
      sum = sum + count[k];
    }
    mean = sum / size;
    printf("mean = %lf \n", mean);

    //find median

    for(i=0; i<=size; i++) // put numbers in numerical order
    {
      for(j=i+1; j<size; j++)
      {
        if(count[i]>count[j])
        {
          temp = count[i];
          count[i] = count[j];
          count[j] = temp;
        }
      }
    }

      median = count[49]+count[50];
      median = median / 2;
      printf("median = %lf \n", median);


    // find the mode
    for (i=0; i<size; i++)
    {
      for(j=i+1; j<size; j++)
      {
        if (count[i]==count[j])
        {
          mod[k] = count[i];
          k++;
          counter++;

        }
      }
    }
    if(counter==0)
      printf("the mode does not exist \n");
    else
      printf("mode = %d (occurs %d times)\n", mod[k-1], counter);
  }
