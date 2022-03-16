/*
solve the quadratic equation
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main ()
{
  double a, b, c, discriminant, root1, root2, realPart, imaginaryPart;

  printf("Enter a b and c from quadratic equation \n");
  scanf("%lf %lf %lf", &a, &b, &c);

  // discriminant gives an idea of the number of roots and the nature of roots of an equation
  discriminant = b*b-4*a*c;

  // condition for real and different roots
  if (a > 0)
  {
    // takes sqaureroot of quadratic equation when a is a nonzero interger
    root1 = (-b+sqrt(discriminant))/(2*a);
    root2 = (-b-sqrt(discriminant))/(2*a);
    printf("There are two known solutions: \n");
    printf("x=%lf \nx=%lf \n", root1, root2);
  }

  // when a and b = 0, special case with no solution
  else if (a==0 && b==0)
  {
    root1 = 0;
    root2 = 0;
    printf("There is no solution. \n");
  }

  //condition for real and equal roots (both x answers will be equal so only one result)
  else if (discriminant  == 0)
  {
    root1 = root2 = -b/(2*a);
    printf("There is one known solution: \n");
    printf(" x=%lf \n", root1);
  }

  // if roots are not real, allows for imaginary solutions
  else if (a < 0)
  {
    realPart = -b/(2*a);
    imaginaryPart = (-discriminant/(2*a));
    printf("x=%lf+%lfi %lf-%lfi", realPart, imaginaryPart, realPart, imaginaryPart);
  }

//when a = 0 , special case with one solution
else if (a == 0)
{
  root1 = (-c/b);
  printf("There is one known solution: \n");
  printf("x=%lf \n", root1);
}

}
