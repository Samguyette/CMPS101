//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// queueClient.c 
// Takes input of a file of words and sorts their indicies and places them in
// a List lexicographicly
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include"List.h"

int main(int argc, char* argv[]){

	FILE* in;		//in file
	FILE* out;		//out file

	//makes sure command line unput is correct if not error
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//opens reading file
	in = fopen(argv[1], "r"); // "r" for read input file
	if(in == NULL){															//taken code from 12B (SESH)
		printf("Unable to read file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	//opens writing file
	out = fopen(argv[2], "w"); // "w" for writing output file
	if(out == NULL){
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	int topL = 200;
	char data[topL];
	char* dataArray[topL];
	int counter = 0;

	while(fgets(data,topL,in) != NULL){
		counter++;							//counts number of elements in input
	}
	rewind(in);
	
	for(int j = 0; j <= counter; j++){
		dataArray[j] = calloc(1, sizeof(char*[topL]));	//allocates space for array of data
	}
	
	int length = 0;
	int lengthTwo = 0;
	while(fgets(data,topL,in) != NULL){
		strcpy(dataArray[length], data);
		length++;
		lengthTwo++;
	}
	//has array of strings
	// for(int i = 0; i < 5; i++){
	// 	printf("%s\n", dataArray[i]);		//PRINTING TEST
	// }
 
	List inputList = newList();	//creates new list called inputList

	append(inputList, 0);			//places first element in list, no need to sort
	for(int arrayCounter = 1; arrayCounter < length; arrayCounter++){		//loops through every element in the array
		moveBack(inputList);								//moves curser to the back
		char *tempOne = dataArray[arrayCounter];
		int listCounter = arrayCounter - 1;
		bool x = true;

		while(x == true && strcmp(tempOne, dataArray[get(inputList)]) <= 0 && listCounter >= 0){			//holds data from array and finds proper place in list				
			movePrev(inputList);											//by movingPrev down thorugh the list until it is alphabetically
			listCounter--;												//found the right place
			if(listCounter < 0){
				x = false;						//boolean trigger to not run compareTo if list counter is negative
			}									//in place
		}
		if(index(inputList) >= 0){
			insertAfter(inputList, arrayCounter);							//if not last it insterts the indecie between the two proper indecies
		}
		if(index(inputList) < 0){
			prepend(inputList, arrayCounter);								//if at the front this indecie is placed at the start of the list
		}
	}
	//printf("%d\n", length(inputList));
	moveFront(inputList);					//moves cursor to the front for printing
	while(lengthTwo > 0){
		fprintf(out, "%s", dataArray[get(inputList)]);				//loops through list and prints part of array with correct indecie
		moveNext(inputList);
		
		lengthTwo--;
	}

	freeList(&inputList);
	fclose(in);									//closes Writers and Readers
	fclose(out);

	return(0);
}
