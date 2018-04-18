//downhill_simplex.c
//related to 13_downhill_simplex part of the
//PandA1 course at UoBristol
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 


struct Point
{
  double value;
  double x[DIM];
};

typedef struct Point Point;

void print_point(Point* point)
{
  int i;
  for(i=0;i<DIM;i++)
    printf("%f ",(point->x)[i]);
  printf(" : %f\n",point->value);
}

Point* make_point(double this_x[DIM],double (*fxn)())
{
  Point*  point=malloc(sizeof(Point));
  int i=0;
  for(i=0;i<DIM;i++)
    (*point).x[i]=this_x[i];

  point->value=(*fxn)(this_x);

  return point;
}


Point* make_point_zero(double this_x[DIM])
{
  Point*  point=malloc(sizeof(Point));
  int i=0;
  for(i=0;i<DIM;i++)
    (*point).x[i]=this_x[i];

  point->value=0;

  return point;
}

void copy_value(Point* from,Point* to)
{
  int i;
  for(i=0;i<DIM;i++)
    (to->x)[i]=(from->x)[i];

  to->value=from->value;

}


void set_centroid(Point* points[DIM+1],int worst,Point* centroid)
{


  double center[DIM];
  
  int i,j;

  for(i=0;i<DIM;i++)
    center[i]=0.0;

  for(i=0;i<DIM+1;i++)
    if(i!=worst)
      for(j=0;j<DIM;j++)
	center[j]+=(points[i])->x[j];
 

  for(i=0;i<DIM;i++)
    {
      center[i]/=DIM;
      (centroid->x)[i]=center[i];
    }


  centroid->value=0;
}

void set_polated_point(Point* centroid,Point* worst,double(*fxn)(),double lambda, Point* pol_point)
{
  double pol_position[DIM];
  
  int i;

  fflush(stdout);

  for(i=0;i<DIM;i++)
    {

      pol_position[i]=(centroid->x)[i]+lambda*((centroid->x)[i]-(worst->x)[i]);
    }
  fflush(stdout);


  
  for(i=0;i<DIM;i++)
    (pol_point->x)[i]=pol_position[i];

  pol_point->value=(*fxn)(pol_position);

}

void set_reflected(Point* centroid,Point* worst,double(*fxn)(), Point* ref_point)
{
  set_polated_point(centroid,worst,fxn,1.0,ref_point);
}


void set_extended(Point* centroid,Point* worst,double(*fxn)(), Point* ext_point)
{
  set_polated_point(centroid,worst,fxn,2.0,ext_point);
}


void set_contracted(Point* centroid,Point* worst,double(*fxn)(), Point* con_point)
{
  set_polated_point(centroid,worst,fxn,-0.5,con_point);
}

void reduce(Point* points[DIM],int best,double(*fxn)())
{

  int i,j;
  double x;

  for(j=0;j<DIM;j++)
    {
      x=((points[best])->x)[j];
      for(i=0;i<DIM+1;i++)
	if(i!=best)
	  {
	    ((points[i])->x)[j]=0.5*(((points[i])->x)[j]+x);
	  }
    }


  for(i=0;i<DIM+1;i++)
    if(i!=best)
      (points[i])->value=(*fxn)((points[i])->x);
}
      


void best_and_worst(Point* points[DIM+1],int *best,int *worst,int * second_worst)
{
  *best=0;
  double best_val=points[0]->value;
  *worst=1;
  double worst_val=points[1]->value;

  if(worst_val<best_val)
    {
      best_val=worst_val;
      *best=1;
      worst_val=points[0]->value;
      *worst=0;
    }
  
  int i;
  double this_val;
  
  for(i=2;i<DIM+1;i++)
    {
      this_val=points[i]->value;
      if(this_val>worst_val)
	{
	  worst_val=this_val;
	  *worst=i;
	}
      else if(this_val<best_val)
	{
	  best_val=this_val;
	  *best=i;
	} 
    }

  *second_worst=*best;
  worst_val=best_val;

  
  for(i=2;i<DIM+1;i++)
    if(i!=*worst)
      {
	this_val=points[i]->value;
	if(this_val>worst_val)
	  {
	    worst_val=this_val;
	    *second_worst=i;
	  }
      }
  
  
}
 
void make_points(double x0[DIM],double epsilon,double (*fxn)(),Point* points[DIM+1])
{

  points[0]=make_point(x0,fxn);

  int i;

  for(i=1;i<DIM+1;i++)
    {
      points[i]=make_point_zero(x0);
      int rand_int=rand();
      double rand_offset=0.5*epsilon*(1+(double)rand_int/RAND_MAX);
      if(rand_int%2==0)
	(points[i]->x)[i-1]+=rand_offset;
      else
	(points[i]->x)[i-1]-=rand_offset;
      points[i]->value=(*fxn)(points[i]->x);
    }

}
