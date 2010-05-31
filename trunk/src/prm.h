#ifndef PRM_H_
#define PRM_H_

#include "linkedList.h"
#include "mmu.h"
#include "queue.h"
#include <pthread.h>



pthread_t prm_thread;


//Struct for page request.
typedef struct pageReq{
	int pid;    	//Process ID.
	int diskStart; //Start Index in the Disk.
	int pageNum;   //Page Number.
}pageReq;


Queue *pageRequests;

//Initialize the pthred for the PRM.
void initPRM();

//Runnable func for the PRM.
void *runPRM();

//Insert new request to the queue.
void insertRequest(int pid, int pageNUm, int diskStart);

//Load page from the Disk to the MM.
int loadPage(int processID, int pageNum, int diskStart);

//extract min regiters index into list.
List* extractMinRegiters(int *regs);

//Create new Entry.
entry* createEntry(int PID, int N, int index, entry* next, entry* prev);

//Replace page with exsit one.
int replacePageInMM(int index, int processID, int pageNum, int diskStart);

//Extract min Int value from list.
int extractMinIntVal(List *l);


#endif /*PRM_H_*/
