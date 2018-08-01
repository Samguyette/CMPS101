//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// List.h 
// List functions for List ADT
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;



//frees memory from a deleted node

List newList(void);

void freeList(List* pL);

//Access functions ------------------------------------------------------------
int length(List L);	//Returns the number of elements in this list

int index(List L);	//If cursor is defined, retuns the index of the cursor element, otherwise returns -1

int front(List L);	//Returns front element. Pre: length() > 0

int back(List L);	//Returns back element. Pre length() > 0

int get(List L);	//Returns cursor element. Pre: length() > 0, index() >= 0

int equals(List A, List B);	  // Returns 1 if and only if this List and L are the same
	// integer sequence and 0 if they are not equal The states of the cursors in the two Lists are not used.

//Manipulation procedures -----------------------------------------------------
void clear(List L);	// Resets this List to its original empty state.

void moveFront(List L);	// If List is non-empty, places the cursor under the front element, otherwise does nothing.

void moveBack(List L);	// If List is non-empty, places the cursor under the back element, otherwise does nothing.

void movePrev(List L);	// If cursor is defined and not at front, moves cursor one step toward front of this List, 
	//if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
void moveNext(List L);	// If cursor is defined and not at back, moves cursor one step toward back of this List, 
	// if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
void prepend(List L, int data);	// Insert new element into this List. If List is non-empty, insertion takes place before front element.

void append(List L, int data);	// Insert new element into this List. If List is non-empty, insertion takes place before front element.

void insertBefore(List L, int data);	// Insert new element before cursor. Pre: length()>0, index()>=0

void insertAfter(List L, int data);	// Inserts new element after cursor. Pre: length()>0, index()>=0

void deleteFront(List L);	// Deletes the front element. Pre: length()>0

void deleteBack(List L);	// Deletes the back element. Pre: length()>0

void delete(List L);	// Deletes cursor element, making cursor undefined. // Pre: length()>0, index()>=0 

//Other operations ------------------------------------------------------------ 
void printList(FILE* out, List L);

List copyList(List L);

#endif
