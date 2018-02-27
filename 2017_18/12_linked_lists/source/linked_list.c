//linked_list.c
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
  struct node *next;
};

void add_node(struct node * here, int new_entry);
void append_node(struct node * here, int new_entry);
void print_list(struct node * iterator);
struct node * make_head(int new_entry);
void delete_node(struct node * head, int delete_entry);
void delete_next(struct node * here);
struct node * locate(struct node * head, int target);

int main()
{
  struct node * a_list = make_head(5);
  add_node(a_list,7);
  add_node(a_list,10);
  add_node(a_list,15);
  struct node * here = locate(a_list,15);
  add_node(here,20);
  append_node(a_list,25);

  print_list(a_list);

  delete_node(a_list,20);

  printf("deleted 20 \n");

  print_list(a_list);


  delete_node(a_list,25);

  printf("deleted 25\n");

  print_list(a_list);


  delete_node(a_list,5);

  printf("deleted 5\n");

  print_list(a_list);


  delete_node(a_list,30);

  printf("deleted 30\n");

  print_list(a_list);

  delete_next(a_list);
  
  printf("deleted entry after head\n");

  print_list(a_list);

}

void print_list(struct node * iterator)
{
  while(iterator->next!=NULL)
    {
      printf("%d\n",iterator->entry);
      iterator=iterator->next;
    }

  printf("%d\n",iterator->entry);
}



void add_node(struct node * here, int new_entry)
{
  struct node * here_next=here->next;
  here->next = make_head(new_entry);
  here->next->next=here_next;
}

void append_node(struct node * head, int new_entry)
{
  while(head->next!=NULL)
    head=head->next;
  head->next = (struct node *)malloc(sizeof(struct node));
  head->next->entry=new_entry;
}


struct node * make_head(int new_entry)
{
  struct node * head = (struct node *)malloc(sizeof(struct node));
  head->entry=new_entry;
  head->next=NULL;
  return head;
}

void delete_node(struct node * head, int delete_entry)
{
  struct node * temp = (struct node *)malloc(sizeof(struct node));

  if(head->entry==delete_entry)
    {
      head->entry=head->next->entry;
      temp=head->next;
      head->next=head->next->next;
      free(temp);

    }
  else
    {
      struct node * iterator=head;
      while(iterator->next->entry!=delete_entry&&iterator->next->next!=NULL)
	iterator=iterator->next;
      if(iterator->next->entry==delete_entry)
	{
	  temp=iterator->next->next;
	  free(iterator->next);
	  iterator->next=temp;
	}
      else if(iterator->next->next==NULL&&iterator->next->entry==delete_entry)
	{
	  free(iterator->next->next);
	  iterator->next=NULL;
	}
    }

}

void delete_next(struct node * here)
{
  if(here->next==NULL)
    return;

  struct node * temp=here->next;
  here->next=here->next->next;
  free(temp);
  
}

struct node * locate(struct node * iterator, int target)
{
  while(iterator->next!=NULL)
    {
      if(iterator->entry==target)
	return iterator;
      iterator=iterator->next;
    }
  if(iterator->entry==target)
    return iterator;

  return NULL;
}
