//insert_sort_verbose.c
//a simple insert sort program
//it prints out each step of the sort
//related to 1_introduction
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>

void sort(int a[], int n);
void print_list(int a[],int n);

int main()
{

  int i,n;

  printf("How many elements? ");
  scanf("%d",&n);

  int a[n];

  printf("Input %d elements.\n",n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);


  printf("Unsorted.");
  print_list(a,n);

  printf("\n");

  sort(a,n);

  printf("Sorted.");
  print_list(a,n);

  printf("\n");

  return 0;
}

//performs insert sort on a[]
void sort(int a[],int n)
{

  int i,j,this_a;

  for(i=1;i<n;i++)
    {
      this_a=a[i];
      j=i-1;

      while(j>=0&&this_a<a[j])
	{
	  a[j+1]=a[j];
	  j=j-1;
	}

      a[j+1]=this_a;
      print_list(a,n);
      printf("\n");
    }

}

//prints the list a
void print_list(int a[],int n)
{
  int i;
  for(i=0;i<n;i++)
      printf(" %d",a[i]); 
}

