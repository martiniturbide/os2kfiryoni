#include "myThread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataBase.h"

void runThread(PCB* myPCB){
	printf("Thread num %d created\n", myPCB->pid);
	while (1){	
		pthread_mutex_lock(&myPCB->mutex);// lock the critical section
		
		//while(myPCB->toDoQueue->size == 0){
	    	printf("Thread num %d is going to sleep\n", myPCB->pid);
	    	pthread_cond_wait(&myPCB->sleep_cond, &myPCB->mutex);
	    //}
		printf("Thread num %d waked up\n", myPCB->pid);
		
		qNode* firstNode = removeFirstNode(myPCB->toDoQueue);
	    pthread_mutex_unlock(&myPCB->mutex);
	    
	    
	    //handleRequest((Command*)firstNode->val);
	    //free(firstNode->val);
	    //free(firstNode);
    
	    
   }
}




void handleRequest(Command* command){
	if (strcmp(command->type,"read")){
		
	}else if (strcmp(command->type,"loopRead")){
		
	}else if (strcmp(command->type,"readToFile")){
		
	}else if (strcmp(command->type,"loopReadToFile")){
		
	}else if (strcmp(command->type,"write")){
		
	}else if (strcmp(command->type,"loopWrite")){
		
	}
	
}

int testThreads(){  //(MAIN)
	initializeAllProgram();
	MaxNumOfProcesses = 3;
	createProcess();
	createProcess();
	
	
	while (1){
		qNode* node = ThreadsQueue->first;
		while (node != 0){
			PCB* pcb = ((ThreadData*)node->val)->pcb;
			pthread_cond_signal ( &pcb->sleep_cond);
			node = node->next;
		}
	}
	
}

