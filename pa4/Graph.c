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
#include"List.h"
#include"Graph.h"

#define white 0
#define gray 1					//defines colors
#define black 2

typedef struct GraphObj{
	List *adjacentN;		
	int *parent;			//members to struct
	int *distance;			//Graph Obj
	int *color;
	int verticesCount;	
	int edgesCount;		
	int source;

}GraphObj;


/*** Constructors-Destructors ***/
Graph newGraph(int n){

//Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
	Graph newGraph = malloc(sizeof(struct GraphObj));		//allocates memory for the new Graph
	newGraph -> adjacentN = calloc(n+1, sizeof(List));		//allocates memory for the neighboring verts
	newGraph -> parent = calloc(n+1, sizeof(int));			//allocates memory for the parent 
	newGraph -> distance = calloc(n+1, sizeof(int));		//allocates memory for the distance int
	newGraph -> color = calloc(n+1, sizeof(int));			//allocates memory for the color 
	newGraph -> source = NIL;
	newGraph -> verticesCount = n;
	newGraph -> edgesCount = 0;
	
	for(int i = 1; i < n+1; i++){
		newGraph -> adjacentN[i] = newList();	//creates a new list that will be placed in the array of lists
		newGraph -> parent[i] = NIL;				//sets all first to NULL
		newGraph -> distance[i] = INF; 			//sets all first to infinite
		newGraph -> color[i] = white;				//sets all colors to start as white
	}
	return newGraph;
}


void freeGraph(Graph* pG){
//Frees all dynamic memory associated with the Graph *pG,then sets the handle *pG to NULL.
	Graph delete = *pG;
	int temp = getOrder(delete);
	for(int i = 1; i <= temp; i++){				//goes though entire Graph to free each list
		freeList(&(delete -> adjacentN[i]));
		temp--;
	}

	free(delete -> adjacentN);					//frees neighbors
	free(delete -> parent);						//frees parent
	free(delete -> distance);					//frees distance int
	free(delete -> color);						//frees color
	free(*pG);	

	*pG = NULL;
}

