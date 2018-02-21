//depth_graph.c
//
//program to estimate the depth of a binary tree from a shuffled list
//
//a program to implement various simple linked list things
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
  int entry;
  struct node *left;
  struct node *right;
  int height;
};

struct node * add_node(struct node * root,int new_entry,int height,int *max_height);
struct node * make_node(int new_entry,int height,int *max_height);
void delete(struct node * root);

void shuffle(int *array, size_t n);

int main()
{


  int trial_n=1000;

  int big_big_n=20000;
  int d_big_n=100;

  for(int big_n=d_big_n;big_n<=big_big_n;big_n+=d_big_n)
    {
  
      int a[big_n];
      
      for(int i=0;i<big_n;i++)
	a[i]=i;
      
      int total_height=0;
      
      for(int trial_c=0;trial_c<trial_n;trial_c++)
	{


	  
	  shuffle(a,big_n);
	  
	  int max_height=0;

	  struct node * root=make_node(a[0],1,&max_height);

	  for(int i=1;i<big_n;i++)
	    add_node(root,a[i],1,&max_height);

	  total_height+=max_height;

	  delete(root);
	  
	}
      
      double average_height=(double)total_height/trial_n;
      
      printf("%i %f\n",big_n,average_height);
      fflush(stdout);
    }
}


struct node * make_node(int new_entry,int height,int *max_height)
{
  struct node * a_node=(struct node *)malloc(sizeof(struct node));
  a_node->entry=new_entry;
  a_node->height=height;
  
  if(height>*max_height)
    *max_height=height;

  return a_node;
}



struct node * add_node(struct node * here, int new_entry,int height,int *max_height)
{

  
  if(here==NULL)
    return make_node(new_entry,height,max_height);


  if(new_entry<here->entry)
    here->left = add_node(here->left,new_entry,height+1,max_height);
  else
    here->right = add_node(here->right,new_entry,height+1,max_height);

  return here;

}

void delete(struct node * root)
{

  if(root->left!=NULL)
    delete(root->left);
  root->left=NULL;

  if(root->right!=NULL)
    delete(root->right);
  root->right=NULL;
  
  free(root);
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
