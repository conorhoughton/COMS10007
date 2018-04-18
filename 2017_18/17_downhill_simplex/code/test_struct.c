//test_struct.c
//this is a test program for a function pointer being used in make_point
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdlib.h>
#include<stdio.h>

enum {DIM=4};

struct Point
{
  double x[DIM];
  double value;
};

typedef struct Point Point;

Point* make_point(double this_x[DIM],double (*fxn)())
{
  Point*  point=malloc(sizeof(Point));
  int i=0;
  for(i=0;i<DIM;i++)
    (*point).x[i]=this_x[i];

  point->value=(*fxn)(this_x);

  return point;
}

 
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

  double x[DIM]={1,2,3,4};

  double (*fxn)();

  fxn=sum;

  Point* point=make_point(x,fxn);

  printf("%f\n",point->value);
}

