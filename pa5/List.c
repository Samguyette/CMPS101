//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// List.c
// pa5
// CMPS101
// Spring 2018
// June 6, 2018
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

//structs ---------------------------------------------------------------------
//structs basis taken from Tantalo's Queue.c
//private Node type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* previous;
}NodeObj;

//private Node type
typedef NodeObj* Node;

//private List type
typedef struct ListObj{
	Node front;
	Node back;
	Node current;
	int cursor;
	int index;
	int length;
}ListObj;

//Constructors-Destructors ----------------------------------------------------
//Creates and initializes a new node and returns ref
Node newNode(int data){
	Node new = malloc(sizeof(NodeObj));
	new->next = NULL;
	new->previous = NULL;
	new->data = data;
	return new;
}
//frees memory from a deleted node
void freeNode(Node* pN){
	if(pN != NULL){
		if(*pN != NULL){
			free(*pN);
			*pN = NULL;
		}
	}
}

List newList(void){
	List newList;
	newList = malloc(sizeof(ListObj));
	newList->front = NULL;
	newList->back = NULL;
	newList->index = -1;
	newList->length = 0;
	return(newList);
}

void freeList(List* pL){
	if(pL != NULL){
		Node temp = (*pL)->front;
		while(temp!=NULL){
			Node currentTemp = temp;
			temp = temp->next;
			free(currentTemp);
		}
	}
}

// //Access functions ------------------------------------------------------------
int length(List L){	//Returns the number of elements in this list
	if(L == NULL){
		return 0;
	}
	return L->length;
}

int index(List L){	//If cursor is defined, retuns the index of the cursor element, otherwise returns -1
	if(length(L) < 1){
		return -1;
	}
	return(L->cursor);
}

int front(List L){	//Returns front element. Pre: length() > 0
	if(length(L) == 0){
		printf("Does not meet prerequisites. (11)");	//if the Pre: is not meet a run time exception will be thrown
		exit(1);
	}
	else{						//returns front of the list
		return L->front->data;
	}
}

int back(List L){	//Returns back element. Pre length() > 0
	if(length(L) == 0){
		printf("Does not meet prerequisites. (10)");	//if the Pre: is not meet a run time exception will be thrown
		exit(1);
	}
	else{						//returns front of the list
		return L->back->data;
	}
}

int get(List L){	//Returns cursor element. Pre: length() > 0, index() >= 0
	if(L->current == NULL){
		printf("Does not meet prerequisites. (9)");	//if the Pre: is not meet a run time exception will be thrown
		exit(1);
	}
	if(length(L) <= 0){
		printf("Does not meet prerequisites. (8)");	//if the Pre: is not meet a run time exception will be thrown
		exit(1);
	}

	return (L->current->data); 			//returns what element the cursor is on
}

int equals(List A, List B){	  // Returns 1 if and only if this List and L are the same
	//integer sequence and 0 if they are not equal The states of the cursors in the two Lists are not used.
		if(length(A) != length(B)){			//in determining equality.
			return 0;						//if the lists are not of same length inherently not the same
		}
		if(A == NULL){
			printf("Error: The lists are empty\n");
			exit(1);
		}
		Node firstInput = A->front;
		Node secondInput = B->front;
		for(int i = 0; i <= length(A)-1; i++){		//has to subtract so you don't get null
			if(firstInput->data != secondInput->data){		//compares the data of each slot in the proposed equal lists
				return 0;
			}
			else{
				firstInput = firstInput->next;
				secondInput = secondInput->next;				//iterates both lists
			}
		}
		return 1;
	}


// //Manipulation procedures -----------------------------------------------------
void clear(List L){		// Resets this List to its original empty state.
	Node temp = L->front;
	while(temp != NULL){
		Node tempTwo = temp;
		temp = temp->next;
		free(tempTwo);
	}

	L->front = NULL;
	L->back = NULL;
	L->current = NULL;		//clears entire linked list
	L->length = 0;			//removes all data
	L->cursor = -1;
}
void moveFront(List L){	// If List is non-empty, places the cursor under the front element, otherwise does nothing.
	if(length(L) > 0){
	L->cursor = 0;		//cursor equals first element
	L->current = L->front;
	}
}
void moveBack(List L){	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
	if(length(L) > 0){
		L->cursor = length(L) - 1;	//currsor equals last element
		L->current = L->back;
	}
}
void movePrev(List L){	// If cursor is defined and not at front, moves cursor one step toward front of this List,
	//if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
	if(L->current == NULL){
		return;
	}
	if(L->current == L->front){
		L->cursor = -1;
		L->current = NULL;
	}
	else{				//moves cursor to the front of the previous node
		L->current = L->current->previous;
		L->cursor--;
	}
}

void moveNext(List L){	// If cursor is defined and not at back, moves cursor one step toward back of this List,
	// if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
	if(L->current == NULL){
		return;
	}
	if(L->current == L->back){
		L->cursor = -1;
		L->current = NULL;
	}
	else{
		L->current = L->current->next;				//moves cursor to the next node
		L->cursor = L->cursor + 1;
	}
}

