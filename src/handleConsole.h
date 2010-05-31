#ifndef HANDLECONSOLE_H_
#define HANDLECONSOLE_H_

#include "dataBase.h"
#include "prm.h"


int createProcess();
void read(int vAddr, int id, int amount);
void loopRead(int vAddr, int id, int off, int amount);
void readToFile(int vAddr,int id, int amount, char* filename);
void loopReadToFile(int vAddr, int id, int off, int amount, char* filename);
void writeReg(int vAddr, int id, char* s);
void write(int vAddr, char* c, int amount);
void loopWrite(int vAddr, int id, char c, int off, int amount);
void printHitrate();      //Print the hitrate.
void printMM();           //Print the MM Table.
void printMMUTable();	  //Print the MMU Table.
void printRegisters();    //Print the registers.
void printHat();          //Print the HAT table.
void monitorOn();           //turn on the simulator.
void MonitorOff();		  //turn off the simulator.
void cleanAndExit();    //clean the memory & exit the simulator.
void printDisk();

#endif /*HANDLECONSOLE_H_*/
