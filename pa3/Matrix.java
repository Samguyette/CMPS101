//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Matrix.java  
// pa3
// CMPS101
// Spring 2018
// May 9, 2018
//-----------------------------------------------------------------------------
import java.io.*;

public class Matrix{
	// Constructor
	//creates a data object to go inside of the list
	private class dataObj{
		int place;	//column in matrix
		double value;	//value of data being held

		dataObj(int place, double value){
			this.place = place;
			this. value = value;
		}
		
		public boolean equals(Object x){ // overrides Object's equals() method
			boolean equals = true;
			dataObj temp;

			if(x instanceof dataObj){	//compares the insides of Obj
				temp = (dataObj)x;
				if(temp.place != this.place && temp.value != this.value){
					equals = false;
				}
			}
			return equals;
		}

		//method to overaide toString method
		public String toString(){
			String val = place+" "+value;
			return val;
		}
	}

	List array[];
	int size;
	int NZCount;
	Matrix(int n){ // Makes a new n x n zero Matrix. pre: n>=1
		if(n <= 0){
			throw new
			RuntimeException("Matrix size must be greater than 0.");
		}
		array = new List[n+1];	//declares new list
		size = n;

		for(int i = 1; i < (n+1); i++){
			array[i] = new List();
		}
		this.size = n;
	}
	
	// Access functions
	int getSize(){ // Returns n, the number of rows and columns of this Matrix
		return size;
	}

	int getNNZ(){ // Returns the number of non-zero entries in this Matrix
		NZCount = 0;
		int size  = getSize();
		for(int i = 1; i <= size; i++){
			array[i].moveFront();
			while(array[i].index() >= 0){
				array[i].moveNext();
				NZCount++;
			}
		}
		return NZCount;
	}

	// public boolean equals(Object x){ // overrides Object's equals() method
	// 	boolean same = true;
	// 	Matrix equals;

	// 	if(x instanceof Matrix){		//checks if the object is and instance of Matrix Obj
	// 		equals = (Matrix)x;
	// 		int equalsSize = equals.getSize();
	// 		int currentSize = this.getSize();
	// 		if(equalsSize != currentSize){		//checks if x and the current matrix are the same size
	// 			//System.out.println("hit1");
	// 			same = false;
	// 			return same;
	// 		}

	// 		for(int i = 1; i <= equalsSize; i++){
	// 			if(this.array[i].equals(equals.array[i]) == false){	//compairs each list in the array
	// 				//System.out.println("hit2");
	// 				same = false;
	// 				return same;
	// 			}
	// 		}

	// 	}
	
	// 	return same;
	// }

	// Manipulation procedures
	void makeZero(){ // sets this Matrix to the zero state
		int size = getSize();
		for(int i = 1; i < size; i++){
			array[i].clear();
		}
	}
	
	Matrix copy(){   // returns a new Matrix having the same entries as this Matrix
		int currentSize = getSize();
		Matrix newMatrix = new Matrix(currentSize);		//creates new Matrix

		for(int i = 1; i <= currentSize; i++){			//iterates through every list in the array
			array[i].moveFront();
			int listSize = array[i].length();			
			while(this.array[i].index() >= 0){						//iterates throught every element in the list
				dataObj tempObj = (dataObj)this.array[i].get();
				
				newMatrix.array[i].append(new dataObj(tempObj.place, tempObj.value));		//copies the element
				this.array[i].moveNext();
				//listSize--;
			}
		}
		return newMatrix;
	}
	
