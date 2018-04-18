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

  double x1[DIM]={0,0};
  double x2[DIM]={1,0};
  double x3[DIM]={0,2};

  Point* points[DIM+1];

  points[0]=make_point(x1,fxn);
  points[1]=make_point(x2,fxn);
  points[2]=make_point(x3,fxn);
  

  Point* p0=malloc(sizeof(Point));

  set_centroid(points,0,p0);

  print_point(p0);

}
