//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// List.java  
// pa3
// CMPS101
// Spring 2018
// May 9, 2018
//-----------------------------------------------------------------------------
public class List{	
	private class Node{		//creats private Node class
		Node next;
		Node previous;
		Object dataObj;
		
		Node(Object dataObj){
			next = null;		//doubly LL node for an Object
			previous = null;
			this.dataObj = dataObj;
		}
		public boolean equals(Object newObj){		 // Returns true if and only if this List and L are the same
		// integer sequence. The states of the cursors in the two Lists // are not used in determining equality.
			boolean equals = true;
			Node temp;		

			if(newObj instanceof Node){		//checks if the two dataObj are the same
				temp = (Node)newObj;
				if(this.dataObj.equals(temp) == false){
					equals = false;
				}
			}
			return equals;
		}

		public String toString(){
			return String.valueOf(dataObj);
		}

	}

	int currentLength;
	Node front;
	Node current;
	Node back;
	int cursor = -1;

	// Creates a new empty list.
	List(){
		cursor = -1;
		front = null;
		back = null;
		current = null;
		currentLength = 0; 
	}

	//* Access functions *//
	int length(){	//Returns the number of elements in this list
		int count = 0;
		Node temp = front;
		while(temp != null){
			count++;
			temp = temp.next;
		}

		return count;
	}
	
