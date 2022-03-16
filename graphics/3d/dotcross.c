#include "FPToolkit.c"

double dot(double A[3], double B[3]){
  double dot;
  dot=A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
  return dot;
}

void cross(double C[3],double A[3], double B[3]){
  C[0]=(A[1]*B[2])-(A[2]*B[1]);
  C[1]=-((A[0]*B[2])-(A[2]*B[0]));
  C[2]=(A[0]*B[1])-(A[1]*B[0]);
}
