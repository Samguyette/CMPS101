//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Lex.java  
// Takes input of a file of words and sorts their indicies and places them in
// a List lexicographicly
//-----------------------------------------------------------------------------
import java.io.*;
import java.util.*;
import java.util.Scanner;

class Lex{	
	public static void main(String args[]) throws IOException{
		if(args.length < 2){
			System.out.println("Usage: java -jar length.jar <input file> <output file>");		
			System.exit(1); 			//if less or more than 2 args throws error
		}
		Scanner inCounter = new Scanner(new File(args[0]));		//opens scanner1
		Scanner inData = new Scanner(new File(args[0]));		//opens scanner2
		PrintWriter out = new PrintWriter(new File (args[1]));	//opens printwriter
		int counter = 0;

		while(inCounter.hasNextLine()){
			String temp = inCounter.nextLine();			//counts number of elements in input
			counter++;
		}
		inCounter.close();

		String data[] = new String[counter];
		int indicies = 0;						//places elements in an array called data
		while(inData.hasNextLine()){
			data[indicies] = inData.nextLine();
			indicies++;
		}

		List inputList = new List();	//creates new list called inputList

		inputList.append(0);			//places first element in list, no need to sort

		for(int arrayCounter = 1; arrayCounter < data.length; arrayCounter++){		//loops through every element in the array
			inputList.moveBack();								//moves curser to the back
			String tempOne = data[arrayCounter];
			int listCounter = arrayCounter - 1;
			boolean x = true;

			while(x == true && tempOne.compareTo(data[inputList.get()]) <= 0){			//holds data from array and finds proper place in list				
				//System.out.println(tempOne+" "+data[inputList.get()]);
				inputList.movePrev();											//by movingPrev down thorugh the list until it is alphabetically
				listCounter--;													//found the right place
				if(listCounter < 0){
					x = false;						//boolean trigger to not run compareTo if list counter is negative
				}									//in place
			}

			if(inputList.index() >= 0){
				inputList.insertAfter(arrayCounter);							//if not last it insterts the indecie between the two proper indecies
			}
			if(inputList.index() < 0){
				inputList.prepend(arrayCounter);								//if at the front this indecie is placed at the start of the list
			}

		}

		
		inputList.moveFront();						//moves cursor to the front for printing
		for(int i = 0; i < counter; i++){
			out.println(data[inputList.get()]);		//loops through list and prints part of array with correct indecie
			inputList.moveNext();
		}

		out.close();								//closes Writers and Readers
		inData.close();
		inCounter.close();

	}
}
