//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Graph.c 
// pa4
// CMPS101
// Spring 2018
// May 20, 2018
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	//printf("sams\n");
	Graph A = newGraph(4);
	addEdge(A, 1, 1);
	addEdge(A, 1, 2);
	addEdge(A, 2, 3);
	addEdge(A, 3, 4);

	printGraph(stdout, A);

	BFS(A, 3);
	List temp = newList();
	getPath(temp, A, 2);


	printf("Graph G has source ")
	printf("%d\n", getSource(G));

	printf("Graph G from 2 has parent ");
	printf("%d, ", getParent(A, 2));
	printf("at a distance of ");
	printf("%d\n", getDis(G, 2));

	return(0);
}
