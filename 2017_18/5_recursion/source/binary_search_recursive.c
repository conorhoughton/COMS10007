//binary_search_recursive.c
//a program to demonstrate recursive binary search on a sorted list
//related to 3_search
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>

void sort(int a[], int n);
int search(int a[], int n, int val);
int search_recursion(int a[],int n, int val,int low,int high);

int main()
{

  int i,n;

  printf("How many elements? ");
  scanf("%d",&n);

  int a[n];

  printf("Input %d elements.\n",n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);

  sort(a,n);

  for(i=0;i<n ;++i)
    printf("%d ",a[i]);
  printf("\n");

  int val;

  printf("Which element do you want? ");
  scanf("%d",&val);

  int index=search(a,n,val);

  if(index==-1)
    printf("That wasn't an element you eejit!\n");
  else
    printf("In the sorted array %d was element %d\n",val,index);

  return 0;
}

//sorts the list ready for binary searching
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
    }

}

//wrapper for calling the recursive function
//needed since the recursive function needs high and low in the arguments
int search(int a[],int n, int val)
{
  return search_recursion(a,n,val,0,n-1);
}
 
//recursive binary search function
int search_recursion(int a[],int n, int val,int low,int high)
{

  if(high<low)
    return -1;

  int mid=(high+low)/2;

  if(a[mid]==val)
    return mid;

  if(val>a[mid])
    return search_recursion(a,n,val,mid+1,high);
  
  return search_recursion(a,n,val,low,mid-1);
}

