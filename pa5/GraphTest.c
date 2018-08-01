//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// GraphTest.c
// pa5
// CMPS101
// Spring 2018
// June 6, 2018
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i;
   int n = 8;
   List S = newList();
   Graph G = newGraph(n);
   Graph Transpose = NULL;
   Graph Copy = NULL;


   append(S, 1);
   append(S, 2);
   append(S, 3);
   append(S, 4);
   append(S, 5);
   append(S, 6);
   append(S, 7);
   append(S, 8);

   addArc(G, 1,2);
   addArc(G, 3,2);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   Transpose = transpose(G);
   Copy = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, Copy);
   fprintf(stdout, "\n");
   printGraph(stdout, Transpose);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&Transpose);
   freeGraph(&Copy);
   return(0);
}
