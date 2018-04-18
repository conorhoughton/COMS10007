#include<stdlib.h>
#include<stdio.h>
#include<math.h>

enum{DIM=3};

#include "downhill_simplex.c"

double quad(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=pow(x[i],2);

  return total;
}

//p5 http://www.geatbx.com/download/GEATbx_ObjFunExpl_v38.pdf
double hyper_ellipsoid(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=(i+1)*pow(x[i],2);

  return total;
}

int main()
{
  double (*fxn)();
  fxn=hyper_ellipsoid;

  Point* points[DIM];

  double x[DIM]={20,20,20};
  double epsilon=0.25;

  make_points(x,epsilon,fxn,points);
  
  print_point(points[0]);
  print_point(points[1]);
  print_point(points[2]);
  print_point(points[3]);
  
  int step_c,step_n=100;

  Point *xo=malloc(sizeof(Point));
  Point *xr=malloc(sizeof(Point));
  Point *xc=malloc(sizeof(Point));
  Point *xe=malloc(sizeof(Point));

  int best,worst,second_worst;
  double best_value,worst_value,second_worst_value;

  char move='s';

  for(step_c=0;step_c<step_n;step_c++)
    {
      best_and_worst(points,&best,&worst,&second_worst);
      best_value=points[best]->value;
      worst_value=points[worst]->value;
      second_worst_value=points[second_worst]->value;

      //      printf("%i %i %f %i %f\n",step_c,best,best_value,worst,worst_value);

      set_centroid(points,worst,xo);

      set_reflected(xo,points[worst],fxn,xr);

      if(xr->value<best_value)
	{
	  set_extended(xo,points[worst],fxn,xe);
	  if(xe->value<xr->value)
	    {
	      copy_value(xe,points[worst]);
	      move='e';
	    }
	  else
	    {
	      copy_value(xr,points[worst]);
	      move='r';
	    }
	}
      else if(xr->value<second_worst_value)
	{
	  copy_value(xr,points[worst]);
	  move='r';
	}
      else
	{
	  set_contracted(xo,points[worst],fxn,xc);
	  if(xc->value<worst_value)
	    {
	      copy_value(xc,points[worst]);
	      move='c';
	    }
	  else
	    {
	      reduce(points,best,fxn);
	      move='d';
	    }
	  
	}

      printf("%c(%f)",move,best_value);	  
	  


    }
  printf("\n");

}
