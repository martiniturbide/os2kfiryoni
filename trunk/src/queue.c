#include "queue.h"

Queue* createQueue(){
	Queue *newQueue = malloc(sizeof (Queue));
	newQueue->first = 0;
	newQueue->last = 0;
	newQueue->size = 0;
	return newQueue;
}

void  addNode(Queue* q,void* toAdd){
	qNode *newNode = malloc(sizeof (qNode));
	newNode->val = toAdd;
	if (q->last == 0){ //the first element
		q->first = newNode;
		q->last = newNode;
	}
	else {  //not the first - add to the end of the queue
		q->last->next = newNode;
		q->last = newNode;		
	}
	q->size++;
}

int removeFirstAndDelete(Queue* q){
	if (q == 0 || q->size==0)
		return 0;
	
	qNode* temp = q->first;
	if (q->size == 1){ //in case of one node
		q->last = 0;
	}
	q->first = q->first->next;
	if (temp != 0)
		free(temp);
	if (temp->val != 0)
		free(temp->val);
	q->size--;
	
	return 1;
}


void* removeFirstNode(Queue* q){
	if (q == 0 || q->size==0)
		return 0;
	
	qNode* temp = q->first;
	if (q->size == 1){ //in case of one node
		q->last = 0;
	}
	q->first = q->first->next;
	q->size--;
	
	void* value = temp->val;
	free(temp);
	return value;
}


int removeNodeAt(Queue *q, int index){
	if (q->size < index+1){  //invaild node
		return 0;
	}
	
	int currentIndex = 0;
	qNode* currentNode = q->first;
	qNode* prevNode = 0;
	while (currentIndex < index){
		currentIndex++;
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
	
	if (currentNode == q->first){
		removeFirstAndDelete(q);
	}
	else if (currentNode == q->last){
		q->last = prevNode;
		free(currentNode->val);
		free(currentNode);
		q->size--;
	}
	else{
		prevNode->next = currentNode->next;
		free(currentNode->val);
		free(currentNode);
		q->size--;
	}
	return 1;	
}


void* getFirstNode(Queue* q){
	return q->first;
}

void* getLastNode(Queue* q){
	return q->last;
}
int isEmptyQueue(Queue *q){
	if (q->size == 0)
		return 1;
	return 0;
}
int queueSize(Queue *q){
	return q->size;
}

void freeAllQueue(Queue *q){
	freeAllNodes(q->first);
	free(q);
}

void freeAllNodes(qNode* node){
   if(!node){
      return;
   }
   freeAllNodes(node->next);
   free(node->val);
   free(node);
}

//test the queue
/*int main2(){
	
	typedef struct INT{
		int value;
	}INT;
	
	Queue* q = createQueue();
	INT* element1 = malloc(sizeof(INT));
	INT* element2 = malloc(sizeof(INT));
	INT* element3 = malloc(sizeof(INT));
	INT* element4 = malloc(sizeof(INT));
	element1->value = 1;
	element2->value = 2;
	element3->value = 3;
	element4->value = 4;
	
	addNode(q, element1);
	addNode(q, element2);
	addNode(q, element3);
	addNode(q, element4);
	
	//removeFirstNode(q);
	//removeFirstNode(q);
	//removeFirstNode(q);
	//removeFirstNode(q);
	
	removeNodeAt(q, 2);
	removeNodeAt(q, 0);
	removeNodeAt(q, 1);
	removeNodeAt(q, 0);
	
	//freeAllNodes(q);
}
*/