#ifndef MYTHREAD_H_
#define MYTHREAD_H_

#include "queue.h"
#include <pthread.h>

//Process Control Block
typedef struct PCB{
	int pid;           //Process ID.
	int start;         //Start Index in the Disk.
	int end;           //End index in the Disk.
	Queue* toDoQueue;  //todo queue
	pthread_cond_t  sleep_cond;
	pthread_mutex_t mutex;
}PCB;

typedef struct CharArr{
	char input [1024];
}CharArr;

typedef struct Command{
	char* type;
	void* first;
	void* second;
	void* third;
	void* forth;
	void* fifth;
}Command;


void runThread(); //PCB* myPCB
void handleRequest(Command* command);


#endif /*MYTHREAD_H_*/