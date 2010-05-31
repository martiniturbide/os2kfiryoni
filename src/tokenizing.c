#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokenizing.h"

/* This function adds a string to the linked list */
void add_to_list(List **l, char *element)
{
  List *e;

  
  if (*l == NULL)
    {
      (*l)= (List *)malloc(sizeof(List));
      (*l)->str = (char *)malloc(strlen(element)+1);
      strcpy((*l)->str, element);
      (*l)->next = NULL;
    }
  else
    if ((*l)->next!= NULL)
       add_to_list(&(*l)->next, element);
    else
      {
        e = (List *)malloc(sizeof(List));
        e->str = (char *)malloc(strlen(element)+1);
        strcpy(e->str, element);
        e->next = NULL;
        (*l)->next = e;
      }
}

/* Function parse() parses a string of characters into parts separated
 by one of the delimiters until one of forbidden characters is found.
 Parameters: str - a string to parse,
             delimiters - a string of possible delimiters,
             forbidden - a string of characters on which the parsing stops.
 Return value: a linked list of tokens. */
List *parse(char *str, char *delimiters, char *forbidden)
{
  char *token;
  List *l=NULL;
  char *s, *str2;

  str2 = (char *)malloc(strlen(str)+1);
  strcpy(str2, str);
  s=strtok(str2, forbidden);

  token = strtok(s, delimiters);
 
 while (token != NULL)
    {
       add_to_list(&l, token);
       token = strtok(NULL, delimiters);
    }

 return l;
}

/* This function prints the linked list of strings */
void print_list(List *l)
{
  
  if (l!= NULL)
    {
      printf("%s\n",l->str); 
      print_list(l->next);
    }
}

/* returns length of string */
int length(List *l)
{
  if (l == NULL)
    return 0;
  else return 1+length(l->next);
}

void free_list(List * list)
{
   if(!list)
   {
      return;
   }
   free_list(list->next);
   free(list->str);
   free(list);      
}
