#include "mmu.h"
#include "prm.h"
#include <pthread.h>

//Use to synchronize the PRM.
//extern pthread_mutex_t condition_mutex;
//extern pthread_cond_t  prm_cond;


void createMMU(){
	IPT = malloc(NumOfPagesInMM * sizeof(entry*));
	HAT = malloc(NumOfPagesInMM * sizeof(int));
	
	int i;
	for (i=0; i< NumOfPagesInMM; i++){ //init the HAT to nulls
		HAT[i] = -1;
		IPT[i] = 0;
	}
}


int hashFunc(int pid, int n){
	return (pid*n)%NumOfPagesInMM;
}


Page* getPhisicalAddrs(int pid, int pageNum, int diskStart){
	int found = 0;
	entry* iptPointer;
	int hashIndex = hashFunc(pid, pageNum);
	int iptIndex =  HAT[hashIndex];
	
	
	if(iptIndex != -1){
		iptPointer = IPT[iptIndex];
		while (!found){
			if (iptPointer==0){ //null pointer
				break;
			}else if (isCorrectEntry(iptPointer, pageNum, pid)){
				found = 1;
			}else if(iptPointer->next == NULL){ //check if the next is null
				break;
			}else{
				iptPointer = iptPointer->next;
			}
		}
	}
	
	//return the page from MM or Null if it does not exist
	if (found)
		return MM[iptPointer->index];
	
	else{
		printf("Insert new request to the prm, and call recursuive\n");
		insertRequest(pid, diskStart, diskStart);
		return getPhisicalAddrs(pid,pageNum,diskStart);
	}	
}


//check if the given entry is the requested entry
int isCorrectEntry(entry* iptPointer, int va, int pid){
	if (iptPointer!=0 && iptPointer->pid == pid && iptPointer->N == va)
		return 1;
	else
		return 0;
}



//main that checks the MMU logic
/*int main2(){
	NumOfPagesInMM = 10;
	createDataBase();
	createMMU();
	
	//entries in the IPT - en1 point next to en2
	entry en2 = {.pid = 2, .N = 2, .dirtyBit =0, .referenceBit=0, .index=2 ,.next=0, .prev=0};
	entry en1 = {.pid = 2, .N = 3, .dirtyBit =0, .referenceBit=0, .index=1 ,.next=&en2, .prev=0};
	
	IPT[1] = &en1;
	IPT[2] = &en2;
	
	//pointer from the hash to the IPT
	HAT[4] = 1;
	
	//pages in the MM
	Page pg1 = {.pageArray = 1};
	Page pg2 = {.pageArray = 2};
	MM[1] = &pg1;
	MM[2] = &pg2;
	
	Page* ans1 = getPhisicalAddrs(2,2); //ans1 array should contain 2
	Page* ans2 = getPhisicalAddrs(3,4); //ans2 array should contain 0 - not found
	
	return 1;
}*/

