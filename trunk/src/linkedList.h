#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>



typedef struct link{
	int val;
	struct link *next;
}link;

typedef struct List{
	link* first;
	int size;
}List;

List *createList();
void addVal(List* l,int p);
int removeFirst(List* l);
int removeInt(List *l, int n);
int top(List* l);
int isEmpty(List *l);
void freeAllList(List *l);


#endif /*LINKEDLIST_H_*/