/*** Access functions ***/
int getOrder(Graph G){
//Returns the corresponding field values.
	if(G == NULL){		//checks if G is NULL
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	return G -> verticesCount;			//returns count
}

int getSize(Graph G){
//Returns the corresponding field values.
	if(G == NULL){		//checks if G is NULL
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	return G -> edgesCount;				//returns count
}

int getSource(Graph G){
//Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
	return G -> source;				//returns source
}

int getParent(Graph G, int u){
//Returns the parent of vertex u in the Breadth First tree created by BFS(), or NIL if BFS() has not yet been called.
//precondition 1 <= u <= getOrder(G)
	if(G == NULL){		//checks if G is NULL
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	return G -> parent[u]; 		//returns parent
}

int getDist(Graph G, int u){
//Returns the distance from the most recent BFS source to vertex u,or INF if BFS()hasnotyetbeencalled.
//precondition 1 <= u <= getOrder(G)
	if(G == NULL){		//checks if G is NULL
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	if(getSource(G) == NIL){		//Checks if source is NIL
		return INF;
	}
	return G -> distance[u];		//returns distance
}

void getPath(List L, Graph G, int u){
//Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
//Has the precondition getSource(G)!= NIL, so BFS() must be called before getPath()
//precondition 1 <= u <= getOrder(G)
	if(u == getSource(G)){
		append(L, getSource(G));				//appends source
	}
	else if(G -> parent[u] == NIL){
		append(L, NIL);							//if nil appends source and exits
	}											//no path exists
	
	if(u != getSource(G) && G -> parent[u] != NIL){
		getPath(L, G, G -> parent[u]);			//if not nil calls getPath and keeps exicuting
		append(L, u);							//apends new path
	}

}

/*** Manipulation procedures ***/
void makeNull(Graph G){
//Deletes all edges of G, restoring it to its original (no edge) state.
	if(G == NULL){		//checks if G is NULL
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	int temp = getOrder(G) + 1;
	for(int i = 0; i < temp; i++){	//makes every element NULL
		clear(G -> adjacentN[i]);
	}
	G -> edgesCount = 0;		//reset edge count
}

void addEdge(Graph G, int u, int v){
//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
//Precondition that their two int arguments must lie in the range 1 to getOrder(G)
	if(G == NULL){
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	List A = newList();			//creates new list
	A = G -> adjacentN[u];		//assigns to proper list
	if(length(A) == 0){
		append(A, v);			//if list is empty appends
	}

	for(moveFront(A); index(A) != -1; moveNext(A)){
		if(v == get(A)){
			//insertBefore(A, v);		//insures not printed twice
			break;
		}
		if(v < get(A)){					//finds proper place numarically to insert new edge
			insertBefore(A, v);
			break;
		}
	}
	if(index(A) == -1){
		append(A, v);					//if cursor made it to the end appends at the back
	}

	List B = newList();			//creates new list
	B = G -> adjacentN[v];		//assigns to proper list
	if(length(B) == 0){
		append(B, u);			//if list is empty appends
	}

	for(moveFront(B); index(B) != -1; moveNext(B)){
		if(u == get(B)){
			//insertBefore(A, v);		//insures not printed twice
			break;
		}
		if(u < get(B)){					//finds proper place numarically to insert new edge
			insertBefore(B, u);
			break;
		}
	}
	if(index(B) == -1){
		append(B, u);					//if cursor made it to the end appends at the back
	}
	G -> edgesCount++;
}

void addArc(Graph G, int u, int v){
//Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
//Precondition that their two int arguments must lie in the range 1 to getOrder(G)
	if(G == NULL){
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	List A = newList();			//creates new list
	A = G -> adjacentN[u];		//assigns to proper list
	if(length(A) == 0){
		append(A, v);			//if list is empty appends
	}

	for(moveFront(A); index(A) != -1; moveNext(A)){
		if(v == get(A)){
			//insertBefore(A, v);		//insures not printed twice
			break;
		}
		if(v < get(A)){					//finds proper place numarically to insert new edge
			insertBefore(A, v);
			break;
		}
	}
	if(index(A) == -1){
		append(A, v);					//if cursor made it to the end appends at the back
	}
}

void BFS(Graph G, int s){
//Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
//Algarithm given in class Lecture 13
	if(G == NULL){
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
	if(s > getOrder(G) || s < 1){
		fprintf(stderr, "Error: Out of bounds.\n");
	}


	for(int i = 1; i <= getOrder(G); i++){
		G -> parent[i] = NIL;
		G -> distance[i] = INF;			//initializes verticess
		G -> color[i] = white;
	}

	G -> parent[s] = NIL;
	G -> distance[s] = 0;				//initializes vertices
	G -> color[s] = gray;
	G -> source = s;					
	
	List tempList = newList();			//creates a temporary list
	append(tempList, s);					

	//int tempLength = length(tempList);
	while(length(tempList) > 0){					//cycles though as many objects are in list
		int frontData = front(tempList);
		deleteFront(tempList);						//version of enqeue and dequeue (tempList)
		
		List neighbors = G -> adjacentN[frontData];
		for(moveFront(neighbors); index(neighbors) != -1; moveNext(neighbors)){
			int data = get(neighbors);

			if(G -> color[data] == white){
				G -> parent[data] = frontData;
				G -> distance[data] = G -> distance[frontData] + 1;
				G -> color[data] = gray;

				append(tempList, data);
			}
		}
		G -> color[frontData] = black;			//once finished with vert changes color to black
		//tempLength--;
	}
	freeList(&tempList);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
//Prints the adjacency list representation of G to the file pointed to by out.
	int counter = getOrder(G);

	for(int i = 1; i <= counter; i++){			//cycles though entire array
		List temp = newList();
		temp = G -> adjacentN[i];
		fprintf(out, "%d:", i);

		moveFront(temp);
		while(index(temp) != -1){				//cycles though entire list
			int tempData = get(temp);
			fprintf(out, " %d", tempData);
			moveNext(temp);
		}
		fprintf(out, "\n");
	}
}



