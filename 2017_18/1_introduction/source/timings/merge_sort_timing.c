//insert_sort_timing.c
//a simple mergesort program
//it also works out run time

//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 


#include<stdio.h>
#include<time.h>

void swap(int a[],int i, int j);

void merge_sort_r(int a[], int merged_a[],int first, int last, int direction);
void merge(int a[], int merged_a[], int first, int mid, int last, int direction);


void sort(int a[], int n,int direction);

int main()
{

  clock_t begin,end;

  int i,n;
  int n0=1,n1=1000;
  int trials=1000;

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

    }

  return 0;
}


void sort(int a[], int n, int direction)
{
  int merged_a[n];
  merge_sort_r(a,merged_a,0,n-1,direction);
}

void merge_sort_r(int a[], int merged_a[],int first, int last,int direction)
{
  if(last-first<=0)
    return;

  int mid=(last+first)/2+1;

  merge_sort_r(a, merged_a,first,mid-1,direction);
  merge_sort_r(a, merged_a,mid,last,direction);

  merge(a, merged_a, first, mid, last,direction);

  return;

}



void merge(int a[], int merged_a[], int first, int mid, int last,int direction)
{
  int last_lower=mid-1,i=first,j=mid;
  int merged_i=first;

  while(i<=last_lower&&j<=last)
    if(direction*a[i]<direction*a[j])
      {
	merged_a[merged_i]=a[i];
	i++;
	merged_i++;
      }
    else
      {
	merged_a[merged_i]=a[j];
	j++;
	merged_i++;
      }

  while(i<=last_lower)
    {
      merged_a[merged_i]=a[i];
      i++;
      merged_i++;
    }


  while(j<=last)
    {
      merged_a[merged_i]=a[j];
      j++;
      merged_i++;
    }

  for(i=first;i<=last;i++)
    a[i]=merged_a[i];

}

void swap(int a[],int i, int j)
{
  int temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}
 
