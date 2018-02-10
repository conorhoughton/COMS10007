//merge_sort.c
//a program to calculate perform merge_sort
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>


void print_array(int a[], int n);
void swap(int a[],int i, int j);
void merge_sort(int a[], int n);
void merge_sort_r(int a[], int merged_a[],int first, int last);
void merge(int a[], int merged_a[], int first, int mid, int last);

int main()
{

  int n,big_n;

  printf("How many elements? ");
  scanf("%d",&n);

  printf("Largest element? ");
  scanf("%d",&big_n);
  
  int a[n];

  int i;

  for(i=0;i<n;i++)
    a[i]=rand()%big_n;
  
  print_array(a,n);

  printf("\n");

  merge_sort(a,n);

  print_array(a,n);

}


void merge_sort(int a[], int n)
{
  int merged_a[n];
  merge_sort_r(a,merged_a,0,n-1);
}

void merge_sort_r(int a[], int merged_a[],int first, int last)
{
  if(last-first<=0)
    return;

  int mid=(last+first)/2+1;

  merge_sort_r(a, merged_a,first,mid-1);
  merge_sort_r(a, merged_a,mid,last);

  merge(a, merged_a, first, mid, last);

  return;

}



void merge(int a[], int merged_a[], int first, int mid, int last)
{
  int last_lower=mid-1,i=first,j=mid;
  int merged_i=first;

  while(i<=last_lower&&j<=last)
    if(a[i]<a[j])
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

void print_array(int a[], int n)
{
  int i;

  for(i=0;i<n;i++)
      printf(" %d",a[i]); 

  printf("\n");

}


void swap(int a[],int i, int j)
{
  int temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}
