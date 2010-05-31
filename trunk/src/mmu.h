#ifndef MMU_H_
#define MMU_H_
#include "dataBase.h"

typedef struct entry{
	int pid;
	int N;
	int dirtyBit;
	int referenceBit;
	int index;
	struct entry* next;
	struct entry *prev;
}entry;


entry** IPT;
int* HAT;  //the hash table - points to the IPT entries


void createMMU();
int hashFunc(int pid, int n);
Page* getPhisicalAddrs(int pid, int pageNum, int diskStart);
int isCorrectEntry(entry* iptPointer, int va, int pid);

#endif /*MMU_H_*/
