//insert_sort_timing.c
//a simple insert sort program
//it also works out run time

//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 


#include<stdio.h>
#include<time.h>

void sort(int a[], int n,int direction);

int main()
{

  clock_t begin,end;

  int i,n;
  int n0=1,n1=1000;
  int trials=500;

  for(n=n0;n<n1 ;++n)
    {

      int a[n];
      for(i=0;i<n;i++)
	a[i]=n-i-1;	


      double time_spent=0;
      
      int trial_c;
      begin = clock();
      for(trial_c=0;trial_c<trials;trial_c++)
	{

	  sort(a,n,+1);
	  sort(a,n,-1);

	}
      end = clock();
      time_spent = (double)(end - begin) / CLOCKS_PER_SEC;      
      printf("%i %f\n",n,time_spent);
      fflush(stdout);
    }

  return 0;
}

void sort(int a[],int n, int direction)
{

  int i,j,this_a;

  for(i=1;i<n;i++)
    {
      this_a=a[i];
      j=i-1;

      while(j>=0&&direction*this_a<direction*a[j])
	{
	  a[j+1]=a[j];
	  j=j-1;
	}

      a[j+1]=this_a;
    }

}
 
