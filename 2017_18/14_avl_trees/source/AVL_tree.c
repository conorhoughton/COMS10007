//copied in part from "p4program.blogspot.co.uk/2010/12/c-program-to-insert-and-delete-elements.html

#include <stdio.h>
#include <stdlib.h>

struct node
{
  int entry;
  int balance;
  struct node *left;
  struct node *right;
};

struct node * add_node(struct node * root,int new_entry);
struct node * add_node_r(struct node * root,int new_entry,int * work_needed);
struct node * make_node(int new_entry);
void quick_print(struct node * root);
int rand_print(int big_n);
int is_entry(struct node * root,int a_entry);
struct node * find_entry(struct node * root, int a_entry);
int get_height(struct node *a_node) ;
int max(int a, int b);

struct node * rotate_ll(struct node * here);
struct node * rotate_rr(struct node * here);
struct node * rotate_lr(struct node * here);
struct node * rotate_rl(struct node * here);

struct node * latex_print(struct node * head,char * filename);
struct node * latex_print_r(struct node * head,FILE *fil);

int main()
{

  int i,n,big_n,count;
  
  printf("How many elements? ");
  scanf("%d",&n);
  
  big_n=0;
  
  while(big_n<n)
    {
      printf("Largest element? ");
      scanf("%d",&big_n);
    }
  
  struct node * root=make_node(rand()%big_n);
  
  count=1;
  
  int element;
    
  while(count<=n)
  {
    element=rand()%big_n;
    fflush(stdout);
    if(find_entry(root,element)==NULL)
      {
	root=add_node(root,element);
	count++;
      }
  }


  /*
    
    int i,n;
    
    printf("How many elements? ");
    scanf("%d",&n);
    
    struct node * root=make_node(n-1);
    
    for(i=n-2;i>=0;i--)
    root=add_node(root,i);
    
    printf("\n");
    
  */

  latex_print(root,"tree.tex");

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
  a_node->balance=0;
  a_node->right=NULL;
  a_node->left=NULL;

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


struct node * add_node(struct node * root,int new_entry)
{
  int work_needed;
  return add_node_r(root,new_entry,& work_needed);

}

struct node * add_node_r(struct node * here,int new_entry,int * work_needed)
{
  
  if(here==NULL)
    {
      *work_needed = 1;
      return make_node(new_entry);
    }
  
  if(new_entry<here->entry)
    {
      here->left = add_node_r(here->left,new_entry,work_needed);
      if(*work_needed)
	{
	  switch(here->balance)
	    {
	    case -1:
	      here->balance=0;
	      *work_needed=0;
	      return here;
	    case 0:
	      here->balance=1;
	      //*work_needed=1 already, doesn't need to be set.
	      return here;
	    case 1:
	      if(here->left->balance==1)
		here=rotate_ll(here);
	      else
		here=rotate_lr(here);
	      *work_needed=0;
	      return here;
	    }
	}
    }
  else
    {
      here->right =add_node_r(here->right,new_entry,work_needed);
      if(*work_needed)
	{
	  switch(here->balance)
	    {
	    case 1:
	      here->balance=0;
	      *work_needed=0;
	      return here;
	    case 0:
	      here->balance=-1;
	      return here;
	    case -1: 
	      if(here->right->balance==-1)
		here=rotate_rr(here);
	      else 
		here=rotate_rl(here);
	      *work_needed=0;
	      return here;
	    }
	}
    }
  
  return here;

}

void quick_print(struct node * root)
{
  printf("%d:%i",root->entry,root->balance);
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

int max(int a, int b)
{
  return a>b ? a:b;
}

struct node * rotate_ll(struct node * here)
{
  struct node * left = here->left;
  here->left=left->right;
  left->right=here;
  here->balance=0;
  here=left;
  here->balance=0;

  return here;
}

struct node * rotate_rr(struct node * here)
{
  struct node * right = here->right;
  here->right=right->left;
  right->left=here;
  here->balance=0;
  here=right;
  here->balance=0;

  return here;
}

struct node * rotate_lr(struct node * here)
{
  struct node * left=here->left;
  struct node * left_right=left->right;

  left->right=left_right->left;
  left_right->left=left;

  here->left=left_right->right;
  left_right->right=here;
		  
  if(left_right->balance==1)
    here->balance=-1;
  else
    here->balance=0;
  
  if(left_right->balance==-1)
    left->balance=1;
  else
    left->balance=0;
		  
  here=left_right;
  
  here->balance=0;
  
  return here;
}

struct node * rotate_rl(struct node * here)
{
  struct node * right=here->right;
  struct node * right_left=right->left;

  right->left=right_left->right;
  
  right_left->right=right;
  here->right=right_left->left;
  right_left->left=here;
  
  if(right_left->balance==-1)
    here->balance=1;
  else
    here->balance=0;
  
  if(right_left->balance==1)
    right->balance=-1;
  else
    right->balance=0;
  
  here=right_left;

  here->balance=0;

  return here;

}

struct node * latex_print(struct node * head,char * filename)
{

  FILE *fil;
  fil=fopen(filename,"wt");

  fprintf(fil,"\\documentclass[11pt,a4paper]{scrartcl}\n");
  fprintf(fil,"\\typearea{12}\n");
  fprintf(fil,"\\usepackage{tikz-qtree}\n");
  fprintf(fil,"\\begin{document}\n");
  fprintf(fil,"\\tikzset{every tree node/.style={minimum width=2em,draw,circle},\n");
  fprintf(fil,"blank/.style={draw=none},\n");
  fprintf(fil,"edge from parent/.style=\n");
  fprintf(fil,"{draw,->, edge from parent path={(\\tikzparentnode) -- (\\tikzchildnode)}},\n");
  fprintf(fil,"level distance=1.5cm}\n");
  fprintf(fil,"\\begin{figure}\n");
  fprintf(fil,"\\begin{center}\n");
  fprintf(fil,"\\begin{tikzpicture}\n");
  fprintf(fil,"\\Tree\n");
  
  head=latex_print_r(head,fil);

  fprintf(fil,"\\end{tikzpicture}\n");
  fprintf(fil,"\\end{center}\n");
  fprintf(fil,"\\end{figure}\n");
  fprintf(fil,"\\end{document}\n");

  fclose(fil);

  return head;

}

struct node * latex_print_r(struct node * head,FILE *fil)
{

  if(head==NULL)
    {
      fprintf(fil,"\\edge[blank]; \\node[blank]{};\n");
      return head;
    }

  if(head->left==NULL&&head->right==NULL)
    {
      fprintf(fil,"\\edge;{%i}\n",head->entry);
      return head;
    }

  fprintf(fil,"[.%i \n",head->entry);
  
  head->left=latex_print_r(head->left,fil);
  head->right=latex_print_r(head->right,fil);

  fprintf(fil,"]\n");

  return head;

}