	int index(){	//If cursor is defined, retuns the index of the cursor element, otherwise returns -1
		if(length() <= 0){
			return -1;
		}
		else{
			return cursor;	//returns number of index the cursor is currently on
		}		
	}
	Object front(){	//Returns front element Object. Pre: length() > 0
		if(length() == 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		else{						//returns front of the list
			return front.dataObj;
		}
	}
	Object back(){		//Returns back element Object. Pre length() > 0
		if(length() == 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		else{						//returns element in the back of the list
			return back.dataObj;
		}
	}
	Object get(){		//Returns cursor element Object. Pre: length() > 0, index() >= 0
		if(current == null){
			throw new 
			RuntimeException
			("Does not meet prerequisites. (1)");	//if the Pre: is not meet a run time exception will be thrown
		}
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites. (2)");	//if the Pre: is not meet a run time exception will be thrown
		}

		return current.dataObj;			//returns what element the cursor is on
	}
	boolean isNull(){
		if(current == null){		//if current is empty returns true
			return true;
		}
		else{
			return false;
		}
	}
	
	// public boolean equals(Object newObj){		 // Returns true if and only if this List and L are the same
	// // integer sequence. The states of the cursors in the two Lists // are not used in determining equality.
	// 	boolean same = true;
	// 	List equals;
	// 	Node a;
	// 	Node b;

	// 	if(newObj instanceof List){
	// 		equals = (List)newObj;
	// 		a = this.front;
	// 		b = equals.front;

	// 		int currentLength = this.length();
	// 		int newLength = equals.length();
	// 		if(currentLength != newLength){
	// 			same = false;
	// 			return same;
	// 		}
	// 		while(a != null){
	// 			if(a.equals(b) == false){
	// 				same = false;
	// 				return same;	
	// 			}
	// 			a = a.next;
	// 			b = b.next;
	// 		}
	// 	}
	// 	return same;
	// }

	// Manipulation procedures
	void clear(){		// Resets this List to its original empty state.
		front = null;
		back = null;
		current = null;		//clears entire linked list 
		currentLength = 0;	//removes all data
		cursor = -1;
	}

	void moveBack(){	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
		if(length() > 0){
			cursor = length() - 1;	//currsor equals last element 
			current = back;
		}
	}

	void moveFront(){	// If List is non-empty, places the cursor under the front element, otherwise does nothing.
		if(length() > 0){
			cursor = 0;		//cursor equals first element
			current = front;
		}
	}

	void moveNext(){	// If cursor is defined and not at back, moves cursor one step toward back of this List, 
	// if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
		if(current == back){
			cursor = -1;
			current = null;
		}
		if(cursor != -1){
			//System.out.println(cursor);
			current = current.next;				//moves cursor to the next node
			cursor++;
		}
	}

	void movePrev(){	// If cursor is defined and not at front, moves cursor one step toward front of this List, 
	//if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
		if(current == front){
			cursor = -1;
			current = null;
		}
		if(cursor != -1){				//moves cursor to the front of the previous node
			current = current.previous;
			cursor--;
		}
	}

	int returnCursor(){
		return cursor;				//returns cursor for testing purposes
	}

	void prepend(Object dataObj){	// Insert new element into this List. If List is non-empty, insertion takes place before front element.
		Node newNode = new Node(dataObj);
		
		if(front == null){
			front = newNode;
			back = newNode;
			current = front;
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

	void append(Object dataObj){	// Insert new element object into this List. If List insertion takes place after back element. void insertBefore(int data) 
	// Insert new element before cursor. Pre: length()>0, index()>=0
		Node newNode = new Node(dataObj);
		if(length() == 0){
			front = newNode;			//squeezes new node in the back of the list
			back = newNode;
			current = back;
			currentLength++;
		}
		else{
			back.next = newNode;
			newNode.previous = back;
			back = newNode;						//inserts element to the back of the list
			newNode.next = null;
			currentLength++;
		}
	}
	
	void insertAfter(Object dataObj){	// Inserts new element after cursor. Pre: length()>0, index()>=0
		if(length() <= 0){
			if(index() < 0){
				throw new 
				RuntimeException
				("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
			}
		}
		Node newNode = new Node(dataObj);

		if(current == back){
			append(dataObj);
		}
		else{
			current.next.previous = newNode;
			newNode.next = current.next;
			newNode.previous = current;				//inserts new node after cursor
			current.next = newNode;
		}
		currentLength++;

	}
	void insertBefore(Object dataObj){	// Insert new element before cursor. Pre: length()>0, index()>=0
		if(current == null){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");	//if the Pre: is not meet a run time exception will be thrown
		}
		if(current == front){
			prepend(dataObj);					//if cursor is at the front adds data to the front
		}
		else{
			Node newNode = new Node(dataObj);
			newNode.previous = current.previous;
			newNode.next = current;
			current.previous.next = newNode;		//inserts new node before cursor
			current.previous = newNode;
		}
		currentLength++;
	}
	

	void deleteBack(){	// Deletes the back element. Pre: length()>0
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
		if(current == front){
			back.previous = back;	//removes back node
			back.next = null;
			currentLength--;
			current = null;
			cursor = -1;
		}
		else{
			back.previous = back;	//removes back node
			back.next = null;
			currentLength--;
		}
	} 


	void deleteFront(){	// Deletes the front element. Pre: length()>0
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
		if(current == front){
			front = front.next;		//removes front node
			currentLength--;
			current = null;
			cursor = -1;
			//front.previous = null;
		}else{
			front = front.next;		//removes front node
			//front.previous = null;
			currentLength--;
		}
	}

	void delete(){	// Deletes cursor element, making cursor undefined. // Pre: length()>0, index()>=0 
		if(length() <= 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
		if(index() < 0){
			throw new 
			RuntimeException
			("Does not meet prerequisites.");
		}
		if(current == front){
			deleteFront();				//deletes the node that the cursor is currently on 
			return;
		}
		if(current == back){
			deleteBack();
			return;
		}
		current.previous.next = current.next;		//deletes the node that the cursor is on
		current.next.previous = current.previous;	//bringing both side pointers together
		cursor = -1;
		currentLength--;
		current = null;
	}


	//* Other Methods *//
	public String toString(){ // Overrides Object's toString method. Returns a String representation of this List consisting of a space
	// separated sequence of integers, with front on left. List copy() Returns a new List representing the same integer sequence as 
	// this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
		String input = "";
		//System.out.println("hit");
		if(length() < 1){
			return input;			//converts the list to a string which makes it able to be printed out
		}
		Node iterator = front;
		while(iterator != null){
			input += iterator.dataObj + " ";
			iterator = iterator.next;
		}
		return input;
	}
}












