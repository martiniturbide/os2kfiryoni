#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataBase.h"
#include "prm.h"
#include "mmu.h"
#include "myThread.h"

void checkThread(){
	printf("NEW THREAD NEW THREAD");
}

//Create new process.
int createProcess(){
	if (ThreadsQueue->size <= MaxNumOfProcesses){
		pthread_t newThread;
		PCB* pcb = malloc(sizeof(PCB));  //init the PCB
		pcb->pid = ThreadsCounter;
		ThreadsCounter++;
		pcb->start = NULL;  		//**** SHOULD BE FROM DISK ****
		pcb->start = NULL;  		//**** SHOULD BE FROM DISK ****
		pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;
		pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
		pcb->sleep_cond = condition_cond;
		pcb->mutex = condition_mutex;
		createQueue(pcb->toDoQueue);
	
		ThreadData* data = malloc(sizeof(ThreadData));
		data->pcb = pcb;
		data->thisThread = newThread;
		addNode(ThreadsQueue,data); //added to the threads queue
		pthread_create(&newThread, NULL, &runThread, (void*)pcb);
		
		return 1;
	}
	return 0;
}

//read (b).
void read(int vAddr, int id, int amount){
	
}

//loop Read (c).
void loopRead(int vAddr, int id, int off, int amount){
	
}

//read to file (d).
void readToFile(int vAddr,int id, int amount, char* filename){
	
}

//loop Read to file  (e).
void loopReadToFile(int vAddr, int id, int off, int amount, char* filename){
	
}

//Write (f).
void writeReg(int vAddr, int id, char* s){
	
}

//Write ad descrived in (i).
void write(int vAddr, char* c, int amount){
	
}

//loopWrite (g).
void loopWrite(int vAddr, int id, char c, int off, int amount){
	
}


//Print the hit rate.
void printHitrate(){
	printf("Hitrate:%d\n",hit / readTotal);
}

//Print the MM.
void printMM(){
	int i,j;
	for (i = 0; i < NumOfPagesInMM; ++i) {
		printf("MM[%d]:\n",i);
		for (j = 0; j < PageSize; ++j) {
			if (MM[i] != 0){
				int n = MM[i]->pageArray[j];
				printf("Page[%d] = %d\n",j,n);
			}
			else{
				printf("empty\n");
				break;
			}
		}
		printf("\n");
	}
}

void printMMUTable(){
	int i;
	printf("MMUTable:\n");
	for (i = 0; i < NumOfPagesInMM; ++i) {
		if(IPT[i] != 0){
			entry *cur = IPT[i];
			printf("pid:%d, pageNum:%d, dirty bit:%d, aging reference bit:%d, next:%d, prev:%d\n",
				   cur->pid, cur->N, cur->dirtyBit, cur->referenceBit, (int)cur->next, (int)cur->prev);
		}
		else
			printf("free\n");	
	}
	printf("\n");
}


//Print the registers.
void printRegisters(){
	int i;
	printf("Registers:\n");
	for (i = 0; i < NumOfPagesInMM; ++i) {
		printf("%d. %d\n",i,Regs[i]);
	}
	printf("\n");
}

//Print the HAT table.
void printHat(){
	int i;
	printf("HAT:\n");
	for (i = 0; i < NumOfPagesInMM; ++i) {
		printf("%d\n",HAT[i]);
	}
	printf("\n");
}

//turn on the simulator.
void monitorOn(){
	monitor = 1;
}

//turn off the simulator.
void MonitorOff(){
	monitor = 0;
}

//clean the memory & exit the simulator.
void cleanAndExit(){

}

void printDisk(){
	int i,j;
		for (i = 0; i < NumOfPagesInDisk; ++i) {
			printf("Disk[%d]:\n",i);
			for (j = 0; j < PageSize; ++j) {
				if (Disk[i] != 0){
					int n = Disk[i]->pageArray[j];
					printf("Page[%d] = %d\n",j,n);
				}
				else{
					printf("empty\n");
					break;
				}
			}
			printf("\n");
		}
}