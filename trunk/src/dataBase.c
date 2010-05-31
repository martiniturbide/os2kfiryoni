#include "dataBase.h"




void createDataBase(){
	//Read from file first.
	readFromFile(&NumOfPagesInMM, &NumOfPagesInDisk, &MaxNumOfProcesses);
	
	//Initalize the data structers.
	ThreadsCounter = 0;
	MM = malloc(NumOfPagesInMM * sizeof(Page*));
	Disk = malloc(NumOfPagesInDisk * sizeof(Page*));
	MmDiskMap = malloc(NumOfPagesInMM * sizeof (int));
	freePages = createList();
	ThreadsQueue = createQueue();
	

	//Add all the pages first.
	int i;
	for (i=0; i<NumOfPagesInMM; i++){  //init the free pages
		addVal(freePages,i);
	}
	//Init the registers.
	Regs = malloc (NumOfPagesInMM * sizeof (int));
	for (i = 0; i < NumOfPagesInMM; ++i) {
		Regs[i] = 0;
	}


}

