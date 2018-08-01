//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// MatrixTest.java  
// pa3
// CMPS101
// Spring 2018
// May 9, 2018
//-----------------------------------------------------------------------------
class MatrixTest{
	public static void main(String[] args){

		Matrix sam = new Matrix(2);
		sam.changeEntry(1,1,1);
		sam.changeEntry(1,2,2);
		sam.changeEntry(2,1,3);
		sam.changeEntry(2,2,4);

		Matrix sam2 = new Matrix(2);
		sam2.changeEntry(1,1,3);
		sam2.changeEntry(1,2,3);
		sam2.changeEntry(2,1,3);
		sam2.changeEntry(2,2,3);
		

		String temp = sam.toString();
		System.out.println(temp);

		String temp2 = sam2.toString();
		System.out.println(temp2);

		// Matrix newM = sam.scalarMult(2);
		// String temp2 = newM.toString();
		// System.out.println(temp2);

		// newM.makeZero();

		// String temp3 = newM.toString();
		// System.out.println(temp3);

		Matrix subM = sam.add(sam2);
		String temp3 = subM.toString();
		System.out.println(temp3);
	}
}