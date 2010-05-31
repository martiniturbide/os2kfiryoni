#include "dataBase.h"
#include "prm.h"
#include "handleConsole.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "mutex_vars.h"



pthread_mutex_t prm_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  prm_cond = PTHREAD_COND_INITIALIZER;



void initPRM(){
	pageRequests = createQueue();
	pthread_create(&prm_thread, NULL, runPRM, NULL);
}

//Runnable func for the PRM.
void *runPRM(){
	int n = 0;
	printMM();
	while(1){
		//Lock the mutex.
		pthread_mutex_lock( &prm_mutex );
		//printf("isEmpty: %d\n",isEmptyQueue(pageRequests));
		while(isEmptyQueue(pageRequests)){
			pthread_cond_wait( &prm_cond, &prm_mutex );
		}
		//printf("isEmpty: %d\n",isEmptyQueue(pageRequests));
		//Remove first request from the queue.
		pageReq *curReq = (pageReq*)removeFirstNode(pageRequests);
		pthread_mutex_unlock( &prm_mutex );
		
		//printf("pid:%d ,pageNum:%d, diskStart:%d\n",curReq->pid, curReq->pageNum, curReq->diskStart);
		loadPage(curReq->pid, curReq->pageNum, curReq->diskStart);

		if (curReq != 0)
			free(curReq);
		else
			printf("Error free prm.c line 38\n");
		
	}
}


//Insert new request to the queue.
void insertRequest(int pid, int pageNum, int diskStart){
	pageReq *newReq = malloc(sizeof (pageReq));
	newReq->pid = pid;
	newReq->pageNum = pageNum;
	newReq->diskStart = diskStart;
	//Lock the mutex.
	//printf("insert Before Mutex\n");
	pthread_mutex_lock( &prm_mutex );
	//printf("insert After Lock Mutex\n");//Lock the mutex.
	addNode(pageRequests, newReq); 
	pthread_cond_signal( &prm_cond ); //Wake up the prm.
	pthread_mutex_unlock( &prm_mutex );  //Release the mutex.
	//printf("insert After Unlock Mutex\n");
	printf("Size of the page list%d\n",pageRequests->size);

}


//Load page from the Disk to the MM.
int loadPage(int processID, int pageNum, int diskStart){
	int hashIndex = hashFunc(processID, pageNum);
	int index;
	//If there is free page in the MM.
	if (!isEmpty(freePages)){
		index = removeFirst(freePages);
		MM[index] = Disk[diskStart + pageNum - 1];
		MmDiskMap[index] = diskStart + pageNum - 1;   //Map the MM page to it's place in the Disk.
		//Create new entry for the ipt.
		printRegisters();
		entry* newEntry = createEntry(processID,pageNum,index,0,0);
		printRegisters();
		if (HAT[hashIndex] == -1){  //The HAT cell is free.
			HAT[hashIndex] = index;
			IPT[index] = newEntry;
		}
		else{  //There is already content in the hash.
			if (IPT[HAT[hashIndex]] != 0){
				entry* pos = IPT[HAT[hashIndex]];
				entry* prev = 0;
				while(pos != 0){
					prev = pos;
					pos = pos->next;
				}
				prev->next = newEntry;
				newEntry->prev = prev;
			}
			else
				printf("prm.c - line 40, there is fulk cell in the hash, but empty in the IPT");

		}
	}
	//Replace existing Page in the MM.
	else {
		List* minRegiters = extractMinRegiters(Regs);
		if (minRegiters->size == 1){  //There is register with minimal value.
			index = removeFirst(minRegiters);
			replacePageInMM(index,processID,pageNum,diskStart);
		}//There is more than one minimal register.
		else{  
			int curIndex;
			List *cleanBit = createList();
			List *dirtyBit = createList();
			while (!isEmpty(minRegiters)){  //Extract the clean bit index if there is.
				curIndex = removeFirst(minRegiters);
				if (IPT[curIndex] != 0 && IPT[curIndex]->dirtyBit == 0)
					addVal(cleanBit, curIndex);
				else
					addVal(dirtyBit, curIndex);
			}
			if (cleanBit->size == 1){  //There is only one register with clean bit.
				index = removeFirst(cleanBit);
			}
			else if (cleanBit->size == 0){  //All the reisters with dirty bit.
				index = extractMinIntVal(dirtyBit);
			}
			else{ //There is more then one with dirty bit.
				index = extractMinIntVal(cleanBit);
			}
			replacePageInMM(index,processID,pageNum,diskStart);
			freeAllList(cleanBit);  //Free the etmp list.
			freeAllList(dirtyBit);
		}
		freeAllList(minRegiters);  //Free the temp list.
	}
	Regs[index] = 100000000;
	return 1;
}

//Create new Entry.
entry* createEntry(int PID, int N, int index, entry* next, entry* prev){
	entry* newEntry = malloc(sizeof (entry));
	newEntry->pid = PID;
	newEntry->N = N;
	newEntry->index = index;
	newEntry->next = next;
	newEntry->prev = prev;
	newEntry->dirtyBit = 0;
	newEntry->referenceBit = 0;
	return newEntry;
}


//Replace exsiting page in the MM.
int replacePageInMM(int index, int processID, int pageNum, int diskStart){
	int hashIndex = hashFunc(processID, pageNum);
	entry* newEntry = createEntry(processID,pageNum,index,0,0);
	entry* prev = 0;
	entry* next = 0;
	if(IPT[index] != 0){
		prev = IPT[index]->prev;
		next = IPT[index]->next;
		if(IPT[index]->dirtyBit == 1){ //Should write first.
			Disk[MmDiskMap[index]] = MM[index];
		}
		free(IPT[index]);
		if (prev != 0)
			prev->next = newEntry;  //Set the prev for null.
		if (next != 0)
			next->prev = newEntry;
		newEntry->next = next;  //Set the next for next.
		newEntry->prev = prev;
	}
	MM[index] = Disk[diskStart + pageNum - 1];
	MmDiskMap[index] = diskStart + pageNum - 1;   //Map the MM page to it's place in the Disk.
	if (HAT[hashIndex] == -1){
		HAT[hashIndex] = index;
		IPT[index] = newEntry;
	}
	else{
		if (IPT[HAT[hashIndex]] != 0){
			entry* pos = IPT[HAT[hashIndex]];
			entry* prev = 0;
			while(pos != 0){
				prev = pos;
				pos = pos->next;
			}
			prev->next = newEntry;
			newEntry->prev = prev;
		}
		else
			printf("prm.c - line 77, there is fulk cell in the hash, but empty in the IPT");

	}
	return 1;
}


//Extract the minimum registers indexes to a list.
List* extractMinRegiters(int *regs){
	List *ans = createList();
	int minVal = 900000000;
	int i;
	for (i = 0; i < NumOfPagesInMM; ++i) {
		if (regs[i] < minVal)
			minVal = regs[i];
	}
	for (i = 0; i < NumOfPagesInMM; ++i) {
		if (regs[i] == minVal)
			addVal(ans,i);
	}
	return ans;
}

//Extract min Int value from list.
int extractMinIntVal(List *l){
	if (l == 0)
		return -1;
	int min = l->first->val;
	link* pos = l->first;
	while (pos != 0){
		if (pos->val < min)
			min = pos->val;
		pos = pos->next;
	}
	return min;
}



