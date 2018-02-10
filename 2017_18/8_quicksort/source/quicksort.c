//quicksort.c
//a program to calculate perform quicksort
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>

void quick(int a[],int n);
void quick_r(int a[],int first, int last);
void print_array(int a[], int n);
void swap(int a[],int i, int j);

int median(int[],int i, int j, int k);

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

  quick(a,n);

  print_array(a,n);


}

void swap(int a[],int i, int j)
{
  int temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}

//wrapper
void quick(int a[], int n)
{
  quick_r(a,0,n-1);
}

//recursive function for quicksort
void quick_r(int a[],int first, int last)
{
  int n=last-first;

  if(n<1)
    return;

  if(n==1)
    if(a[first]<a[last])
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
      while(a[j]>=a[last]&&j>first)
	j--;
      while(a[i]<a[last])
	i++;
      if(i<j)
	swap(a,i,j);
    }

  swap(a,last,i);

  quick_r(a,first,i-1);
  quick_r(a,i+1,last);

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

void print_array(int a[], int n)
{
  int i;

  for(i=0;i<n;i++)
      printf(" %d",a[i]); 

  printf("\n");

}