	void changeEntry(int i, int j, double x){  // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
		if(i < 1 || j < 1){
			throw new 
			RuntimeException("Row and Column must be greater than 0.");
		}
		if(i > getSize() || j > getSize()){
			throw new 
			RuntimeException("Row and Column must be less than size of Matrix.");
		}
		array[i].moveFront();					//moves cursor to the pront
		int tempSize = array[i].length();
		boolean placed = false;
		
		while(array[i].index() >= 0){
			dataObj tempObj = (dataObj)this.array[i].get();
			if(tempObj.place == j){
				placed = true;						//sees if the place is the list is already taken
			}
			if(placed == true){
				if(x == 0.0){
					array[i].delete();				//if x is 0 it deletes the current one in it's place
					return;
				}
				if(x != 0.0){
					tempObj.value = x;				//if not it replaces the current val with the new val
					return;
				}
			}
			array[i].moveNext();
			//tempSize--;
		}
		

		if(x != 0.0 && placed == false){		//checks if obj was placed in list and if the value is 0.0
			array[i].moveFront();
			if(array[i].index() == -1){					//if list is empty places object at the front of the list
				array[i].append(new dataObj(j,x));
				return;
			}
			if(array[i].index() != -1){
				while(array[i].index() >= 0  && ((dataObj)array[i].get()).place < j){		//if not it moves down the list 
					array[i].moveNext();													//until reaches the right column ot
				}
				//System.out.println(array[i].index());
				if(array[i].index() > -1){											//if index is not at the front of list
					array[i].insertBefore(new dataObj(j,x));						//inserts before the last object
					return;
				}
				if(array[i].index() == -1){
					array[i].append(new dataObj(j,x));								//if index is at the back of list it will append
					return;
				}
			}
		}
	}

    Matrix scalarMult(double x){	// returns a new Matrix that is the scalar product of this Matrix with x
    	int size = getSize();
    	Matrix newMatrix = new Matrix(size);
    	for(int i = 1; i <= size; i++){
    		//System.out.println("hi");
    		if(array[i].length() != 0){
    			array[i].moveFront();
    			while(array[i].index() >= 0){
    				dataObj temp = (dataObj)array[i].get();
    				dataObj newTemp = new dataObj(temp.place, temp.value);
    				newTemp.value = newTemp.value * x;

    				newMatrix.array[i].append(newTemp);
    				array[i].moveNext();
    			}
    		}
    	}
    	return newMatrix;
    }

