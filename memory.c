#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "memory.h"
#define VNAME 20
#define VNUM 20

/*
*
* Data Structs
*
*/

struct frame{ //call
    char intArray[VNUM][VNAME];
	char recArray[VNUM][VNAME];

	int* intValues;
	int** recValues; 

	int intSize;
	int recSize;
};
static struct frame **frameArray;
static int fp;

/*
*
* Helper functions
*
*/

// If iden is an integer, return the index. Otherwise, return -1
static int searchInteger(char* iden){
	int location = -1;
	int i;
	for (i=0; i<frameArray[fp]->intSize; i++) {
		if (strcmp(frameArray[fp]->intArray[i], iden)==0) {
			location = i;
		}
	}
	return location;
}

static int searchRecord(char* iden){
	int location = -1;
	int i;
	for (i=0; i<frameArray[fp]->recSize; i++) {
		if (strcmp(frameArray[fp]->recArray[i], iden)==0) {
			location = i;
		}
	}
	return location;
}


static int searchPrevRecord(char* iden, struct frame *fm){
	int location = -1;
	int i;
	for (i=0; i<fm->recSize; i++) {
		if (strcmp(fm->recArray[i], iden)==0) {
			location = i;
		}
	}
	return location;
}

/*
*
* Memory functions
*
*/

//initialze the formal paramter with the argument of the function call
//If the number of paramter and argument do not matche, error is called
void initializeParam(char *arg1, char* arg2, char* param1, char* param2){
	
	if(arg2 == NULL && param2 != NULL){
		printf("InitializeParam Error: Unmateched Parameter\n");
		exit(0);
	}

	if(arg2 != NULL && param2 ==NULL){
		printf("InitializeParam Error: Unmateched Parameter\n");
		exit(0);
	}


	struct frame *fm = frameArray[fp-1];
	int argLocation1 = searchPrevRecord(arg1, fm);
	int paramLocaiton1 = searchRecord(param1);

	frameArray[fp]->recValues[paramLocaiton1] = fm->recValues[argLocation1];

	if(arg2 != NULL && param2 != NULL){
		int argLocation2 = searchPrevRecord(arg2, fm);
		int paramLocaiton2 = searchRecord(param2);

		frameArray[fp]->recValues[paramLocaiton2] = fm->recValues[argLocation2];
	}
}

//decrease the frame pointer
void stackOutFP(){
	frameArray[fp]=NULL;
	fp--;
}

//initialize frame pointer and frame array
void initializeFP(){
	fp=-1;
	frameArray = (struct frame**) calloc(20, sizeof(struct frame*));
}

//initialize the new frame
//called everytime when new function is called
void initializeSize(){
	fp++;
	struct frame *fm= (struct frame*) calloc(1, sizeof(struct frame));
	frameArray[fp]=fm;

	frameArray[fp]->intSize=0;
	frameArray[fp]->recSize=0;
}

// Initialize data structures
// Don't worry about freeing memory, will do that in project 5
void memory_init() {
	frameArray[fp]->intValues = (int*) calloc(frameArray[fp]->intSize, sizeof(int));
	frameArray[fp]->recValues = (int**) calloc(frameArray[fp]->recSize, sizeof(int));
}

// Handle an integer or record declaration
void declare(char* iden, int type) {


	if(type == INTEGER){
		strcpy(frameArray[fp]->intArray[frameArray[fp]->intSize], iden);
		frameArray[fp]->intSize++;
	}else if(type == RECORD){
		strcpy(frameArray[fp]->recArray[frameArray[fp]->recSize], iden);
		frameArray[fp]->recSize++;
	}

}

// Store a value to a variable. Remember, unindexed stores to a record go to index 0
void store(char* iden, int value) {
	int int_idx = searchInteger(iden);
	int rec_idx = searchRecord(iden);

	if(int_idx == -1 && rec_idx == -1){
		printf("Error: varialbe %s has not been declared\n", iden);
		exit(0);
	}
	if(int_idx != -1){
		frameArray[fp]->intValues[int_idx] = value;
	}
	if(rec_idx != -1){
		frameArray[fp]->recValues[rec_idx][1] = value;
	}
}

// Read a value from a variable. Remember, unindexed reads from a record read index 0
int recall(char* iden) {
	int value;
	int int_idx = searchInteger(iden);
	int rec_idx = searchRecord(iden);

	if(int_idx == -1 && rec_idx == -1){
		printf("Error: varialbe %s has not been declared\n", iden);
		exit(0);
	}
	if(int_idx != -1){
		value = frameArray[fp]->intValues[int_idx];
	}
	if(rec_idx != -1){
		value = frameArray[fp]->recValues[rec_idx][1];
	}

	return value;
}

