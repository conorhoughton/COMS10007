#include<stdlib.h>
#include<stdio.h>

enum{DIM=2};

#include "downhill_simplex.c"

double sum(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=x[i];

  return total;
}

int main()
{
  double (*fxn)();
  fxn=sum;

  Point* points[DIM];

  double x[DIM]={0,0};
  double epsilon=0.25;

  make_points(x,epsilon,fxn,points);
  
  print_point(points[0]);
  print_point(points[1]);
  print_point(points[2]);
  
}
