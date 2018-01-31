//binary_search.c
//a program to demonstrate binary search on a sorted list
//related to 3_search
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 



#include<stdio.h>

void sort(int a[], int n);
int search(int a[], int n, int val);

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

//sorts a[]
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
 
//performs binary search on a[n] for value val
int search(int a[],int n, int val)
{
  int mid;
  int low=0;
  int high=n-1;

  while(low<=high)
    {
      mid=(low+high)/2;
      if(a[mid]==val)
	return mid;
      else if(val>a[mid])
	low=mid+1;
      else
	high=mid -1;
    }

  return -1;
}

