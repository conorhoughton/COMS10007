//going_down_triangles.c
//a simplex method program for printing out triangles
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

enum{DIM=2};

#include "latex_triangles.c"
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
//scaled
double hyper_ellipsoid(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=(i+1)*pow(x[i]/5.0,2);

  return total;
}

//https://en.wikipedia.org/wiki/Rosenbrock_function
double rosenbrock(double x[DIM])
{
  return (1-x[0])*(1-x[0])+100.0*pow(x[1]-x[0]*x[0],2);
}

//goldstein-price function 
//https://en.wikipedia.org/wiki/Test_functions_for_optimization
double goldstein_price(double x_v[DIM])
{
  double f;
  double x=x_v[0]/10.0;
  double y=x_v[1]/10.0;

  f =(1+pow(x+y+1,2)*(19-14*x+3*x*x-14*y+6*x*y+3*y*y))
    *(30+pow(2*x-3*y,2)*(18-32*x+12*x*x+48*y-36*x*y+27*y*y));

  return f;
}
   


int main()
{
  double (*fxn)();
  fxn=hyper_ellipsoid;
  // fxn=rosenbrock;
  //  fxn=goldstein_price;

  Point* points[DIM];

  double x[DIM]={20,30};
  double epsilon=0.5;
  double scale=2.0;
  make_points(x,epsilon,fxn,points);

  int j=0;
  for(j=0;j<=DIM;j++)
    print_point(points[j]);

  int step_c,step_n=450;

  Point *xo=malloc(sizeof(Point));
  Point *xr=malloc(sizeof(Point));
  Point *xc=malloc(sizeof(Point));
  Point *xe=malloc(sizeof(Point));

  int best,worst,second_worst;
  double best_value,worst_value,second_worst_value;

  char move='s';

  FILE * output_file;
  output_file=fopen("triangles.tex","w");

  FILE * output_file_all;
  output_file_all=fopen("all_triangles.tex","w");

  char* title="Hyper-ellipsoid";
  //char* title="Rosenbrock";

  make_preamble(output_file);
  make_preamble(output_file_all);
  add_title(output_file,title);
  add_title(output_file_all,title);

  open_triangle(output_file_all);


  for(step_c=0;step_c<step_n;step_c++)
    {

      best_and_worst(points,&best,&worst,&second_worst);
      best_value=points[best]->value;

      worst_value=points[worst]->value;
      second_worst_value=points[second_worst]->value;

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


      int i;
      for(i=0;i<2;i++)
	printf("%f ",((points[0]->x)[i]+(points[1]->x)[i]+(points[2]->x)[i])/3.0);
      printf("\n");

      add_centered_triangle(output_file,points[0]->x,points[1]->x,points[2]->x);
      append_triangle(output_file_all,points[0]->x,points[1]->x,points[2]->x,scale);


    }
  printf("\n");

  close_triangle(output_file_all);
  make_postamble(output_file_all);
  make_postamble(output_file);

  fclose(output_file);

}
