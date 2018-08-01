//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// Sparce.java  
// pa3
// CMPS101
// Spring 2018
// May 9, 2018
//-----------------------------------------------------------------------------
import java.io.*;
import java.util.*;
import java.util.Scanner;

class Sparse{	
	public static void main(String args[]) throws IOException{
		if(args.length < 2){
			System.out.println("Usage: java -jar length.jar <input file> <output file>");		
			System.exit(1); 			//if less or more than 2 args throws error
		}
		Scanner inData = new Scanner(new File(args[0]));		//opens scanner
		PrintWriter out = new PrintWriter(new File (args[1]));	//opens printwriter

		String inputSpecs = "";
		String[] brokenInput = null;
		inputSpecs = inData.nextLine()+" ";
		brokenInput = inputSpecs.split("\\s+");				//breaks up first line of data and assigns to different ints
		int matrixSize = Integer.parseInt(brokenInput[0]);	//using parseInt		
		int numLinesA = Integer.parseInt(brokenInput[1]);	
		int numLinesB = Integer.parseInt(brokenInput[2]);

		Matrix a = new Matrix(matrixSize);					//creates new Matrix Obj
		Matrix b = new Matrix(matrixSize);
		String blankLine = inData.nextLine();

		int lineCounter = 1;
		String currentLine = "";
		String[] brokenCurrent = null;
		while(inData.hasNextLine()){						//runs thorugh rest of input lines 
			currentLine = inData.nextLine()+" ";			//and fills in the new Matrices using changeEntry Method
			brokenCurrent = currentLine.split("\\s+");		
			if(lineCounter < numLinesA+1){
				a.changeEntry(Integer.parseInt(brokenCurrent[0]), Integer.parseInt(brokenCurrent[1]), Double.parseDouble(brokenCurrent[2]));
			}

			if(lineCounter > numLinesA+1){
				b.changeEntry(Integer.parseInt(brokenCurrent[0]), Integer.parseInt(brokenCurrent[1]), Double.parseDouble(brokenCurrent[2]));
			
			}
			lineCounter++;
		}

		out.print("A has ");
		out.print(a.getNNZ());
		out.println(" non-zero entries:");
      	out.println(a);

      	out.print("B has ");
     	out.print(b.getNNZ());
     	out.println(" non-zero entries:");
     	out.println(b);

     	out.println("(1.5)*A =");
     	Matrix c = new Matrix(matrixSize);
     	c = a.scalarMult(1.5);
     	out.println(c);

     	out.println("A+B =");
     	Matrix d = new Matrix(matrixSize);
     	d = a.add(b);
     	out.println(d);

     	out.println("A+A =");
     	Matrix e = new Matrix(matrixSize);
     	e = a.add(a);
     	out.println(e);

     	out.println("B-A =");
     	Matrix f = new Matrix(matrixSize);
     	f = b.sub(a);
     	out.println(f);

     	out.println("A-A =");
     	Matrix g = new Matrix(matrixSize);
     	g = a.sub(a);
     	out.println(g);

     	out.println("Transpose(A) =");
     	Matrix h = new Matrix(matrixSize);
     	h = a.transpose();
     	out.println(h);

		out.println("A*B =");
     	Matrix i = new Matrix(matrixSize);
     	i = a.mult(b);
     	out.println(i);

     	out.println("B*B =");
     	Matrix j = new Matrix(matrixSize);
     	j = b.mult(b);
     	out.println(j);

     	inData.close();
     	out.close();
	}
}
