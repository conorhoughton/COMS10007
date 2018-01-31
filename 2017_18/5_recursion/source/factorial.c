//factorial.c
//a program to demonstrate different factorial programs
//related to 3_search
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 


#include<stdio.h>

int factorial(int n);
int factorial_tenary(int n);
int factorial_tail_r(int n, int big_n);
int factorial_tail(int n);



int main()
{

  int n=10;

  int n_fact=factorial(n);
  printf("%d ",n_fact);

  n_fact=factorial_tenary(n);
  printf("%d ",n_fact);


  n_fact=factorial_tail(n);
  printf("%d ",n_fact);

  printf("\n");

}

//simple factorial
int factorial(int n)
{
   if(n<2)
      return 1;

   return n*factorial(n-1);
}

//using the tenary operator
int factorial_tenary(int n)
{
   return (n<2) ? 1 : n*factorial_tenary(n-1);
}

//tail recursive factorial program
int factorial_tail_r(int n, int big_n)
{
  if(n<2)
    return big_n;

  return factorial_tail_r(n-1,n*big_n);
}

//wrapper for the tail recursive function
int factorial_tail(int n)
{
  factorial_tail_r(n,1);
}
