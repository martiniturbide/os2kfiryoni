#ifndef DATABASE_H_
#define DATABASE_H_

#include "linkedList.h"
#include "readFromFile.h"
#include "myThread.h"



typedef struct Page{
	int* pageArray;
}Page;

typedef struct ThreadData{
	pthread_t thisThread;
	PCB* pcb;
}ThreadData;



//Configuration File Data - supposed to be init from file
int ThreadsCounter;
int MaxNumOfProcesses;
int PageSize;
int NumOfPagesInMM;
int NumOfPagesInDisk;
int NumOfProcessPages; 
int ShiftClock;
int monitor; //Bool var for the monitor status.

//Data Structures

Page** Disk; 			//Disk.
Page** MM;  			//Main Memory.
int* MmDiskMap;   		//Eeach index in the MM array point to his index in the disk array.
List *freePages; 		//Free List - list of free pages in the MM array.
int *Regs;  			//Register for each pysical Thread.
Queue* ThreadsQueue; 	//Contains all the threads


//Statistics Vars.
int readTotal;  //How many calls to the read from MM.
int hit;		//How many hit without need to page in from the Disk.

//Functions
void createDataBase();

#endif /*DATABASE_H_*/
