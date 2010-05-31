#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>


typedef struct qNode{
	void* val;
	struct qNode *next;
}qNode;

typedef struct Queue{
	qNode* first;
	qNode* last;
	int size;
}Queue;


Queue* createQueue();
void  addNode(Queue* q,void* toAdd);
int removeFirstAndDelete(Queue* q);
void* removeFirstNode(Queue* q);
int removeNodeAt(Queue *q, int index);
void* getFirstNode(Queue* q);
void* getLastNode(Queue* q);
int isEmptyQueue(Queue *q);
int queueSize(Queue *q);
void freeAllQueue(Queue *q);
void freeAllNodes(qNode* node);

#endif /*QUEUE_H_*/
