//dikstra.c
//a program to calculate perform dijkstra
//part of the COMS10007 course at Bristol University
//Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

/*
this performs dijkstra on specifically the graph in the notes; it assumes the starting point
is the 0th node, and the end point the 4th and hard codes the distance matrix
*/


#define n 5
#define inf 1000
#include<stdio.h>


void print_matrix(int a[n][n]);
void print_route(int route[n]);

int dijkstra(int a[n][n],int route[n]);

int main()
{

  int adj[n][n]={{0,10,4,11,inf},{10,0,2,3,8},{4,2,0,inf,8},{11,3,inf,0,1},{inf,8,8,1,0}};

  print_matrix(adj);

  int route[n];

  int distance=dijkstra(adj,route);

  printf("%d\n",distance);

  print_route(route);

}

int dijkstra(int a[n][n],int route[n])
{
  
  int i, available[n], distances[n],current=0,next,min_distance;

  for(i=0;i<n;i++)
    {
      route[i]=0;
      available[i]=1;
      distances[i]=inf;
    }
  
  distances[0]=0;

  while(current!=n-1)
    {
      available[current]=0;

      for(i=1;i<n;i++)
	{
	  if(available[i]&& distances[i]>distances[current]+a[i][current])
	    {
	      distances[i]=distances[current]+a[i][current];
	      route[i]=current;
	    }
	}
      
      next=current;
      min_distance=inf;
      for(i=1;i<n;i++)
	{
	  if(available[i]&&distances[i]<min_distance) 
	    {
	      next=i;
	      min_distance=distances[i];
	    }
	}
      current=next;
   }
  return distances[n-1];
} 


void print_route(int route[n])
{

  int current=n-1;

  while(current!=0)
    {      
      char node=97+current;
      printf("%c ",node);
      current=route[current];
    }

  char node=97+current;
  printf("%c\n",node);
}
  



void print_matrix(int a[n][n])
{
  int i,j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++) printf("%d\t",a[i][j]);
      printf("\n");
    }
}

