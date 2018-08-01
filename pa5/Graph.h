//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Graph.h
// pa5
// CMPS101
// Spring 2018
// June 6, 2018
//-----------------------------------------------------------------------------

//header file for Graph.c
//description of each function can be found in Graph.c

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define NIL 0
#define INF -1
#define black 2
#define gray 1					//defines colors
#define white 0
#define NIL 0
#define UNDEF -1

#include "List.h"

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

//int getSource(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

//void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
//void makeNull(Graph G);
void addArc(Graph G, int u, int v);

void addEdge(Graph G, int u, int v);

void DFS(Graph G, List S);

/*** Other Functions ***/
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);


#endif
