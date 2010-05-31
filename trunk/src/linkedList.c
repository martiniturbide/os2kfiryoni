#include "linkedList.h"


List *createList(){
	List *newList = malloc(sizeof (List));
	newList->first = 0;
	newList->size = 0;
	return newList;
}

void addVal(List* l,int p){
	link *newLink = malloc(sizeof (link));
	newLink->val = p;
	if (l->first != 0){
		link* temp = l->first;
		l->first = newLink;
		newLink->next = temp;
	}
	else {
		l->first = newLink;
		newLink->next = 0;
	}
	l->size++;

}


int removeFirst(List* l){
	link* temp = l->first;
	int ans = temp->val;
	l->first = temp->next;
	free(temp);
	l->size--;
	return ans;
}

int removeInt(List *l, int n){
	link* pos = l->first;
	link* prev = 0;
	while (pos != 0){
		if (pos->val == n){
			if (prev != 0){
				prev->next = pos->next;
			}
			else
				l->first = l->first->next;
			l->size--;
			return 1;
		}
		else{
			prev = pos;
			pos = pos->next;
		}
	}
	return 0; //Hasn't found.
}


int top(List* l){
	return l->first->val;
}

int isEmpty(List *l){
	if (l->size == 0)
		return 1;
	return 0;
}

void freeAllList(List *l){
	if (l != 0){
		link *pos = l->first;
		while (pos != 0){
			free(pos);
			pos = pos->next;
		}
		free(l);
	}
}