void prepend(List L, int data){		// Insert new element into this List. If List is non-empty, insertion takes place before front element.
	Node H = newNode(data);
	if(L->front == NULL){
		L->front = H;
		L->back = H;
		L->current = L->front;		//inserts element at the front of the list
	}
	else{
		//printf("hit\n");
		H->next = L->front;			//squeezes new element in the front of the list
		H->previous = NULL;
		L->front->previous = H;
		L->front = H;
		//L->current = L->current->previous;
	}
	L->length++;
}
void append(List L, int data){		// Insert new element into this List. If List is non-empty, insertion takes place before front element.
	Node H = newNode(data);
	H->previous = L->back;
	H->next = NULL;

	if(L->back == NULL){
		L->front = H;				//squeezes new node in the back of the list
		L->back = H;
		//L->current = L->back;				//inserts element to the back of the list
	}
	else{
		L->back->next = H;
		L->back = H;
		//L->current = L->current->next;
	}
	L->length++;
}
void insertBefore(List L, int data){	// Insert new element before cursor. Pre: length()>0, index()>=0
	if(L->current == NULL){
		printf("Does not meet prerequisites. (7)");	//if the Pre: is not meet a run time exception will be thrown
		exit(1);
	}
	if(length(L) <= 0){
		printf("Does not meet prerequisites. (6)");	//if the Pre: is not meet a run time exception will be thrown
		exit(1);
	}
	Node H = newNode(data);
	if(L->current == L->front){
		prepend(L, data);					//if cursor is at the front adds data to the front
	}
	else{
		H->previous = L->current->previous;
		H->next = L->current;
		L->current->previous->next = H;		//inserts new node before cursor
		L->current->previous = H;
		L->length++;
	}
}

void insertAfter(List L, int data){	// Inserts new element after cursor. Pre: length()>0, index()>=0
	if(length(L) <= 0){
		if(index(L) < 0){
			printf("Does not meet prerequisites. (5)");	//if the Pre: is not meet a run time exception will be thrown
			exit(1);
		}
	}
	if(index(L) < 0){
		if(index(L) < 0){
			printf("Does not meet prerequisites. (5.5)");	//if the Pre: is not meet a run time exception will be thrown
			exit(1);
		}
	}
	Node H = newNode(data);
	if(L->current == L->back){
		append(L, data);
		return;
	}

	H->previous = L->current;				//inserts new node after cursor
	H->next = L->current->next;
	if(L -> current -> next != NULL){
		L->current->next->previous = H;
	}
	L->current->next = H;
	L->length++;
}

void deleteFront(List L){	// Deletes the front element. Pre: length()>0
	int tempLength = length(L);
	if(tempLength <= 0){
		printf("Does not meet prerequisites. (4)");
		exit(1);
	}
	Node temp = L->front;
	if(length(L) > 1){
		L -> front = L -> front -> next;
	}
	else{
		L -> front = NULL;
		L -> back = NULL;	//removes front node
	}
	L->length--;

	freeNode(&temp);
	//*temp = NULL;
}

void deleteBack(List L){	// Deletes the back element. Pre: length()>0
	Node temp = NULL;
	if(length(L) <= 0){
		printf("Does not meet prerequisites. (3)");
		exit(1);
	}

	if(L -> current == L -> back){
		L -> current = NULL;
		L -> back -> previous = L -> back;
		L -> back -> next = NULL;
		L -> index = -1;
	}
	else{
		L -> back -> previous = L -> back;
		L -> back -> next = NULL;
	}
	L->length--;

	freeNode(&temp);
	//*temp = NULL;
}

void delete(List L){	// Deletes cursor element, making cursor undefined. // Pre: length()>0, index()>=0
	if(length(L) < 0){
		printf("Does not meet prerequisites. (1)");
		exit(1);
	}
	if(index(L) < 0){
		printf("Does not meet prerequisites. (2)");
		exit(1);
	}
	if(L->current == L->front){
		deleteFront(L);				//deletes the node that the cursor is currently on
		return;
	}
	if(L->current == L->back){
		deleteBack(L);
		return;
	}
	Node temp = L->current;
	L->current->previous->next = L->current->next;		//deletes the node that the cursor is on
	L->current->next->previous = L->current->previous;	//bringing both side pointers together
	L->current = NULL;
	L->cursor = -1;
	L->length--;

	freeNode(&temp);
}

// //Other operations ------------------------------------------------------------
void printList(FILE* out, List L){
	int size = length(L);
	if(size == 0){
		printf("Error: Can not print becasue list is empty");
		exit(1);
	}
	// int front = L->front->data;
	// int back = L->back->data;
	// printf("%d", front);
	// printf("%d", back);
	// printf("%d\n", size);
	Node temp = L->front;
	while(size > 0){
		fprintf(out, "%d ", temp->data);
		temp = temp->next;
		size--;
	}
}
List copyList(List L){	// Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined,
	// regardless of the state of the cursor in this List. This List is unchanged.
	List copy = newList();		//doesn't work come back
	if(length(L) > 0){
		Node iterator;
		iterator = L->front;
		while(iterator > 0){							//copys the original list to another list
			append(copy, iterator->data);
			iterator = iterator->next;				//iterates thorugh entire list copying
		}
	}
	copy->current = NULL;
	copy->cursor = -1;

	return copy; 		//returns copy
}
