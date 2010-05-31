#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tokenizing.h"
#include "user_interface.h"



int startUI(){
	char inputLine[1024];
	deleteInputLine(inputLine);
	printf("> ");
	
	while (fgets(inputLine, 1024, stdin)){
		Console_data* input_data = malloc(sizeof(Console_data));
		int lineLength = strlen(inputLine);
		strncpy(input_data->inputFixed, inputLine, lineLength -1); //cut the '\n' char from the line
		input_data->wordsList = parse(input_data->inputFixed, " ", "\0\n");
		deleteInputLine(inputLine);
		
		if(strcmp(input_data->wordsList->str, "exit") == 0){ //check exit
			user_interface_destructor();
			printf("System Exits\n");
			exit(1);
		}

		int pid = fork();
		if (pid == 0){	//child			
			read_from_console(input_data);
			return 1;

		}
		if (pid != 0){  //parent
			printf("> ");
			/*if (fgets(inputLine, 2024, stdin) == 0)
				return 0;*/
		}
		
	}
	
	return 1;
}


int read_from_console(Console_data * input){
	
	if(strcmp(input->wordsList->str, "createProcess") == 0){
		printf("@CREATE PROCESS\n");
	}
	else if (strcmp(input->wordsList->str, "delProcess") == 0){
		input->wordsList = input->wordsList->next;
		if (input->wordsList == 0){
			printf("thread number missing\n");
		}else {
			int stat = atoi(input->wordsList->str);
			printf("@DEL PROCESS NUM: %d\n" , stat);
		}
	}else if (strcmp(input->wordsList->str, "read") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 3)
			printf("@READ: %s, %s, %s\n" , input->wordsList->str, input->wordsList->next->str, input->wordsList->next->next->str);
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "loopRead") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 4)
			printf("@LOOP READ: %s, %s, %s, %s\n" , input->wordsList->str, input->wordsList->next->str, input->wordsList->next->next->str, input->wordsList->next->next->next->str);
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "readToFile") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 4)
			printf("@READTOFILE: %s, %s, %s, %s\n" , input->wordsList->str, input->wordsList->next->str, input->wordsList->next->next->str, input->wordsList->next->next->next->str);
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "loopReadToFile") == 0){
			input->wordsList = input->wordsList->next;
			if (length(input->wordsList) == 5)
				printf("@LOOPREADTOFILE: %s, %s, %s, %s, %s\n" , input->wordsList->str, input->wordsList->next->str, input->wordsList->next->next->str, input->wordsList->next->next->next->str, input->wordsList->next->next->next->next->str);
			else
				printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "write") == 0){
			input->wordsList = input->wordsList->next;
			if (length(input->wordsList) == 3)
				printf("@WRITE: %s, %s, %s\n" , input->wordsList->str, input->wordsList->next->str, input->wordsList->next->next->str);
			else
				printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "loopWrite") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 5)
			printf("@LOOPWRITE: %s, %s, %s, %s, %s\n" , input->wordsList->str, input->wordsList->next->str, input->wordsList->next->next->str, input->wordsList->next->next->next->str, input->wordsList->next->next->next->next->str);
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "hitRate") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 0)
			printf("@HITRATE: \n");
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "printMM") == 0){
			input->wordsList = input->wordsList->next;
			if (length(input->wordsList) == 0)
				printf("@PRINTMM: \n");
			else
				printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "printMMUTable") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 0)
			printf("@PRINTMMUTABLE: \n");
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "printRegisters") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 0)
			printf("@PRINTREGISTERS: \n");
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "printHat") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 0)
			printf("@PRINTHAT: \n");
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "monitor") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 0)
			printf("@MONITOR: \n");
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "noMonitor") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 0)
			printf("@NOMONITOR: \n");
		else
			printf("arguments error \n");
	}else if (strcmp(input->wordsList->str, "batchFile") == 0){
		input->wordsList = input->wordsList->next;
		if (length(input->wordsList) == 1)
			printf("@BATCHFILE: %s\n", input->wordsList->str);
		else
			printf("arguments error \n");
	}
	else{
		printf("unknown command \n");
	}
		
	
	deleteVariables(input);
	return 1;
}



//this function initialize the loop variables
int deleteVariables(Console_data * input_data){
	if (input_data->wordsListHeadPointer != 0)
		free_list(input_data->wordsListHeadPointer);
	int i=0;
	for (; i<1024; i++){
		input_data->inputFixed[i] = 0;
	}
	input_data->wordsList = 0;
	return 1;
}

int deleteInputLine(char * inputLine){
	int i =0;
	for (; i<1024; i++){
		inputLine[i] = 0;
	}
	return 1;
}


int user_interface_destructor(){
	//delete variables
	return 1;
}


