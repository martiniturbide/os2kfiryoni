//#include "linkedList.h"
//#include "mmu.h"
#include "dataBase.h"
#include "prm.h"
#include <pthread.h>
//#include "mutex_vars.h"

//extern pthread_t prm_thread;

pthread_mutex_t prm_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  prm_cond2  = PTHREAD_COND_INITIALIZER;


pthread_t t1,t2;

void initializeAllProgram();
void testPrm();
void printAll();
void *runPRM2();
void initPRM2();
void insertRequest2(int pid, int pageNum, int diskStart);
void* insert2();






int main(){


	testPrm();
	
	initPRM();
	int i;
	for (i = 0; i < 30; ++i) {
		loadPage(1,0,0);
		
	}
	printMM();
	

	//pthread_create(&t1, NULL, insert2, NULL);
	//pthread_join(prm_thread, NULL);
	//pthread_join(t1,NULL);

	return 1;
}


void* insert2(){
	printf("insrt2\n");
	int n = 0;
	while(1){

		//printf("insrt2\n");
		insertRequest(1,0,0);
		n++;
		if (n == 30)
			break;
		//pthread_cond_timedwait(&prm_cond2, &prm_mutex2, 1000);
	}
}

void initPRM2(){
	pageRequests = createQueue();
	pthread_create(&t1, NULL, runPRM2, NULL);
	pthread_create(&t2, NULL, runPRM2, NULL);


	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}

//Runnable func for the PRM.
void *runPRM2(){
	printf("AAAAA\n");

	while(1){
		//Lock the mutex.
		pthread_mutex_lock( &prm_mutex2 );
		printf("Size: %d\n",isEmptyQueue(pageRequests));
		while(isEmptyQueue(pageRequests)){
			printf("Size: %d\n",isEmptyQueue(pageRequests));
			pthread_cond_wait( &prm_cond2, &prm_mutex2 );
			printf("Size: %d\n",isEmptyQueue(pageRequests));
		}
		//Remove first request from the queue.
		pageReq *curReq = (pageReq*)removeFirstNode(pageRequests);
		pthread_mutex_unlock( &prm_mutex2 );

		loadPage(curReq->pid, curReq->pageNum, curReq->diskStart);

		if (curReq != 0)
			free(curReq);
		else
			printf("Error free prm.c line 38\n");

	}
}

//Insert new request to the queue.
void insertRequest2(int pid, int pageNum, int diskStart){
	pageReq *newReq = malloc(sizeof (pageReq));
	newReq->pid = pid;
	newReq->pageNum = pageNum;
	newReq->diskStart = diskStart;
	//Lock the mutex.
	pthread_mutex_lock( &prm_mutex2 );	 //Lock the mutex.
	addNode(pageRequests, newReq);    //Insert the request to the queue.
	pthread_cond_signal( &prm_cond2 ); //Wake up the prm.
	pthread_mutex_unlock( &prm_mutex2 );  //Release the mutex.

}

void testPrm(){
	NumOfPagesInMM = 3;
	NumOfPagesInDisk = 5;
	MaxNumOfProcesses = 6;
	PageSize = 2;
	initializeAllProgram();
	int* arr = malloc(2 * sizeof (int));
	arr[0] = 9;
	arr[1] = 99;
	int* arr2 = malloc(2 * sizeof (int));
	arr2[0] = 100;
	arr2[1] = 1000;
	Page *p1 = malloc(sizeof (Page));
	p1->pageArray = arr;
	Page *p2 = malloc(sizeof (Page));
	p2->pageArray = arr2;


	Disk[0] = p1;
	Disk[1] = p1;
	//while (!isEmpty(freePages))
	//removeFirst(freePages);
	MM[0] = p2;
	entry* newE = malloc(sizeof (entry));
	newE->dirtyBit = 1;
	IPT[0] = newE;



}

void printAll(){
	//List *l = createList();
	printMM();
	printMMUTable();
	printDisk();
	printRegisters();
	printHat();
}


void initializeAllProgram(){
	createDataBase();
	createMMU();
}