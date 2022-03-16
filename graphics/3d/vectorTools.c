#include "FPToolkit.c"

/**
 *finds the distance of a vector needed in calculating its unit vector
 */
double findDist(double V[3]){
  return sqrt((V[0]*V[0])+(V[1]*V[1])+(V[2]*V[2]));
}


/**
 * adds two vecotrs B and C and returns the new vector in A
 */
void addVectors(double A[3],double B[3], double C[3]){
  double P[3];
  P[0]=C[0]+B[0];
  P[1]=C[1]+B[1];
  P[2]=C[2]+B[2];
  
  A[0]=P[0];
  A[1]=P[1];
  A[2]=P[2];
}

/**
 * negates vector B and saves it in A
 */
void negateVector(double A[3], double B[3]){
  A[0]=-B[0];
  A[1]=-B[1];
  A[2]=-B[2];
}

/**
 *scales Vector B by k and saves it into A
 */
void scaleVector(double A[3],double B[3],double k){
  A[0]=k*B[0];
  A[1]=k*B[1];
  A[2]=k*B[2];
}

/**
 * makes a reflection vector of Lu and saves/returns it as Ru
 * PARAM Lu (unit light vector)
 * PARAM Nu (unit normal vector) 
 * PARAM alpha (the amount needed to scale Nu to get to Ru)
 */
void makeReflectionVector(double Ru[3], double Lu[3], double Nu[3],double alpha){
  double nLu[3],Su[3];
  negateVector(nLu,Lu);
  scaleVector(Su,Nu,2*alpha);
  addVectors(Ru,nLu,Su);
}
