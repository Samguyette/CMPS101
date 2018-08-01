//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Graph.c
// pa5
// CMPS101
// Spring 2018
// June 6, 2018
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

#define black 2
#define gray 1					//defines colors
#define white 0
#define NIL 0
#define UNDEF -1

typedef struct GraphObj{
	List *adjacentN;
	int *parent;			//members to struct
	int *distance;			//discover
	int *color;
    int *finish;
    int edgesCount;        //edge count
	int verticesCount;     //vert count
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
	newGraph -> finish = calloc(n+1, sizeof(int));          //allocates memory for finish
	newGraph -> edgesCount = 0;
    newGraph -> verticesCount = n;
    newGraph -> source = NIL;

	for(int i = 1; i < n+1; i++){
		newGraph -> adjacentN[i] = newList();	//creates a new list that will be placed in the array of lists
		newGraph -> parent[i] = NIL;				//sets all first to NULL
        newGraph -> finish[i] = UNDEF;              //sets all finish to undef
        newGraph -> distance[i] = UNDEF; 			//sets all first to undef
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

    free(delete -> finish);                     //frees finish
	free(delete -> adjacentN);					//frees neighbors
    free(delete -> distance);					//frees distance int
	free(delete -> color);						//frees color
    free(delete -> parent);						//frees parent

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

int getDiscover(Graph G, int u){
//Returns the distance from the most recent BFS source to vertex u,or INF if BFS()hasnotyetbeencalled.
//precondition 1 <= u <= getOrder(G)
	if(G == NULL){		//checks if G is NULL
		fprintf(stderr, "Error: The graph is NULL.\n");
		exit(1);
	}
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Error: Wrong specs.\n");
		exit(1);
    }
	return G -> distance[u];		//returns distance
}

int getFinish(Graph G, int u){
//return the appropriate field values for the given vertex.
    if(G == NULL){		//checks if G is NULL
        fprintf(stderr, "Error: The graph is NULL.\n");
        exit(1);
    }
    return G -> finish[u];      //returns finish
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
    else{
        for(moveFront(A); index(A) != -1; moveNext(A)){
            // if(v == get(A)){
            //     //insertBefore(A, v);		//insures not printed twice
            //     break;
            // }
            if(v < get(A)){					//finds proper place numarically to insert new edge
                insertBefore(A, v);
                break;
            }
        }
        if(index(A) == -1){
            append(A, v);					//if cursor made it to the end appends at the back
        }
    }
    G -> edgesCount++;
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

void visit(Graph G, List L, int x, int *t){
// helper function for DFS
    G -> color[x] = gray;                       //changes color to gray for first iteration
    G -> distance[x] = (++*t);                 //time is corilated to depth of visit

    moveFront(G -> adjacentN[x]);
    while(index(G -> adjacentN[x]) != -1){
        int temp = get(G -> adjacentN[x]);      //gets data

        //printf("sam\n");
        if(G -> color[temp] == white){          //if color is white
                G -> parent[temp] = x;          //means it has not been visited
                visit(G, L, temp, t);        //and calls visit func
        }
        moveNext(G -> adjacentN[x]);
        //moves to next
    }
    G -> finish[x] = (++*t);                   //time is increased
    G -> color[x] = black;                      //vert is changed to black and is concidered finished

    prepend(L, x);                              //prepend to the stack
}

void DFS(Graph G, List S){
//Perform the depth first search algorithm on G
//Second, when DFS is complete, it will store the vertices in order of decreasing finish times (hence S can be considered to be a stack).
//Algarithm given in class Lecture
//Precondition OrderSize has to be equal to stack size
    int orderSize = getOrder(G);
    for(int j = 1; j <= orderSize; j++){        //firstly
        G -> parent[j] = NIL;               //changes parent to NIL and color to whiite
        G -> color[j] = white;
        //G -> distance[j] = UNDEF;
        //G -> finish[j] = UNDEF;
    }
    moveFront(S);                           //moves to front of the stack
    int time = 0;

    //printf("sam\n");
    while(index(S) >= 0){
        //check indicies
        int temp = get(S);
        if(G -> color[temp] == white){
            visit(G, S, temp, &time);       //if color is white it will move to visit function
        }                                   //for first visit

        moveNext(S);                        //iterates
    }
    int newOrderSize = getOrder(G);
    for(int j = 0; j < newOrderSize; j++){
        //check indicies
        deleteBack(S);                     //deletes back once it has been visited
    }
}

/*** Other Functions ***/
Graph copyGraph(Graph G){ //Constructor
//Returns a reference to a new graph which is a copy of G.
    int size = getOrder(G);
    Graph graphCopy = newGraph(size);     //creates new graph
    for(int j = 1; j <= size; j++){
        moveFront(G -> adjacentN[j]);       //moves to front

        while(index(G -> adjacentN[j]) >= 0){
            addArc(graphCopy, j, get(G -> adjacentN[j]));     //adds copied arc
            moveNext(G -> adjacentN[j]);        //iterates
        }
    }
    return graphCopy;         //returns new graph
}

Graph transpose(Graph G){ //Constructor
//Returns a reference to a new graph object representing the transpose of G.
    int size = getOrder(G);
    Graph newTranspose = newGraph(size);        //creates new graph

    for(int j = 1; j <= size; j++){
        moveFront(G -> adjacentN[j]);           //moves cursor to the front

        if(length(G -> adjacentN[j]) != 0){     //checks that list is not empty
            while(index(G -> adjacentN[j]) != -1){
                addArc(newTranspose, get(G -> adjacentN[j]), j);    //adds new Arc in reversed
                moveNext(G -> adjacentN[j]);                        //iterates
            }
        }
    }
    return newTranspose;            //returns new graph
}

void printGraph(FILE* out, Graph G){
//Prints the adjacency list representation of G to the file pointed to by out.
	int counter = getOrder(G);

	for(int i = 1; i <= counter; i++){			//cycles though entire array
		List temp = newList();
		temp = G -> adjacentN[i];
		fprintf(out, "%d:", i);

		moveFront(temp);
        if(index(temp) == -1){                  //adds extra space if list is empty
            fprintf(out, " ");
        }
		while(index(temp) != -1){				//cycles though entire list
			int tempData = get(temp);
			fprintf(out, " %d", tempData);
			moveNext(temp);
		}
		fprintf(out, "\n");
	}
}
