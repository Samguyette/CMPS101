//-----------------------------------------------------------------------------
// Samuel Guyette
// sguyette
// 1518801
// ListTest.java  
// pa3
// CMPS101
// Spring 2018
// May 9, 2018
//-----------------------------------------------------------------------------
class ListTest{
	public static void main(String[] args) {
		List testList = new List();
		//dataObj testDataObj = new dataObj(1,5.0);

		for(int i = 0; i < 5; i++){
			testList.append(i);
		}
		testList.prepend(9);
		testList.prepend(9);
		testList.prepend(9);

		String list = testList.toString();
		System.out.println(list);

		testList.clear();

		list = testList.toString();
		System.out.println(list+"cleared List");

		for(int i = 0; i < 5; i++){
			testList.append(i);
		}

		testList.moveNext();
		testList.moveNext();
		testList.insertAfter(9);
		testList.insertBefore(9);
		
		list = testList.toString();
		System.out.println(list+"inserted after and before cursor.");

		System.out.println("The length of the list is "+testList.length());
		System.out.println("The front element is "+testList.front());
		System.out.println("The back element is "+testList.back());
		System.out.println("The cursor element is "+testList.get());
		System.out.println("Is the List NULL? "+testList.isNull());

		testList.deleteFront();
		testList.deleteBack();
		list = testList.toString();
		System.out.println(list+"Front and back elements deleted.");
	}
}