// Store a value to a record variable, at the given index
void storeRec(char* iden, int index, int value) {
	//Search iden idx
		//if iden idx == -1 error non existing var
	//check index 
	//	if index < 0 error index must be Natural number
	//check recValues[iden idx]
		//if recValues[iden idx] == NULL   error uninitialization error
	//check iden size in recValues[iden idx][0]	
		//if recValues[iden idx][0]	 == index error ouside of array size
	//else
	//index++;
	//recValues[iden idx][index] = value
	int iden_idx = searchRecord(iden);
	if(iden_idx == -1){
		printf("Error: Record variable has not been declared\n");
		exit(0);
	}
	if(index < 0){
		printf("Error: Index must be natural number\n");
		exit(0);
	}
	if(frameArray[fp]->recValues[iden_idx][0] == index){
		printf("Error: Index out of range\n");
		exit(0);
	}
	index++;
	frameArray[fp]->recValues[iden_idx][index]=value;

}

// Read a value from a record variable, from the given index
int recallRec(char* iden, int index) {
	//Search iden idx
		//if iden idx == -1 error non existing var
	//check index 
	//	if index < 0 error index must be Natural number
	//check recValues[iden idx]
		//if recValues[iden idx] == NULL   error uninitialization error
	//check iden size in recValues[iden idx][0]	
		//if recValues[iden idx][0] == index error ouside of array size
	//else
	//index++;
	//return recValuse[iden idx][index]
	int iden_idx = searchRecord(iden);
	if(iden_idx == -1){
		printf("Error: Record variable has not been declared\n");
		exit(0);
	}
	if(index < 0){
		printf("Error: Index must be natural number\n");
		exit(0);
	}
	if(frameArray[fp]->recValues[iden_idx][0] == index){
		printf("Error: Index out of range\n");
		exit(0);
	}
	index++;
	return frameArray[fp]->recValues[iden_idx][index];
}

// Handle "id := record id" type assignment (x)
void record(char* lhs, char* rhs) {
	//search lhs idx
		//if lhs idx == -1 error non existing var
	//search rhs idx
		//if rhs idx == -1 error non existing var
	//check recValues[rhs idx]
		//if recValues[rhs idx] == NULL   error uninitialization error
	//recValues[lhs idx] = recValues[rhs idx]
	int lhs_idx = searchRecord(lhs);
	int rhs_idx = searchRecord(rhs);
	if(lhs_idx == -1){
		printf("Error: Record %s has not been declared\n", lhs);
		exit(0);
	}
	if(rhs_idx == -1){
		printf("Error: Record %s has not been declared\n", rhs);
		exit(0);
	}

	frameArray[fp]->recValues[lhs_idx]=frameArray[fp]->recValues[rhs_idx];
}

// Handle "id := new record[<expr>]" type assignment (x)
void allocateRecord(char* iden, int size) {
	//search iden idx
		//if iden idx == -1 error non existing var
	//recValue[iden idx] = calloc (size+1)
	//recValue[iden idx][0] = size

	int idx = searchRecord(iden);
	if(idx == -1){
		printf("Error: Record variable has not been declared\n");
		exit(0);
	}
	if(size < 1){
		printf("Error: Size of Record must be greater than 0\n");
		exit(0);
	}
	frameArray[fp]->recValues[idx]=(int*) calloc(size+1,sizeof(int));
	frameArray[fp]->recValues[idx][0]=size;
}

//print variables and its values


void printInt(){
	int i;
	printf("Int variables: \n");
	for(i=0; i< frameArray[fp]->intSize;i++){
		printf(" %s\n", frameArray[fp]->intArray[i]);
	}
}

void printRec(){
	int i;
	printf("Rec variables: \n");
	for(i=0; i< frameArray[fp]->recSize;i++){
		printf(" %s\n", frameArray[fp]->recArray[i]);
	}
}

void printIntValues(){
	int i;
	printf("----------Integer Variables-----------------\n");
	for(i=0; i< frameArray[fp]->intSize;i++){
		printf("Int: %s   Value: %d\n", frameArray[fp]->intArray[i], frameArray[fp]->intValues[i]);
	}
}

void printRecValues(){
	int i, j;
	printf("----------Record Variables------------------\n");
	for(i=0; i<frameArray[fp]->recSize;i++){
		printf("Rec: %s\n", frameArray[fp]->recArray[i]);

		if(frameArray[fp]->recValues[i] == NULL){
			continue;
		}

		int arraySize = frameArray[fp]->recValues[i][0];
		printf("Values: ");
		for(j=0; j<=arraySize;j++){
			printf("%d, ", frameArray[fp]->recValues[i][j]);
		}printf("\n");
	}

}

void printIntSize(){
	printf("Number of Integers: %d\n", frameArray[fp]->intSize);
}

void printRecSize(){
	printf("Number of Records: %d\n", frameArray[fp]->recSize);
}