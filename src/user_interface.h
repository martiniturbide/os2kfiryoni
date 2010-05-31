#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

typedef struct Console_data{
	char inputFixed[1024];
	List* wordsList;
	List* wordsListHeadPointer;
} Console_data;

	//char inputLine[1024];
	//char inputFixed[1024];
	//List* wordsList;
	//List* wordsListHeadPointer;

	int startUI();
	int read_from_console();
	void handleRun();
	void handleLoad();
	void handleState();
	int deleteVariables(Console_data * input_data);
	int deleteInputLine(char * inputLine);
	
	int checkPriority(char* priorities);
	
	int user_interface_destructor();
	

#endif /*USER_INTERFACE_H_*/
;