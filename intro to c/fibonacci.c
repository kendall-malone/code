//compute fibonaccie numbers

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fib(int n) // compute nth fibonnaci number for n>2
{
  int k;
  int term1 = 1;
  int term2 = 1;
  int temp;
  for(k=2; k<n; k++)
  {
    temp = term1;
    term1 = term2;
    term2 = temp + term1;
  }
  return term2;
}

int getInput() // get integer from user
{
  int input=0;
  while(input<=0)
  {
    printf("Give me a positive interger: \n");
    scanf("%d", &input);
    if(input<=0)
    {
      printf("The integer needs to be positive. \n");
    }
  }
  return input;
}

void report(int output) // print results
{
  printf("The corresponding Fibonnaci number is %d \n", output);
}

int main ()
{
  int n;
  n = getInput();

  if(n==1 || n==2) // special case
  {
    report(1);
  }
  else // general case
  {
    report(fib(n));
  }
}
