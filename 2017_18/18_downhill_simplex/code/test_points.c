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

  double x1[DIM]={0,1};
  double x2[DIM]={-1,0};
  double x3[DIM]={1,0};

  Point* points[DIM+1];

  points[0]=make_point(x1,fxn);
  points[1]=make_point(x2,fxn);
  points[2]=make_point(x3,fxn);
  
  int worst=0;
  
  Point* xo=malloc(sizeof(Point));

  set_centroid(points,worst,xo);

  printf("centroid ");
  print_point(xo);

  Point* xr=malloc(sizeof(Point));
  Point* xe=malloc(sizeof(Point));
  Point* xc=malloc(sizeof(Point));

  set_reflected(xo,points[worst],fxn,xr);
  set_extended(xo,points[worst],fxn,xe);
  set_contracted(xo,points[worst],fxn,xc);

  printf("reflecte ");
  print_point(xr);

  printf("extended ");
  print_point(xe);

  printf("contract ");
  print_point(xc);

  reduce(points,1,fxn);

  printf("\n");
  print_point(points[0]);
  print_point(points[1]);
  print_point(points[2]);
  
}
