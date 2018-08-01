//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// FindPath.c 
// pa4
// CMPS101
// Spring 2018
// May 20, 2018
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


	int range = 0;
	int source;
	int vectorA;
	int vectorB;
	int destination;
	Graph tempGraph = NULL;

	fscanf(in, "%d", &range);
	tempGraph = newGraph(range);

	while(fgetc(in) != EOF){			//continues to loop until file is read in completely
		fscanf(in, "%d", &vectorA);		//reads in first vector
		fscanf(in, "%d", &vectorB);		//reads in second vector
		if(vectorA == 0 && vectorB == 0){
			break;						//if 0,0 means input is over
		}

		addEdge(tempGraph, vectorA, vectorB);		//adds the new edge to the graph 
	}


	printGraph(out, tempGraph);
	fprintf(out, "\n");



	while(fgetc(in) != EOF){
		fscanf(in, "%d", &source);		//reads in source
		fscanf(in, "%d", &destination);		//reads in destination
		if(source == 0 && destination == 0){
			break;						//if 0,0 means input is over
		}

		List output = newList();
		BFS(tempGraph, source);
		getPath(output, tempGraph, destination);

		if(getDist(tempGraph, destination) != INF){			//gets distance
			fprintf(out, "The distance from ");
			fprintf(out, "%d ", source);
			fprintf(out, "to ");
			fprintf(out, "%d ", destination);
			fprintf(out, "is ");
			fprintf(out, "%d\n", length(output) - 1);


			fprintf(out, "A shortest ");
			fprintf(out, "%d", source);
			fprintf(out, "-");
			fprintf(out, "%d ", destination);
			fprintf(out, "path is: ");
			printList(out, output);
			fprintf(out, "\n");
			fprintf(out, "\n");
		}
		if(getDist(tempGraph, destination) == INF){
			fprintf(out, "The distance from ");
			fprintf(out, "%d ", source);
			fprintf(out, "to ");
			fprintf(out, "%d ", destination);
			fprintf(out, "is infinity\n");



			fprintf(out, "No ");
			fprintf(out, "%d", source);
			fprintf(out, "-");
			fprintf(out, "%d ", destination);
			fprintf(out, "path exists");
			fprintf(out, "\n");
			fprintf(out, "\n");	
		}

		freeList(&output);
	}
	freeGraph(&tempGraph);			//attempts to free mem

	fclose(in);
	fclose(out);
	return(0);
}
