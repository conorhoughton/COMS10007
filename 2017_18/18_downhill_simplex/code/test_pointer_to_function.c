//pointer_to_function_test.c
//this is a test program for a function pointer being used to pass a function
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

//the syntax for function pointers is described in
//http://www-ee.eng.hawaii.edu/~tep/EE160/Book/chap14/section2.1.3.html


#include<stdio.h>
#include<stdlib.h>


double f(double x)
{
  return x*x;
}

double g(double x)
{
  return -x;
}

struct X_value
{
  double x;
  double value;
};

typedef struct X_value X_value;

X_value * make_X_value(double this_x,double (*fxn)())
{
  X_value * new_x_value=(X_value*)malloc(sizeof(X_value));
  new_x_value->x=this_x;
  new_x_value->value=(*fxn)(this_x);
}

int main()
{
  //this is a function pointer - it points to a function which returns a double
  double (*fxn)();
  fxn=f;

  double x=2;
  
  X_value* x_value_1=make_X_value(x,fxn);

  printf("%f %f\n",x_value_1->x,x_value_1->value);

  fxn=g;

  X_value* x_value_2=make_X_value(x,fxn);

  printf("%f %f\n",x_value_2->x,x_value_2->value);

}
