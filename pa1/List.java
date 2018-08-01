//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Lex.java  
// List functions for List ADT
// (Used https://www.randomlists.com/random-words for testing purposes.)
//-----------------------------------------------------------------------------
class List{	
	private class Node{		//creats private Node class
		Node next;
		Node previous;
		int data;
		
		Node(int data){
			next = null;		//doubly LL node
			previous = null;
			this.data = data;
		}

	}

	int currentLength;
	Node front;
	Node Current;
	Node back;
	int cursor = -1;

	// Creates a new empty list.
	List(){
		cursor = -1;
		front = null;
		back = null;
		Current = null;
		currentLength = 0; 
	}

	//* Access functions *//
	int length(){	//Returns the number of elements in this list
		return currentLength;
	}
	
	int index(){	//If cursor is defined, retuns the index of the cursor element, otherwise returns -1
		if(length() <= 0){
			return -1;
		}
		else{
			return cursor;	//returns number of index the cursor is currently on
		}		
	}
	int front(){	//Returns front element. Pre: length() > 0
		if(length() == 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		else{						//returns front of the list
			return front.data;
		}
	}
	int back(){		//Returns back element. Pre length() > 0
		if(length() == 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		else{						//returns element in the back of the list
			return back.data;
		}
	}
	int get(){		//Returns cursor element. Pre: length() > 0, index() >= 0
		if(Current == null){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}

		return Current.data;			//returns what element the cursor is on
	}
	boolean isNull(){
		if(Current == null){		//if current is empty returns true
			return true;
		}
		else{
			return false;
		}
	}
	
	boolean equals(List L){		 // Returns true if and only if this List and L are the same
	// integer sequence. The states of the cursors in the two Lists // are not used in determining equality.
		if(L.length() != length()){			//if the lists are not of same length inherently not the same
			return false;
		}
		Node Input = L.front;
		Node CurrentTemp = front;
		for(int i = 0; i <= L.length()-1; i++){		//has to subtract so you don't get null
			if(CurrentTemp.data != Input.data){		//compares the data of each slot in the proposed equal lists	
				return false;
			}
			else{
				CurrentTemp = CurrentTemp.next;
				Input = Input.next;				//iterates both lists
			}
		}
		return true;
	}

	// Manipulation procedures
	void clear(){		// Resets this List to its original empty state.
		front = null;
		back = null;
		Current = null;		//clears entire linked list 
		currentLength = 0;	//removes all data
		cursor = -1;
	}

	void moveBack(){	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
		if(length() > 0){
			cursor = length() - 1;	//currsor equals last element 
			Current = back;
		}
	}

	void moveFront(){	// If List is non-empty, places the cursor under the front element, otherwise does nothing.
		if(length() > 0){
			cursor = 0;		//cursor equals first element
			Current = front;
		}
	}

	void moveNext(){	// If cursor is defined and not at back, moves cursor one step toward back of this List, 
	// if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
		if(Current == back){
			cursor = -1;
			Current = null;
		}
		else{
			Current = Current.next;				//moves cursor to the next node
			cursor = cursor + 1;
		}
	}

	void movePrev(){	// If cursor is defined and not at front, moves cursor one step toward front of this List, 
	//if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
		if(Current == front){
			cursor = -1;
			Current = null;
		}
		else{				//moves cursor to the front of the previous node
			Current = Current.previous;
			cursor--;
		}
	}

	int returnCursor(){
		return cursor;				//returns cursor for testing purposes
	}

	void append(int data){	// Insert new element into this List. If List insertion takes place after back element. void insertBefore(int data) 
	// Insert new element before cursor. Pre: length()>0, index()>=0
		Node newNode = new Node(data);
		if(back != null){
			back.next = newNode;
			newNode.previous = back;
			back = newNode;						//inserts element to the back of the list
			newNode.next = null;
		}
		if(back == null){
			front = newNode;			//squeezes new node in the back of the list
			back = newNode;
			Current = back;
		}
		currentLength++;
	}

	void prepend(int data){	// Insert new element into this List. If List is non-empty, insertion takes place before front element.
		Node newNode = new Node(data);
		
		if(front == null){
			front = newNode;
			back = newNode;
			Current = front;
								//inserts element at the front of the list
		}
		else{
			front.previous = newNode;
			newNode.next = front;			//squeezes new element in the front of the list
			newNode.previous = null;
			front = newNode;
		}
		currentLength++;
	}

	
	void insertAfter(int data){	// Inserts new element after cursor. Pre: length()>0, index()>=0
		if(length() <= 0){
			if(index() < 0){
				throw new 
				RuntimeException
				("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
			}
		}
		Node newNode = new Node(data);

		if(Current == back){
			append(data);
		}
		else{
			Current.next.previous = newNode;
			newNode.next = Current.next;
			newNode.previous = Current;				//inserts new node after cursor
			Current.next = newNode;
		}
		currentLength++;

	}
	void insertBefore(int data){	// Insert new element before cursor. Pre: length()>0, index()>=0
		if(Current == null){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		if(Current == front){
			prepend(data);					//if cursor is at the front adds data to the front
		}
		else{
			Node newNode = new Node(data);
			newNode.previous = Current.previous;
			newNode.next = Current;
			Current.previous.next = newNode;		//inserts new node before cursor
			Current.previous = newNode;
		}
		currentLength++;
	}
	

	void deleteBack(){	// Deletes the back element. Pre: length()>0
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
	
		back = back.previous;	//removes back node
		back.next = null;
		currentLength--;
	} 


	void deleteFront(){	// Deletes the front element. Pre: length()>0
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}

		front = front.next;		//removes front node
		front.previous = null;
		currentLength--;
	}

	void delete(){	// Deletes cursor element, making cursor undefined. // Pre: length()>0, index()>=0 
		if(length() < 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
		if(index() < 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
		if(Current == front){
			deleteFront();				//deletes the node that the cursor is currently on 
			return;
		}
		if(Current == back){
			deleteBack();
			return;
		}
		Current.previous.next = Current.next;		//deletes the node that the cursor is on
		Current.next.previous = Current.previous;	//bringing both side pointers together
		Current = null;
		cursor = -1;
		currentLength--;
	}


	//* Other Methods *//
	public String toString(){ // Overrides Object's toString method. Returns a String representation of this List consisting of a space
	// separated sequence of integers, with front on left. List copy() Returns a new List representing the same integer sequence as 
	// this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
		String input = "";
		if(length() < 1){
			return input;			//converts the list to a string which makes it able to be printed out
		}
		Node iterator = front;
		while(iterator != null){
			input += iterator.data + " ";
			iterator = iterator.next;
		}
		return input;
	}

	List copy(){ // Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined, 
	// regardless of the state of the cursor in this List. This List is unchanged.
		List copy = new List();
		if(length() > 0){
			Node iterator;
			iterator = front;
			while(iterator != null){				//copys the original list to another list
				copy.append(iterator.data);
				iterator = iterator.next;			//iterates thorugh entire list copying
			}
		}
		copy.Current = null;
		copy.cursor = -1;

		return copy; 		//returns copy
	}
}












