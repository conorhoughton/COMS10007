//fib_tail_recursion.c
//a program to calculate the fibonacci sequence
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>


int fib(int n);
int fib_r(int n, int a, int b);

int main()
{

  int n=30;

  printf("F(%d) is %d\n",n,fib(n));

  return 0;
}

int fib_r(int n, int a, int b)
{
   if(n==0)
     return a;
   if(n==1)
     return b;
   if(n==2)
     return a+b;
     
   return fib_r(n-1,b,a+b);

}

int fib(int n)
{
  return fib_r(n,0,1);
}
