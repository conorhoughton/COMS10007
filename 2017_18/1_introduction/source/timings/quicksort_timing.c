//insert_sort_timing.c
//a simple insert sort program
//it also works out run time

//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(int a[],int n,int direction);
void quick_r(int a[],int first, int last,int direction);

void swap(int a[],int i, int j);

int median(int[],int i, int j, int k);
void shuffle(int *array, size_t n);

int main()
{

  clock_t begin,end;

  int i,n;
  int n0=1,n1=1000;
  int trials=2000;

  for(n=n0;n<n1 ;++n)
    {

      int a[trials][n];
      
      int trial_c;
      
      for(trial_c=0;trial_c<trials;trial_c++)
	for(i=0;i<n;i++)
	  {
	    a[trial_c][i]=n-i-1;	
	    shuffle(a[trial_c],n);
	  }

      begin = clock();
      for(trial_c=0;trial_c<trials;trial_c++)
	sort(a[trial_c],n,+1);
      end = clock();

      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;      

      printf("%i %f\n",n,time_spent);
      fflush(stdout);
    }

  return 0;
}

void swap(int a[],int i, int j)
{
  int temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}

//wrapper
void sort(int a[], int n,int direction)
{
  quick_r(a,0,n-1,direction);
}

//recursive function for quicksort
void quick_r(int a[],int first, int last,int direction)
{
  int n=last-first;

  if(n<1)
    return;

  if(n==1)
    if(direction*a[first]<direction*a[last])
      return;
    else
      {
	swap(a,first,last);
	return;
      }

  int i=first,j=last-1;

  swap(a,median(a,first,first+1,last),last);
  
  while(i<j)
    {
      while(direction*a[j]>=direction*a[last]&&j>first)
	j--;
      while(direction*a[i]<direction*a[last])
	i++;
      if(i<j)
	swap(a,i,j);
    }

  swap(a,last,i);

  quick_r(a,first,i-1,direction);
  quick_r(a,i+1,last,direction);

}

//returns the index of the middle element among a[i], a[j], a[k]
int median(int a[],int i, int j, int k)
{

  if(a[i]>a[j]&&a[i]>a[k])
    return (a[j]>a[k]) ? j : k;
  if(a[i]<a[j]&&a[i]<a[k])
    return (a[j]>a[k]) ? k : j;

  return i;

}


//implementation of the Fisher Yates shuffle from 
//http://stackoverflow.com/questions/6127503/shuffle-array-in-c
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