    Matrix add(Matrix M){  // returns a new Matrix that is the sum of this Matrix with M pre: getSize()==M.getSize()
    	int mainSize = getSize();
    	int newSize = M.getSize();
    	Matrix copy = new Matrix(mainSize);
    	copy = this.copy();

    	if(newSize != mainSize){
    		throw new 
    		RuntimeException("Matrices have different sizes. Can't add.");
    	}
    	Matrix additionM = new Matrix(mainSize);
    	for(int i = 1; i <= mainSize; i++){
	    	copy.array[i].moveFront();
	    	M.array[i].moveFront();
	    	int currentListSize = copy.array[i].length();
	    	int newListSize = M.array[i].length();

	    	//System.out.println(currentListSize+" "+newListSize+"row "+i);

	    	while(copy.array[i].index() >= 0 && M.array[i].index() >= 0){
	    		
	    		boolean placed = false;
	    		dataObj tempCurrent = (dataObj)copy.array[i].get();
	    		dataObj tempM = (dataObj)M.array[i].get();
	    		if(tempCurrent.place == tempM.place){
	    			//if M matrix has an element in the same place as the current array
	    			additionM.array[i].append(new dataObj(tempCurrent.place, tempM.value+tempCurrent.value));
	    			M.array[i].moveNext();
	    			copy.array[i].moveNext();
	    			newListSize--;
	    			currentListSize--;
	    			placed = true;
	    		}

	    		if(tempCurrent.place > tempM.place && placed == false){
	    			//if M matrix has an element where the current matrix doesn't
	    			additionM.array[i].append(new dataObj(tempM.place, tempM.value));
	    			M.array[i].moveNext();
	    			newListSize--;
	    			placed = true;
	    		}
	    		
	    		if(tempCurrent.place < tempM.place){
	    			//if current matrix has an element where the M matrix doesn't
	    			additionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value));
	    			copy.array[i].moveNext();
	    			currentListSize--;
	    			placed = true;
	    		}

	    		if(tempM != null && tempCurrent == null && placed == false){
	    			//if M matrix has an element in the same place as the current array has nothing
	    			additionM.array[i].append(new dataObj(tempM.place, tempM.value));
	    			M.array[i].moveNext();
	    			newListSize--;
	    			placed = true;
	    		}
	    		if(placed == false){
	    			additionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value));
	    			copy.array[i].moveNext();
	    			currentListSize--;
	    		}
	    	
	    		// currentListSize--;
	    		// newListSize--;
	    	}
	    	//System.out.println(currentListSize+" "+newListSize);
	    	int holder = currentListSize;
	    	if(currentListSize > newListSize){
	    		while(currentListSize > 0){
	    			dataObj tempCurrent = (dataObj)copy.array[i].get();
	    			additionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value));		//if theres extras add
	    			copy.array[i].moveNext();
	    			currentListSize--;
	    		}
	    	}

	    	currentListSize = holder;
	    	if(currentListSize < newListSize){
	    		while(newListSize > 0){
	    			dataObj tempM = (dataObj)M.array[i].get();
	    			additionM.array[i].append(new dataObj(tempM.place, tempM.value));				//if theres extras add
	    			M.array[i].moveNext();
	    			newListSize--;
	    		}
	    	}
    	}
    	return additionM;
    }

    Matrix sub(Matrix M){  // returns a new Matrix that is the difference of this Matrix with M pre: getSize()==M.getSize()
    	int mainSize = getSize();		//current minus new
    	int newSize = M.getSize();
    	Matrix copy = copy();

    	if(newSize != mainSize){
    		throw new 
    		RuntimeException("Matrices have different sizes. Can't subtract.");
    	}
    	Matrix subtractionM = new Matrix(mainSize);
    	for(int i = 1; i <= mainSize; i++){
	    	copy.array[i].moveFront();
	    	M.array[i].moveFront();
	    	int currentListSize = copy.array[i].length();
	    	int newListSize = M.array[i].length();
	    	
	    	while(copy.array[i].index() >= 0 && M.array[i].index() >= 0){
	    		boolean placed = false;
	    		dataObj tempCurrent = (dataObj)copy.array[i].get();
	    		dataObj tempM = (dataObj)M.array[i].get();
	    		if(tempCurrent.place == tempM.place && placed == false){
	    			//if M matrix has an element in the same place as the current array
	    			if((tempCurrent.value-tempM.value) != 0.0){
	    				subtractionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value-tempM.value));
	    			}
	    			M.array[i].moveNext();
	    			copy.array[i].moveNext();
	    			newListSize--;
	    			currentListSize--;
	    			placed = true;
	    		}

	    		if(tempCurrent.place > tempM.place && placed == false){
	    			//if M matrix has an element where the current matrix doesn't
	    			subtractionM.array[i].append(new dataObj(tempM.place, (-1 * tempM.value)));
	    			M.array[i].moveNext();
	    			newListSize--;
	    			placed = true;
	    		}
	    		
	    		if(tempCurrent.place < tempM.place){
	    			//if current matrix has an element where the M matrix doesn't
	    			subtractionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value));
	    			copy.array[i].moveNext();
	    			currentListSize--;
	    			placed = true;
	    		}

	    		if(tempM != null && tempCurrent == null && placed == false){
	    			//if M matrix has an element in the same place as the current array has nothing
	    			subtractionM.array[i].append(new dataObj(tempM.place, -1 * tempM.value));
	    			M.array[i].moveNext();
	    			newListSize--;
	    			placed = true;
	    		}
	    		if(placed == false){
	    			subtractionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value));
	    			copy.array[i].moveNext();
	    			currentListSize--;
	    		}
	    	
	    		// currentListSize--;
	    		// newListSize--;
	    	}
	    	//System.out.println(currentListSize+" "+newListSize);
	    	int holder = currentListSize;
	    	if(currentListSize > newListSize){
	    		while(currentListSize > 0){
	    			dataObj tempCurrent = (dataObj)copy.array[i].get();
	    			subtractionM.array[i].append(new dataObj(tempCurrent.place, tempCurrent.value));		//if theres extras add
	    			copy.array[i].moveNext();
	    			currentListSize--;
	    		}
	    	}
	    	currentListSize = holder;
	    	//System.out.println(currentListSize+" "+newListSize);
	    	if(currentListSize < newListSize){
	    		while(newListSize > 0){
	    			dataObj tempM = (dataObj)M.array[i].get();
	    			subtractionM.array[i].append(new dataObj(tempM.place, -1 * tempM.value));				//if theres extras add
	    			M.array[i].moveNext();
	    			newListSize--;
	    		}
	    	}
    	}
    	return subtractionM;
    }
 

    Matrix transpose(){	// returns a new Matrix that is the transpose of this Matrix
    	int mainSize = getSize();
    	Matrix transpose = new Matrix(mainSize);		//creates matrix of same size
    	for(int i = 1; i <= mainSize; i++){
    		array[i].moveFront();					//runs through rows
    		int listSize = array[i].length();
    		while(array[i].index() >= 0){
    			dataObj temp = (dataObj)array[i].get();

    			transpose.changeEntry(temp.place, i, temp.value);		//changes row with column using changeEntry function
    			array[i].moveNext();									//moves cursor to next Obj
    			//listSize--;
    		}
    	}
    	return transpose;
    }

    Matrix mult(Matrix M){  // returns a new Matrix that is the product of this Matrix with M // pre: getSize()==M.getSize()
    	int currentSize = this.getSize();
    	int newSize = M.getSize();
    	if(currentSize != newSize){
    		throw new
    		RuntimeException("Matrices have different sizes. Can't multiply.");
    	}
    	Matrix multiplication = new Matrix(currentSize);		//creates new matrix to return
    	Matrix transposedM = M.transpose();					//flips matrix M to multiply lists across

    	for(int a = 1; a <= currentSize; a++){
    		int currentListLength = this.array[a].length();
    		if(currentListLength == 0){						//if current list is 0 it skips the current list
    			continue;
    		}
    		
    		for(int b = 1; b <= currentSize; b++){
    			if(newSize == 0){							//if current list is 0 it skips the current input list
    				continue;
    			}
    			multiplication.changeEntry(a,b,listMultFunc(this.array[a],transposedM.array[b]));
    		}	//multiplies the current selected list with the input selected list
    	}		//using the listMultFunc
    	return multiplication;
    }

    double listMultFunc(List A, List B){
    	A.moveFront();
    	B.moveFront();					//moves both the lists to the front
    	
    	double listsTotals = 0.0;
    	int listALength = A.length();
    	int listBLength = B.length();
    	while(A.index() >= 0 && B.index() >= 0){
    		dataObj tempOne = (dataObj)A.get();
    		dataObj tempTwo = (dataObj)B.get();
    		boolean hit = false;

    		if(tempOne.place < tempTwo.place){
    			A.moveNext();			//if not the same place moves A to next Obj
    			hit = true;

    		}
    		if(tempOne.place > tempTwo.place){
    			B.moveNext();			//if not the same place moves B to next Obj
    			hit = true;
    		}
    		if(hit == false){
    			double newVal = tempOne.value * tempTwo.value;
    			listsTotals = listsTotals + newVal;
    			A.moveNext();		//adds the multiplied value to listTotals
    			B.moveNext();
    		}
    		// listALength--;
    		// listBLength--;
    	}
    	return listsTotals;
    }

    // Other functions
	public String toString(){ // overrides Object's toString() method
		String output = "";
		int size = getSize();
		dataObj temp;
		for(int i = 1; i <= size; i++){
			if(array[i].length() > 0){
				output = output + (i+": ");
			}
			array[i].moveFront();
			int counter = array[i].length();
			while(array[i].length() > 0 && array[i].index() >= 0){
				temp = (dataObj)array[i].get();			
				int tempPlace = temp.place;
				double tempValue = temp.value;

				String tempPlaceString = Integer.toString(tempPlace);
				String tempValueString = String.valueOf(tempValue);
				output += "(";
				output += tempPlaceString;
				output += ", ";
				output += tempValueString;
				output += ")";
				array[i].moveNext();
				if(counter > 1){
					output += " ";
				}
				counter--;
			}
			if(array[i].length() > 0){
				output = output + ("\n");
			}
		}
		return output;
	}
}



