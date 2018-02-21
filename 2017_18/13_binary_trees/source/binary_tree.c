//binary_tree.c
//a program to implement various simple linked list things
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include <stdio.h>
#include <stdlib.h>

struct node
{
  int entry;
  struct node *left;
  struct node *right;
};

struct node * add_node(struct node * root,int new_entry);
int is_leaf(struct node * here);
struct node * make_node(int new_entry);
void quick_print(struct node * root);
int rand_print(int big_n);
int is_entry(struct node * root,int a_entry);
struct node * find_entry(struct node * root, int a_entry);

int main()
{

  int i,n,big_n;

  printf("How many elements? ");
  scanf("%d",&n);

  printf("Largest element? ");
  scanf("%d",&big_n);

  struct node * root=make_node(rand_print(big_n));

  for(i=1;i<n;i++)
    add_node(root,rand_print(big_n));

  printf("\n");

  int find_a=1;

  /*  
  while(find_a>=0)
    {
      printf("Find? (negative to end) ");
      scanf("%d",&find_a);
      if(find_a>=0)
	if(is_entry(root,find_a))
	  printf("%d is an entry.\n",find_a);
	else
	  printf("%d is not an entry.\n",find_a);
    }
  */

  while(find_a>=0)
    {
      printf("Find? (negative to end) ");
      scanf("%d",&find_a);
      if(find_a>=0)
	if(find_entry(root,find_a)!=NULL)
	  printf("%d is an entry.\n",find_a);
	else
	  printf("%d is not an entry.\n",find_a);
    }

  //  quick_print(root);

}



int is_leaf(struct node * here)
{
  if(here->left==NULL&&here->right==NULL)
    return 1;
  return 0;
}

struct node * make_node(int new_entry)
{
  struct node * a_node=(struct node *)malloc(sizeof(struct node));
  a_node->entry=new_entry;

  return a_node;
}

int is_entry(struct node * root,int a_entry)
{
  if(root==NULL)
    return 0;
  else if(root->entry==a_entry)
    return 1;

  if(root->entry>a_entry)
    return is_entry(root->left,a_entry);
  return is_entry(root->right,a_entry);

}

struct node * find_entry(struct node * root, int a_entry)
{
  if(root==NULL)
    return root;
  else if(root->entry==a_entry)
    return root;

  if(root->entry>a_entry)
    return find_entry(root->left,a_entry);
  return find_entry(root->right,a_entry);
}


int rand_print(int big_n)
{
  int a=rand()%big_n;
  printf("%d ",a);
  return a;

}

struct node * add_node(struct node * here,int new_entry)
{

  if(here==NULL)
    return make_node(new_entry);

  if(new_entry<here->entry)
      here->left = add_node(here->left,new_entry);
  else
      here->right = add_node(here->right,new_entry);

  return here;

}

void quick_print(struct node * root)
{
  printf("%d ",root->entry);
  if(root->left!=NULL)
    printf(" l= %d",root->left->entry);
  if(root->right!=NULL)
    printf(" r= %d",root->right->entry);

  printf("\n");

  if(root->left!=NULL)
    quick_print(root->left);

  if(root->right!=NULL)
    quick_print(root->right);

}
