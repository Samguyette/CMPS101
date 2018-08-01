//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// FindComponents.c
// pa5
// CMPS101
// Spring 2018
// June 6, 2018
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"


int main(int argc, char* argv[]){
	//printf("sams\n");

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


	int range = 0;                     //initializes range variable
	int vectorA;                       //temp vectors
	int vectorB;
	Graph tempGraph = NULL;            //constructs Graph
    int numSCComp = 0;

	fscanf(in, "%d", &range);          //finds range of in file
	tempGraph = newGraph(range);       //sets temp graph to the proper range

	while(fgetc(in) != EOF){			//continues to loop until file is read in completely
		fscanf(in, "%d", &vectorA);		//reads in first vector
		fscanf(in, "%d", &vectorB);		//reads in second vector
		if(vectorA == 0 && vectorB == 0){
			break;						//if 0,0 means input is over
		}

		addArc(tempGraph, vectorA, vectorB);		//adds the new edge to the graph
	}

    fprintf(out, "Adjacency list representation of G:\n");      //text
    printGraph(out, tempGraph);                                //prints out adjacency list
    fprintf(out, "\n");

    List stack = newList();
    for(int j = 1; j <= range; j++){
        append(stack, j);
    }

    DFS(tempGraph, stack);

    Graph transposedGraph = newGraph(range);
    transposedGraph = transpose(tempGraph);
    DFS(transposedGraph, stack);

    int size = getOrder(transposedGraph);         //num of verticies

    moveFront(stack);
    while(size > 0){                     //if parent is NIL it means that is the end of the scc
        int temp = get(stack);
        if(getParent(transposedGraph, temp) == NIL){       //and count is added by 1
            numSCComp = numSCComp + 1;
            insertBefore(stack, -2);
        }
        moveNext(stack);
        size--;
    }
    //printList(stderr, stack);
    fprintf(out, "G contains ");
    fprintf(out, "%d", numSCComp);
    fprintf(out, " strongly connected components:\n");

    size = getOrder(transposedGraph) + numSCComp;         //num of verticies

    int stackArray[size];

    moveFront(stack);
    for(int i = 0; i < size; i++){
        stackArray[i] = get(stack);                       //stores the stack into an array because it is easier to manipulate by indicies
        moveNext(stack);
    }

    for(int i = 1; i < numSCComp + 1; i++){
        fprintf(out, "Component ");                     //prints out what component it is on
        fprintf(out, "%d", i);
        fprintf(out, ": ");

        int index = size;
        while(stackArray[index] != -2){                 //finds where the break is
            index--;
        }
        while(index < size){
            if(stackArray[index] != -1 && stackArray[index] != -2){
                fprintf(out, "%d ", stackArray[index]);         //prints all of the ints after the break
            }
            stackArray[index] = -1;                             //changes all printed nums to -1
            index++;
        }
        fprintf(out, "\n");
    }

    freeList(&stack);
    freeGraph(&tempGraph);			//attempts to free mem
	fclose(in);
	fclose(out);
	return(0);
}
