//fib_recursion_no_termination.c
//a program to calculate the fibonacci sequence
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 


#include<stdio.h>

int fib(int n);

int main()
{

  int n=-1;

  printf("F(%d) is %d\n",n,fib(n));

  return 0;
}

int fib(int n)
{
  if(n==0||n==1)
    {
      return n;
    }

  return fib(n-1)+fib(n-2);

}
